#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

unsigned int N = 1;
int main(void)
{
    srand ( time(NULL) );
    int randNum = rand();
    printf("RAND NUM: %i\n", randNum);
    if ((randNum % 2 == 0))
    {
        int inRand = rand();
        printf("INSIDE: %i\n", inRand);
    }
    N++;
    printf("THIS IS N: %i", N);

    char *s1 = "aaa";
    char *s2 = "AAA";
    printf("COMPARE: %i\n", strcasecmp(s1, s2));
}