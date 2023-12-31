# TODO


# Function to check whether a string is a number
def number(card_no):
    if card_no.isnumeric():
        return 1
    else:
        return 0


# Function to check validity(numerical) of a credit card: (using Luhn’s Algorithm)
def valid(card_no):
    # the number should be atleast 2 digits long to apply this algorithm:
    no_len = len(card_no)
    if no_len < 2:
        return 0

    # Luhn’s Algorithm part 1:
    i = no_len - 2
    sopd_2 = 0
    while i >= 0:
        pdt_2 = int(card_no[i]) * 2 # note that int() will not typecast here, but convert numeric chars to corresponding ints
        sopd_2 = ((int(pdt_2 / 10) + (pdt_2 % 10)) if (pdt_2 > 9) else pdt_2) + sopd_2
        i -= 2

    # Luhn’s Algorithm part 2:
    j = no_len - 1
    sod = 0
    while j >= 0:
        sod = int(card_no[j]) + sod
        j -= 2
    final_sum = sopd_2 + sod

    # Luhn’s Algorithm part 3:
    if final_sum % 10 == 0:
        return 1
    else:
        return 0


def print_card_type(card_no):
    # Card being AMEX:
    if len(card_no) == 15 and (card_no[0:2] == "34" or card_no[0:2] == "37"):
        print("AMEX")

    # Card being MasterCard:
    elif len(card_no) == 16 and (int(card_no[0:2]) > 50 and int(card_no[0:2]) < 56):
        print("MASTERCARD")

    # Card being MasterCard:
    elif (len(card_no) == 13 or len(card_no) == 16) and (int(card_no[0]) == 4):
        print("VISA")

    # Invalid if none of these match:
    else:
        print("INVALID")



    # MAIN FUNCTION:
# Taking number as input:
card_no = "a"
while not number(card_no):
    card_no = input("Number: ")

if valid(card_no):
    print_card_type(card_no)
else:
    print("INVALID")
