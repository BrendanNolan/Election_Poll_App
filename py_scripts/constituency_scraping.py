import csv
import os
import sqlite3


path_to_pictures = "C:\\CPP_Stuff\\Election_Poll_App\\Pictures\\"

primary_database_path = os.getenv("POLL_ZAPP") + "\\databases\\primary_database.db"
primary_database = open(primary_database_path, 'a')
primary_database.close()

db = sqlite3.connect(primary_database_path)
cursor = db.cursor()

cursor.execute('''
    DROP TABLE IF EXISTS constituencies
''')
cursor.execute('''
    CREATE TABLE constituencies  
        (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        name TEXT, 
        latitude INTEGER, 
        longitude INTEGER,
        area_sq_km INTEGER
        )
''')
db.commit()

constituency_names = ["Wexford", "Dublin West", "Dun Laoighre", "Galway"]
constituency_areas = [2365, 600, 600, 3500]
constituency_latitudes = [] #These should be floats. Need to change C++ code.
constituency_longitudes = [] #These should be floats. Need to change C++ code.

for i in range(len(constituency_names)):
    cursor.execute('''
        INSERT INTO constituencies 
            (name, latitude, longitude, area_sq_km) 
            VALUES  
            (?, ?, ?, ?)
    ''', (constituency_names[i], i * 40, i * 40, constituency_areas[i]))
    db.commit()
