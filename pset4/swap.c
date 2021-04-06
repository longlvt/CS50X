#include <stdio.h>
#include <cs50.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 10, y = 20;
    printf("BEFORE SWAPPING: x= %i, y= %i\n", x, y);
    swap(&x, &y);
    printf("AFTER SWAPPING: x= %i, y= %i\n", x, y);

}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}