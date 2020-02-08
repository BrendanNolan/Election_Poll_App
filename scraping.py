import csv
import os
import sqlite3


primary_database_path = "C:\\CPP_Stuff\\Election_Poll_App\\primary_database.db"
primary_database = open(primary_database_path, 'w')
primary_database.close()

db = sqlite3.connect(primary_database_path)
cursor = db.cursor()

cursor.execute('''
    CREATE TABLE politicians 
        (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        constituency_id INTEGER, 
        image_url TEXT, 
        name TEXT, 
        elected INTEGER, 
        candidate INTEGER, 
        party_name TEXT, 
        party_rgb_red TEXT, 
        party_rgb_green TEXT, 
        party_rgb_blue TEXT
        )
''')
db.commit()

cursor.execute('''
    CREATE TABLE constituencies  
            (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            name TEXT, 
            latitude INTEGER, 
            longitude INTEGER
            )
''')
db.commit()

for i in range(3):
    cursor.execute('''
        INSERT INTO constituencies 
            (name, latitude, longitude) 
            VALUES  
            (?, ?, ?)
    ''', ("Wexford", i * 40, i * 40))
    db.commit()
    constituency_id = cursor.lastrowid

    cursor.execute('''
        INSERT INTO politicians 
                (
                constituency_id, image_url, name, elected, candidate, 
                party_name, party_rgb_red, party_rgb_green, party_rgb_blue
                ) 
                VALUES 
                (?, ?, ?, ?, ?, ?, ?, ?, ?)            
    ''', (constituency_id, os.path.abspath("Pictures\\pic" + str(i) + ".jpg"), "Brendan", 1, i % 2, "Fianna Fail", 0, 200, 0))
    db.commit()

    cursor.execute('''
        INSERT INTO politicians 
                (
                constituency_id, image_url, name, elected, candidate, 
                party_name, party_rgb_red, party_rgb_green, party_rgb_blue
                ) 
                VALUES 
                (?, ?, ?, ?, ?, ?, ?, ?, ?)            
    ''', (constituency_id, os.path.abspath("Pictures\\pic" + str(i) + ".jpg"), "Rory", 1, i % 2, "Fine gael", 0, 0, 200))
    db.commit()

    cursor.execute('''
        INSERT INTO politicians 
                (
                constituency_id, image_url, name, elected, candidate, 
                party_name, party_rgb_red, party_rgb_green, party_rgb_blue
                ) 
                VALUES 
                (?, ?, ?, ?, ?, ?, ?, ?, ?)            
    ''', (constituency_id, os.path.abspath("Pictures\\pic" + str(i) + ".jpg"), "David", 0, i % 2, "Labour", 200, 0, 0))
    db.commit()

    cursor.execute('''
        INSERT INTO politicians 
                (
                constituency_id, image_url, name, elected, candidate, 
                party_name, party_rgb_red, party_rgb_green, party_rgb_blue
                ) 
                VALUES 
                (?, ?, ?, ?, ?, ?, ?, ?, ?)            
    ''', (constituency_id, os.path.abspath("Pictures\\pic" + str(i) + ".jpg"), "Kate", 1, i % 2, "Labour", 200, 0, 0))
    db.commit()

print ("Exporting data into CSV............")
for table_name in [str("constituencies"), str("politicians")]:
    cursor.execute("select * from " + table_name)
    with open(table_name + ".csv", "w") as csv_file:
        csv_writer = csv.writer(csv_file, delimiter=",")
        csv_writer.writerow([i[0] for i in cursor.description])
        csv_writer.writerows(cursor)

        dirpath = os.getcwd() + '\\' + table_name + ".csv"
        print("Data exported Successfully into {}".format(dirpath))
