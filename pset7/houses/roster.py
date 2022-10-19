import csv
from cs50 import SQL
from sys import argv, exit

# Check the number of command-line arguments
if len(argv) != 2:
    print("Invalid!")
    exit(1)

# Open database
db = SQL("sqlite:///students.db")

# Query database
rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])

for row in rows:
    first = row['first']
    middle = row['middle']
    last = row['last']
    birth = row['birth']

    # Print out each student’s full name and birth year
    if row['middle'] == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")
