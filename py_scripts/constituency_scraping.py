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
        latitude FLOAT, 
        longitude FLOAT,
        area_sq_km FLOAT
        )
''')
db.commit()

constituency_names = ["Wexford", "Dublin West", "Dun Laoighre", "Galway"]
constituency_areas = [2365.0, 600.0, 600.0, 3500.0]
constituency_latitudes = [52.3369, 53.3104, 53.2944 , 53.2707] #These should be floats. Need to change C++ code.
constituency_longitudes = [6.4633, 6.2899, 6.1339 , 9.0568] #These should be floats. Need to change C++ code.

for i in range(len(constituency_names)):
    cursor.execute('''
        INSERT INTO constituencies 
            (name, latitude, longitude, area_sq_km) 
            VALUES  
            (?, ?, ?, ?)
    ''', (constituency_names[i], constituency_latitudes[i], constituency_longitudes[i], constituency_areas[i]))
    db.commit()
