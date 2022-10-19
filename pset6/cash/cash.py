from cs50 import get_float

while True:
    owed = get_float("Change owed: ")
    if owed >= 0:
        break

cents = round(owed * 100)

count = 0
while cents != 0:
    if cents >= 25:
        count += (cents - cents % 25) / 25
        cents = cents % 25
    elif cents >= 10:
        count += (cents - cents % 10) / 10
        cents = cents % 10
    elif cents >= 5:
        count += (cents - cents % 5) / 5
        cents = cents % 5
    else:
        count += cents
        cents = 0

print(int(count))