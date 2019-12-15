import sys
from config import getConfiguredDB

# must install mysql-connector-python, not mysql-connector
#>python -m pip install mysql-connector-python
mydb = getConfiguredDB()
                              
param = sys.argv[1]
fd = open('../sql/get_' + param + '.sql', 'r')
sql = fd.read()
fd.close()


mycursor = mydb.cursor()
mycursor.execute(sql)
result = mycursor.fetchall()

columnCount = len(mycursor.description)
maxWidths = [0] * len(mycursor.description)
columnNames = [""] * len(mycursor.description)

indx = -1
for row in result:
  indx = -1
  for col in  row:
    indx += 1
    if len(col) > maxWidths[indx]:
      maxWidths[indx] = len(col)
  
indx = -1  
for columnName in mycursor.description:
  indx += 1
  columnNames[indx] = columnName[0].split("_")[0].capitalize()    

line = "|" 
for maxW in maxWidths:
  line += "_" * (maxW+1)
line += "_" *(columnCount-1) + "|"

topLine = " "+"_" * (len(line) - 2) + " "
print(topLine)
header = "|"
indx = -1
for columnName in columnNames:
  indx += 1
  header += " " +columnName.ljust(maxWidths[indx]) + "|"
print(header)
print(line) 
for row in result:
  rowText = "| "
  indx = -1
  for col in row:
    indx += 1
    rowText += col.ljust(maxWidths[indx]) + "| "
  print(rowText)
print(line)