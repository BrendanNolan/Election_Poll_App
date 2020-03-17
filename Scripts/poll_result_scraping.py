import csv
import os
from random import randrange
import sqlite3


path_to_pictures = "C:\\CPP_Stuff\\Election_Poll_App\\Pictures\\"

primary_database_path = "C:\\CPP_Stuff\\Election_Poll_App\\primary_database.db"
primary_database = open(primary_database_path, 'a')
primary_database.close()

db = sqlite3.connect(primary_database_path)
cursor = db.cursor()

cursor.execute('''
    DROP TABLE IF EXISTS poll_results
''')
cursor.execute('''
    CREATE TABLE poll_results
        (
        constituency_id INTEGER,
        source TEXT,
        date_time DATETIME,
        politician_name TEXT,
        poll_value INT
        )
''')
db.commit()

sources = ["NYT", "WAPO", "HUFFPO"]

for constituency_id in range(1, 5):
    for j in range(3):
        cursor.execute('''
            INSERT INTO poll_results
            (constituency_id, source, date_time, politician_name, poll_value)
            VALUES
            (?, ?, ?, ?, ?)
        ''', (constituency_id, sources[j], 20200201 + i, "Politician" + str(i), i * 40))
        db.commit()
