import csv
from cs50 import SQL

# Create a new DB
open("shows.db", "w").close()
db = SQL("sqlite:///shows.db")


# Create tables
db.execute("CREATE TABLE show (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id)")

# Insert into tables row-by-row
## Since 'id' in the 'show' table is PRIMARY KEY, the INSERT function will return the value of the id
id = db.execute("INSERT INTO shows (title) VALUES(?)", title)
db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", id, genre)


# Race conditions
db.execute("BEGIN TRANSACTION")

## Get the number of 'likes' of a post
rows = db.execute("SELECT likes FROM posts WHERE id = ?", id);
likes = rows[0]["likes"]

## Update 'likes' for a post
db.execute("UPDATE post SET like = ? WHERE id = ?", likes + 1, id);
db.execute("COMMIT")