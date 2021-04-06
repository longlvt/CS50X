#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy SOURCE DESTINATION");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (!source)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // CHECK IF THE SOURCE IS JPEG
    BYTE bytes[3];
    // parameters: pointed location to store data , unit of data to be read, amount of data to be read, pointed source to be read
    // NOTE: The amount of data will be moved from 'source' to 'location to store data'
    fread(&bytes, sizeof(BYTE), 3, source);
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("THIS MAYBE A JPEG\n");
        return 1;
    }
    else
    {
        printf("CONTINUE TO COPY\n");
        FILE *dest = fopen(argv[2], "w");
        if (!dest)
        {
            fclose(source);
            printf("Could not create %s\n", argv[2]);
            return 1;
        }

        // write the 3 bytes in 'bytes' to 'dest' file
        fwrite(bytes, sizeof(BYTE), 3, dest);

        BYTE buffer;
        while (fread(&buffer, sizeof(BYTE), 1, source))
        {
            fwrite(&buffer, sizeof(BYTE), 1, dest);
        }

        fclose(source);
        fclose(dest);
    }

    return 0;
}
