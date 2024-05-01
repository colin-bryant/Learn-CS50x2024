

def main():
    s = str(get_int())

    if not luhn_check(s):
        print("INVALID")
        return
    # Check bank-card 银行卡
    # By first two/one digits
    if s[:2] == '34' or s[:2] == '37':
        print("AMEX")
    elif s[:2] == '51' or s[:2] == '52' or s[:2] == '53' or s[:2] == '54' or s[:2] == '55':
        print("MASTERCARD")
    elif s[:1] == '4' and (len(s) == 13 or len(s) == 16):
        print("VISA")
    else:
        print("INVALID")

    return

    return


def get_int():
    while True:
        try:
            numbers=int(input("Numbers: "))
        except ValueError:
            continue
        if numbers > 0:
            break
    return numbers



# define luhn_check algorithms
def luhn_check(numbers):
    sum = 0
    for i in range(len(numbers)-1,-1,-2):
        # Odd digit
        sum += int(numbers[i])
    for i in range(len(numbers)-2,-1,-2):
        # Even digit
        value = int(numbers[i]) * 2
        if value >= 10 :
            sum += 1
            sum += value % 10
        else:
            sum += value
    return sum % 10 == 0

if __name__ == "__main__":
    main()
