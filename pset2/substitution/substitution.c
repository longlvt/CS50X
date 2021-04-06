#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string encrypt(string text, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int len = strlen(argv[1]);

    // CHECK if key not containing 26 characters
    if (len < 26 || len > 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // CHECK if key containing any character that is not an alphabetic character
    for (int id = 0; argv[1][id] != '\0'; id ++)
    {
        int key_ascii = (int) argv[1][id];
        if (key_ascii < 65 || key_ascii > 123  || (key_ascii > 90 && key_ascii < 97))
        {
            printf("Key should not contain number.\n");
            return 1;
        }
    }
    // CHECK if key not containing each letter exactly once
    for (int idx = 0; idx < (len - 1); idx ++)
    {
        for (int e = idx + 1; e < len; e ++)
        {
            if (argv[1][idx] == argv[1][e])
            {
                printf("Duplicated characters in key.\n");
                return 1;
            }
        }
    }
    string plain = get_string("plaintext: ");
    string cipher = encrypt(plain, argv[1]);
    printf("ciphertext: %s\n", cipher);
    return 0;

}

string encrypt(string text, string key)
{
    // TODO: ENCRYPT THE TEXT WITH THE GIVEN KEY
    string encryptedText = text;
    int index;
    for (int i = 0; text[i] != '\0'; i ++)
    {
        int char_ascii = (int) text[i];
        if ((char_ascii >= 65 && char_ascii <= 90) || (char_ascii >= 97 && char_ascii <= 122))
        {
            if (char_ascii >= 65 && char_ascii <= 90)
            {
                index = char_ascii - 65;
                encryptedText[i] = toupper(key[index]);
            }
            else
            {
                index = char_ascii - 97;
                encryptedText[i] = tolower(key[index]);
            }
        }
        else
        {
            encryptedText[i] = text[i];
        }

    }
    return encryptedText;
}
