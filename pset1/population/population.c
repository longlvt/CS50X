#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startNum;
    do
    {
        startNum = get_int("Start size: ");
    }
    while (startNum < 9);

    // TODO: Prompt for end size
    int endNum;
    do
    {
        endNum = get_int("End size: ");
    }
    while (endNum < startNum);

    // TODO: Calculate number of years until we reach threshold
    int yearNum = 0;
    int temp = 0;
    if (startNum < endNum)
    {
        do
        {
            temp = startNum + startNum / 3 - startNum / 4;
            startNum = temp;
            yearNum ++;
        }
        while (temp < endNum);
    }

    // TODO: Print number of years
    printf("Years: %i\n", yearNum);
}