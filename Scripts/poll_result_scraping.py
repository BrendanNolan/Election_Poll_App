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
