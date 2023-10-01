from bs4 import BeautifulSoup	#table scraping
import requests			#html request
import pandas as pd		#printing

def capEachWord(name):
	res =' '.join(word[0].upper() + word[1:] for word in name.split())
	return str(res);

artistName="      the       weeknd      "
#artistName=input("Enter the artists' name: ")
artistName=str(" ".join(artistName.strip().split()))	#removing unwanted spaces
artistName=capEachWord(artistName)	

wiki_url="https://en.wikipedia.org/wiki/{artist}_discography".format(artist=artistName.replace(" ","_"))	#website link
print(wiki_url)
table_id = 'votingmembers'

response=requests.get(wiki_url)

soup = BeautifulSoup(response.text,'html.parser')
print(type(soup))
'''for caption in soup.find_all('caption'):
    if caption.get_text() == 'List of singles as featured artist, with selected chart positions and certifications, showing year released and album name\n':
        table = caption.find_parent('table', {'class': 'wikitable plainrowheaders'})
        #print("yes")
        #print(table) '''

# First remove Falsey values(None) if present
table_soup = soup.find_all('table')
filtered_table_soup = [table for table in table_soup if table.caption is not None]

required_table = None

for table in filtered_table_soup:
    if str(table.caption.string).strip() == 'List of singles as featured artist, with selected chart positions and certifications, showing year released and album name':
        required_table = table
        #print("yes")
        break    

#print(required_table)

'''
rows = []

# Find all `tr` tags
data_rows = required_table.find_all('tr')

for row in data_rows:
    value = row.find_all('td')
    beautified_value = [ele.text.strip() for ele in value]
    # Remove data arrays that are empty
    if len(beautified_value) == 0:
        continue
    rows.append(beautified_value)

for r in rows:
	print(r)'''
	
	
#print(table)
op=pd.read_html(str(required_table))


pd.set_option('display.max_columns', 100)
pd.set_option('display.max_rows', 500)
pd.set_option('display.min_rows', 500)
pd.set_option('display.max_colwidth', 150)
pd.set_option('display.width', 120)
pd.set_option('expand_frame_repr', True)

'''for x in op:
	print(type(x))'''
#print(op[0]['Title'])
#print(table)
#congress_table=soup.find( 'table' ,attrs={'':})
