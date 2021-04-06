#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>

typedef uint8_t BYTE;

bool check_header(BYTE *bytes);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open raw data
    FILE *source = fopen(argv[1], "r");
    if (!source)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    int destNum = 0, jpegCount = 0;
    bool fileWriting = false;

    // Open a new file to write
    char destName[7];
    sprintf(destName, "%03i.jpg", destNum);

    FILE *dest;
    dest = fopen(destName, "w");

    // Read data from raw input data block-by-block
    BYTE dataByte[512];
    while (fread(dataByte, sizeof(BYTE), 512, source))
    {
        // // Read Header from input raw data

        // Check for JPEG Header
        if (check_header(dataByte)) // If JPEG Header found
        {
            // Check if it's the first JPEG?
            if (jpegCount == 0) // If yes
            {
                printf("+ FIRST JPEG: %s\n", destName);

                // Write data to JPEG file
                fwrite(dataByte, sizeof(BYTE), 512, dest);

                // Indicate that there's a JPEG already existing.
                jpegCount++;

                // Mark as writing JPEG in progress.
                fileWriting = true;
            }
            else // If a JPEG already found
            {
                printf("+ ANOTHER JPEG, PREVIOUS ONE IS: %s\n", destName);
                // Close previous JPEG file
                fclose(dest);

                // Increase number of JPEG for the next write
                destNum ++;

                // Open a new file to write
                sprintf(destName, "%03i.jpg", destNum);
                printf("+ NEW JPEG: %s\n", destName);
                dest = fopen(destName, "w");

                // Write header
                // fwrite(headerBytes, sizeof(BYTE), 4, dest);

                // Write data to JPEG file
                fwrite(dataByte, sizeof(BYTE), 512, dest);

                // Mark as writing JPEG in progress.
                fileWriting = true;
            }
            printf("======================================================\n");
        }
        // If there's a file already open for write, then continue writing
        else if (fileWriting)
        {
            printf("IN PROGRESS WITH: %s\n", destName);
            // Write data to JPEG file
            fwrite(dataByte, sizeof(BYTE), 512, dest);
        }
    }

    // Close source data
    fclose(source);
    return 0;
}

bool check_header(BYTE *bytes)
{
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
    {
        printf("========= GET A NEW JPEG MATCHED =========\n");
        return true;
    }
    return false;
}