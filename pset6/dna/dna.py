import csv
from sys import argv, exit


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Open and read csv file
    csvfile = open(argv[1], "r")
    reader = csv.DictReader(csvfile)

    # Open and read txt file
    txtfile = open(argv[2], "r")
    sequence = txtfile.read()

    # Get the list of STRs
    key_list = reader.fieldnames

    # Caculate the longest run for each STR
    result = {}
    for key in key_list:
        max_count = 0
        for i in range(len(sequence)):
            count = 0
            while sequence[i:(i + len(key))] == key:
                count += 1
                i += len(key)
            if count > max_count:
                max_count = count
        result[key] = max_count

    # Comparing against data in csv
    for row in reader:
        same_count = 0
        for key in row:
            if key != 'name' and int(row[key]) == result[key]:
                same_count += 1
        if same_count == len(row) - 1:
            print(row['name'])
            csvfile.close()
            txtfile.close()
            exit(0)
    print("No match")
    csvfile.close()
    txtfile.close()
    exit(1)


main()