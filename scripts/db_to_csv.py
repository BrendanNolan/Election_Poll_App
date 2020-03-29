import csv
import os
import sqlite3


primary_database_path = "C:\\CPP_Stuff\\Election_Poll_App\\primary_database.db"
primary_database = open(primary_database_path, 'r')
primary_database.close()

db = sqlite3.connect(primary_database_path)
cursor = db.cursor()

table_names = cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
print("Database contains " + str(len(table_names.fetchall())) + " tables.")
print("Table names:")
for table in table_names:
    print(table[0])

print("Exporting data into CSV............")
for table_name in [str("constituencies"), str("politicians"), str("poll_results")]:
    try:
        cursor.execute("select * from " + table_name)
    except:
        print(str("Could not select from table ") + table_name)
        continue
    with open(table_name + ".csv", "w") as csv_file:
        csv_writer = csv.writer(csv_file, delimiter=",")
        csv_writer.writerow([i[0] for i in cursor.description])
        csv_writer.writerows(cursor)

        dirpath = os.getcwd() + '\\' + table_name + ".csv"
        print("Data exported Successfully into {}".format(dirpath))
