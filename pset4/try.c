#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string s = "HI!";
    printf("%p\n", s);
    printf("%p\n", &s[0]);

    char *t = "HELLO!";
    printf("%p\n", t);
    printf("%p\n", &t[0]);
    printf("%c\n", t[1]);
    printf("%c\n", t[1]);

    char n[100];
    printf("TEST: %p\n", n);
    printf("TEST: %p\n", &n);

    int i = get_int("YOUR NUMBER: ");
    char str[7];
    sprintf(str, "%03i.jpg", i);
    // str = str + ".jpg";
    printf("THIS IS YOUR STRING: %s\n", str);
}