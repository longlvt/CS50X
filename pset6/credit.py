from cs50 import get_int

cardNum = 0
while (cardNum < 4):
    cardNum = get_int("Number: ")

print(f"Your number: {cardNum}")
digitsList = [34, 37, 50, 51, 52, 53, 54, 55]
list4 = [39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]

length = 0
oddSum = 0
evenSum = 0
valid = True
last2Digits = 0
lastDigit = 0
while (cardNum):
    digit = cardNum % 10
    if (length % 2 == 1):
        oddMul = digit * 2
        if(oddMul > 9):
            while (oddMul):
                subDigit = oddMul % 10
                oddSum += subDigit
                oddMul //= 10
        else:
            oddSum += oddMul
    else:
        evenSum += digit
    length += 1

    # Get first 2 digits
    if (cardNum < 100 and cardNum > 9):
        if (cardNum in digitsList):
            last2Digits = cardNum
        elif (cardNum in list4):
            lastDigit = 4
        else:
            valid = False
            break
    cardNum //= 10

# Check valid
if (valid == True):
    checkSum = oddSum + evenSum
    valid = ((checkSum % 10) == 0) and length > 12

# SHOW RESULT
if (valid == True and length == 15 and (last2Digits == 34 or last2Digits == 37)):
    print("AMEX")
elif (valid == True and length == 16 and (last2Digits > 50 and last2Digits < 56)):
    print("MASTERCARD")
elif (valid == True and length == 13 or length == 16 and lastDigit == 4):
    print("VISA")
elif (valid == False):
    print("INVALID")

