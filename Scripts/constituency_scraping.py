import csv
import os
from random import randrange
import sqlite3


path_to_pictures = "C:\\CPP_Stuff\\Election_Poll_App\\Pictures\\"

primary_database_path = "C:\\CPP_Stuff\\Election_Poll_App\\primary_database.db"
primary_database = open(primary_database_path, 'w')
primary_database.close()

db = sqlite3.connect(primary_database_path)
cursor = db.cursor()

cursor.execute('''
    DROP TABLE [IF EXISTS] constituencies
''')
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

constituency_names = ["Wexford", "Dublin West", "Dun Laoighre", "Galway"]

for i in range(len(constituency_names)):
    cursor.execute('''
        INSERT INTO constituencies 
            (name, latitude, longitude) 
            VALUES  
            (?, ?, ?)
    ''', (constituency_names[i], i * 40, i * 40))
    db.commit()
