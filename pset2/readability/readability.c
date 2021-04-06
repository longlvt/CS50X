#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    // Get input text
    string text = get_string("Text: ");
    int len = strlen(text);
    int words = 0, sentences = 0, letters = 0;
    if (len > 0)
    {
        words = 1;
    }
    for (int i = 0; text[i] != '\0'; i ++)
    {
        // Count number of words
        if (text[i] == ' ')
        {
            words ++;
        }
        // Count number of sentences
        else if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentences ++;
        }

        int char_ascii = (int) toupper(text[i]);
        if (char_ascii >= 65 && char_ascii <= 90)
        {
            letters ++;
        }
    }
    // printf("%i letters, %i words, %i sentences\n", letters, words, sentences);

    float L = letters * 100.0 / words;
    float S = sentences * 100.0 / words;
    // printf("L: %f, S: %f\n", L, S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
