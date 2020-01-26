import sqlite3

primary_database_path = "/mnt/c/CPP_Stuff/Election_Poll_App/primary_database.db"
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

cursor.execute('''
    INSERT INTO constituencies 
        (name, latitude, longitude) 
        VALUES  
        (?, ?, ?)
''', ("Wexford", 100, 100))
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
''', (constituency_id, "C:\\Users\\Brendan\\Pictures\\Camera Roll\\pic.jpg", "Brendan", 1, 1, "Fianna Fail", 0, 200, 0))
db.commit()
