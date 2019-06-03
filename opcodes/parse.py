from bs4 import BeautifulSoup
import re
import csv

# removes parentheses in a string
def remove_paren(s):
    s = s.replace('(', '')
    s = s.replace(')', '')
    return s

html_file = 'gameboy_opcodes.html' 
out_file = open('opcodes.csv', 'w')
csv_file = csv.writer(out_file)

mem_pattern = re.compile('^\([^)(]*\)$')

opcodes = None
with open(html_file) as fp:
    opcodes = BeautifulSoup(fp, 'html.parser')
    if opcodes is None:
        print('Failed to open %s' % html_file)
        exit()
    fp.close()

# write .csv header
csv_file.writerow(['row', 'col', 'op', 'size', 'cycles', 'rd', 'rd_mem', 'rs', 'rs_mem', 'z_f', 'n_f', 'h_f', 'c_f'])

# get intruction set table
table = opcodes.find_all('table')[0].find('tbody')

# iterate through the rows
rows = table.find_all('tr')
for i, row in enumerate(rows):
    #print(row.prettify())
    if i == 0: # table header ; skip
        continue 
    
    # iterate through the columns in this row
    cols = row.find_all('td')
    for j, col in enumerate(cols):
        if j == 0: # first column is a header ; skip
            continue
        # remove non-breaking space (UTF-8 encoding) and replace <br> tags with new line
        text = re.sub('\xc2\xa0', ' ', col.encode_contents())
        text = re.sub('<br\/?>', '\n', text).split('\n')
        if len(text) != 3:
            csv_file.writerow([i-1, j-1, 'INVALID', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1])
            continue # empty cell ; invalid opcode
     
        insn = text[0].split(' ')
        op = insn[0]
        rd = None
        rs = None
        # _mem indicates a dereference
        rd_mem = 0
        rs_mem = 0
        if len(insn) > 1:
            operands = insn[1].split(',')
            rd = operands[0]
            if mem_pattern.match(rd):
                rd = remove_paren(rd)
                rd_mem = 1
            if len(operands) > 1:
                rs = operands[1]
                if mem_pattern.match(rs):
                    rs = remove_paren(rs)
                    rs_mem = 1

        size = re.findall('\d+', text[1])[0]
        cycles = re.findall('\d+', text[1])[1]
        flags = text[2].split(' ')
        z_f = flags[0]
        n_f = flags[1]
        h_f = flags[2]
        c_f = flags[3]

        # print('(%i, %i) op: %s, size: %s, cycles: %s, flags: (%s, %s, %s, %s)' % (i-1, j-1, op, size, cycles, z_f, n_f, h_f, c_f))
        csv_file.writerow([i-1, j-1, op, size, cycles, rd, rd_mem, rs, rs_mem, z_f, n_f, h_f, c_f])

out_file.close()
