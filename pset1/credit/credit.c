#include <stdio.h>
#include <cs50.h>

int reversDigits(int num)
{
    int rev_num = 0;
    while(num > 0)
    {
        rev_num = rev_num*10 + num%10;
        num = num/10;
    }
    return rev_num;
}

int main(void)
{
    // PROMPT TO GET USER INPUT
    // Use get_long to check the length
    long int cardNum;
    do
    {
        cardNum = get_long("Number: ");
    }
    while (cardNum < 4);

    // REVERT NUMBER
    // int revertNum = reversDigits(cardNum);
    // printf("THIS IS REVERTED NUMBER: %i\n", revertNum);

    // GET EVERY DIGITS IN THE NUMBER
    int length = 0;
    int evenSum = 0;
    int oddMul2 = 0;
    int oddSum = 0;
    int digit;
    int checkSum;
    int lastDigit;
    int last2Digits;
    bool valid = true;
    while(cardNum)
    {
        // Get each digit
        digit = cardNum % 10;

        // Get SUM of odd digits
        if (length % 2 == 1)
        {
            // Multiply digit by 2
            oddMul2 = digit * 2;

            // If result of multiply large than9, get sum of each digits.
            if (oddMul2 > 9)
            {
                while(oddMul2)
                {
                    int subDigit = oddMul2 % 10;
                    oddSum += subDigit;
                    oddMul2 /= 10;
                }
            }
            else oddSum += oddMul2;
        }
        else
        {
            evenSum += digit;
        }
        length ++;

        // Get last 2 digits
        if (cardNum < 100 && cardNum > 9)
        {
            if (cardNum == 34 || cardNum == 37 || (cardNum > 50 && cardNum < 56))
            {
                last2Digits = cardNum;
            }

            // Get last digit
            else if (cardNum > 39 && cardNum < 50)
            {
                lastDigit = 4;
            }
            else
            {
                valid = false;
                break;
            }
        }

        cardNum /= 10;
    }

    if (valid)
    {
        // GET CHECKSUM
        checkSum = oddSum + evenSum;

        // CHECK IF '0' IS THE LAST DIGIT IN CHECK SUM
        valid = ((checkSum % 10) == 0) && length > 12;
    }

    // SHOW RESULT
    if (valid == 1 && length == 15 && (last2Digits == 34 || last2Digits == 37))
    {
        printf("AMEX\n");
    }
    else if (valid == 1 && length == 16 && (last2Digits > 50 && last2Digits < 56))
    {
        printf("MASTERCARD\n");
    }
    else if (valid == 1 && (length == 13 || length == 16) && lastDigit == 4)
    {
        printf("VISA\n");
    }
    else if (valid == 0)
    {
        printf("INVALID\n");
    }

}