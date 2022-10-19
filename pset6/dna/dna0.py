import csv
from sys import argv, exit


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Open and read csv file
    csvfile = open(argv[1], "r")
    reader = csv.reader(csvfile)

    # Open and read txt file
    txtfile = open(argv[2], "r")
    sequence = txtfile.read()

    # Get the list of STRs
    str_list = next(reader)
    str_list.pop(0)

    # Caculate the longest run for each STR
    value_list = []
    for i in str_list:
        max_count = 0
        for j in range(len(sequence)):
            count = 0
            while sequence[j:(j + len(i))] == i:
                count += 1
                j += len(i)
            if count > max_count:
                max_count = count
        value_list.append(max_count)
    txtfile.close()

    # Comparing against data in csv
    for row in reader:
        same_count = 0
        for i in range(1, len(row)):
            if int(row[i]) == value_list[i - 1]:
                same_count += 1
        if same_count == len(row) - 1:
            print(row[0])
            csvfile.close()
            exit(0)
    print("No match")
    csvfile.close()
    exit(1)


main()