import csv
import os
import random
import sqlite3


path_to_pictures = os.getenv("POLL_ZAPP") + "\\Pictures\\"

primary_database_path = os.getenv("POLL_ZAPP") + "\\databases\\primary_database.db"
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

sources = ["NYT", "WAPO", "HUFFPO", "NYPOST"]
politician_names = ["Rory", "David", "Kate", "Brendan"]

source_range = list(range(4))
politician_range = list(range(4))
random.shuffle(source_range)
random.shuffle(politician_range)

for constituency_id in range(1, 5):
    for j in source_range:
        for i in politician_range:
            cursor.execute('''
                INSERT INTO poll_results
                (constituency_id, source, date_time, politician_name, poll_value)
                VALUES
                (?, ?, ?, ?, ?)
            ''', (constituency_id, sources[j], 20200201 + j, politician_names[i], j * 20))

db.commit()
