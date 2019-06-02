from bs4 import BeautifulSoup

html_file = 'opcodes.htm' 
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
for r in rows:
    print(r.prettify())
