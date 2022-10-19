from cs50 import get_string


def main():
    number_str = get_string("Number: ")
    number_int = int(number_str)

    # AMEX
    if number_str[0:2] in ["34", "37"]:
        if len(number_str) == 15 and luhn(number_int) == True:
            print("AMEX")
        else:
            print("INVALID")

    # MASTERCARD
    elif number_str[0:2] in ["51", "52", "53", "54", "55"]:
        if len(number_str) == 16 and luhn(number_int) == True:
            print("MASTERCARD")
        else:
            print("INVALID")

    # VISA
    elif number_str[0] == "4":
        if len(number_str) in [13, 16] and luhn(number_int) == True:
            print("VISA")
        else:
            print("INVALID")

    # INVALID
    else:
        print("INVALID")


def luhn(number):
    total = 0
    add = 0
    places = 1

    # Caculate for the final sum value
    while number != 0:
        if places % 2 != 0:
            add = number % 10
        else:
            add = (number % 10) * 2
            if add >= 10:
                add = (add % 10) + (add - add % 10) / 10
        total += add
        number = (number - number % 10) / 10
        places += 1

    # Check whether the card is valid
    if total % 10 == 0:
        return True
    else:
        return False


main()