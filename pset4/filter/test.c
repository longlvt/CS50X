#include <math.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

#include "helpers.h"

RGBTRIPLE pixel(int r, int g, int b);
void print_pixel(RGBTRIPLE p);

int main(void)
{
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int height = 3, width = 3;
    RGBTRIPLE newImage[3][3];
    RGBTRIPLE img4[3][3];
    img4[0][0] = pixel(0, 10, 25);
    img4[0][1] = pixel(0, 10, 30);
    img4[0][2] = pixel(40, 60, 80);
    img4[1][0] = pixel(20, 30, 90);
    img4[1][1] = pixel(30, 40, 100);
    img4[1][2] = pixel(80, 70, 90);
    img4[2][0] = pixel(20, 20, 40);
    img4[2][1] = pixel(30, 10, 30);
    img4[2][2] = pixel(50, 40, 10);
    printf("ORIGINAL ONE:\n");
    for (int rowCount = 0; rowCount < 3; rowCount++)
    {
        for (int colCount = 0; colCount < 3; colCount++)
        {
            print_pixel(img4[rowCount][colCount]);
        }
        printf("\n");
    }
    for (int row = 0; row < height; row++)
    {
        // Determine the number of rows in 3x3 matrix
        int rowUp = row - 1, rowDown = row + 1;
        for (int col = 0; col < width; col++)
        {
            int colLeft = col - 1, colRight = col + 1;
            int GxBlue = 0, GxGreen = 0, GxRed = 0;
            int GyBlue = 0, GyGreen = 0, GyRed = 0;
            if (row == 0 && col == 2)
            {
                printf("BOUNDARY_ROWS: %i to %i, BOUNDARY_COLS: %i to %i\n", rowUp, rowDown, colLeft, colRight);
            }
            for (int id = rowUp; id <= rowDown; id++)
            {
                for (int idx = colLeft; idx <= colRight; idx++)
                {
                    if (id >= 0 && id < height && idx >= 0 && idx < width)
                    {
                        if (row == 0 && col == 2) {
                            printf("++++++++++++++++++++++++++++++++++++\n");
                            printf("VALUE TO GET: [%i][%i]: R-%i, G-%i, B-%i\n", id, idx, img4[id][idx].rgbtBlue, img4[id][idx].rgbtGreen, img4[id][idx].rgbtRed);
                            printf("Gx[%i][%i]: %i\n", id - rowUp, idx - colLeft, Gx[id - rowUp][idx - colLeft]);
                            printf("Gy[%i][%i]: %i\n", id - rowUp, idx - colLeft, Gy[id - rowUp][idx - colLeft]);
                            printf("====================================\n");
                        }

                        // Calculate values of each channel follow Gx
                        GxBlue += (img4[id][idx].rgbtBlue * Gx[id - rowUp][idx - colLeft]);
                        GxGreen += (img4[id][idx].rgbtGreen * Gx[id - rowUp][idx - colLeft]);
                        GxRed += (img4[id][idx].rgbtRed * Gx[id - rowUp][idx - colLeft]);

                        // Calculate values of each channel follow Gy
                        GyBlue += (img4[id][idx].rgbtBlue * Gy[id - rowUp][idx - colLeft]);
                        GyGreen += (img4[id][idx].rgbtGreen * Gy[id - rowUp][idx - colLeft]);
                        GyRed += (img4[id][idx].rgbtRed * Gy[id - rowUp][idx - colLeft]);
                    }

                }
            }
            newImage[row][col].rgbtBlue = round(sqrt(pow(GxBlue, 2)  + pow(GyBlue, 2))) > 255 ?
                                          255 : round(sqrt(pow(GxBlue, 2)  + pow(GyBlue, 2)));
            newImage[row][col].rgbtGreen = round(sqrt(pow(GxGreen, 2)  + pow(GyGreen, 2))) > 255 ?
                                           255 : round(sqrt(pow(GxGreen, 2)  + pow(GyGreen, 2)));
            newImage[row][col].rgbtRed = round(sqrt(pow(GxRed, 2)  + pow(GyRed, 2))) > 255 ?
                                         255 : round(sqrt(pow(GxRed, 2)  + pow(GyRed, 2)));
        }
    }
    for (int rowCount = 0; rowCount < 3; rowCount++)
    {
        for (int colCount = 0; colCount < 3; colCount++)
        {
            img4[rowCount][colCount] = newImage[rowCount][colCount];
        }
    }
    printf("AFTER CALCULATE:\n");
    for (int rowCount = 0; rowCount < 3; rowCount++)
    {
        for (int colCount = 0; colCount < 3; colCount++)
        {
            print_pixel(img4[rowCount][colCount]);
        }
        printf("\n");
    }
}


RGBTRIPLE pixel(int r, int g, int b)
{
    RGBTRIPLE p;
    p.rgbtRed = r;
    p.rgbtGreen = g;
    p.rgbtBlue = b;
    return p;
}
void print_pixel(RGBTRIPLE p)
{
    printf("%i %i %i\n", p.rgbtRed, p.rgbtGreen, p.rgbtBlue);
}