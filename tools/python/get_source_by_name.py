import mysql.connector
import sys

# must install mysql-connector-python, not mysql-connector
#>python -m pip install mysql-connector-python
mydb = mysql.connector.connect(user='root', password='db_password', 
                              host='127.0.0.1', database='db_name',
                              auth_plugin='mysql_native_password')
                              
fd = open('../sql/get_source_by_name.sql', 'r')
sql = fd.read()
fd.close()
param = sys.argv[1]

mycursor = mydb.cursor()
mycursor.execute(sql, (param,))
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