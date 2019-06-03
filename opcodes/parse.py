from bs4 import BeautifulSoup
import re

html_file = 'opcodes.htm' 
out_file = 'opcodes.csv'

opcodes = None
with open(html_file) as fp:
    opcodes = BeautifulSoup(fp, 'html.parser')
    if opcodes is None:
        print('Error opening %s' % html_file)
        exit()

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
            continue # empty cell ; invalid opcode
     
        op = text[0]
        size = re.findall('\d+', text[1])[0]
        cycles = re.findall('\d+', text[1])[1]
        flags = text[2].split(' ')
        z_f = flags[0]
        n_f = flags[1]
        h_f = flags[2]
        c_f = flags[3]

        print('(%i, %i) op: %s, size: %s, cycles: %s, flags: (%s, %s, %s, %s)' % (i-1, j-1, op, size, cycles, z_f, n_f, h_f, c_f))
