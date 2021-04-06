#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("You s: ");

    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return 1;
    }
    for (int j = 0; j < strlen(s) + 1; j++)
    {
        printf("Value of %i (which has address: %p): %c\n", j+1, (t+j), t[j]);
    }
    // allocate memory for a new string 't'
    // the length in memory should be enough to contain the NULL characer '/0' at the end of the string.

    // Copy every charater of 's' to 't'
    // Can use this funciton: strcpy(NewStr, SourceStr)
    for (int i = 0, n = strlen(s); i <= n; i++)
    // MUST ALSO COPY THE NULL characer '/0', so 'i' should be equal to 'n'
    {
        t[i] = s[i];
        // OR CAN USE THE OTHER WAY
        // *(t + i) = *(s + i);
    }

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // NOTE: MUST FREE MEMORY (of 'malloc') AFTER FINISH USING
    free(t);
}