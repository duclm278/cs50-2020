import csv
from cs50 import SQL
from sys import argv, exit

# Check the number of command-line arguments
if len(argv) != 2:
    print("Invalid!")
    exit(1)
else:
    if argv[1][-4:] != ".csv":
        print("Invalid!")
        exit(1)

# Create database
open("students.db", "w").close()
db = SQL("sqlite:///students.db")

# Create table
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# Open CSV file
with open(argv[1], "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over TSV file
    for row in reader:

        # Parse name
        name = row['name'].split()
        if len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]
        elif len(name) == 2:
            first = name[0]
            middle = None
            last = name[1]

        # Insert students
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   first, middle, last, row['house'], row['birth'])
