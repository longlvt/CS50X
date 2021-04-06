#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height <= 0);

    // printf("Your choice: %i\n", height);
    for (int level = 0; level < height; level ++)
    {
        // printf("LEVEL: %i, SPACES_NUMBER: %i, HASHES_NUMBER: %i\n", level, height - 1 - level, level + 1);

        // LEFT HASHES
        // Print Spaces
        for (int spaces = 0; spaces < (height - 1 - level); spaces ++)
        {
            printf(" ");
        }

        // Print Hashses
        for (int hashes = 0; hashes < (level + 1); hashes ++)
        {
            printf("#");
        }


        // GAP
        printf("  ");

        // RIGHT HASHES// Print Hashses
        for (int hashes = 0; hashes < (level + 1); hashes ++)
        {
            printf("#");
        }
        // // Print Spaces
        // for (int spaces = 0; spaces < (height - 1 - level); spaces ++)
        // {
        //     printf(" ");
        // }
        printf("\n");
    }
}