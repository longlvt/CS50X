#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int newVal = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.0);
            image[row][col].rgbtBlue = image[row][col].rgbtGreen = image[row][col].rgbtRed = newVal;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0, middle = width / 2; col < middle; col++)
        {
            RGBTRIPLE temp;
            int factor = width - 1 - col;
            temp = image[row][col];
            image[row][col] = image[row][factor];
            image[row][factor] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];
    for (int row = 0; row < height; row++)
    {
        int rowUp = 0, rowDown = height - 1;
        if (row - 1 >= 0)
        {
            rowUp = row - 1;
        }
        if (row + 1 <= height - 1)
        {
            rowDown = row + 1;
        }
        for (int col = 0; col < width; col++)
        {
            int colLeft = 0, colRight = width - 1;
            if (col - 1 >= 0)
            {
                colLeft = col - 1;
            }
            if (col + 1 <= width - 1)
            {
                colRight = col + 1;
            }
            int RedSum = 0, BlueSum = 0, GreenSum = 0;
            int count = 0;
            for (int id = rowUp; id <= rowDown; id++)
            {
                for (int idx = colLeft; idx <= colRight; idx++)
                {
                    BlueSum += image[id][idx].rgbtBlue;
                    GreenSum += image[id][idx].rgbtGreen;
                    RedSum += image[id][idx].rgbtRed;
                    count ++;
                }
            }
            newImage[row][col].rgbtBlue = round(BlueSum / (float) count);
            newImage[row][col].rgbtGreen = round(GreenSum / (float) count);
            newImage[row][col].rgbtRed = round(RedSum / (float) count);
        }
    }
    for (int rowCount = 0; rowCount < height; rowCount++)
    {
        for (int colCount = 0; colCount < width; colCount++)
        {
            image[rowCount][colCount] = newImage[rowCount][colCount];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    RGBTRIPLE newImage[height][width];
    for (int row = 0; row < height; row++)
    {
        // Determine the number of rows in 3x3 matrix
        int rowUp = row - 1, rowDown = row + 1;
        for (int col = 0; col < width; col++)
        {
            int colLeft = col - 1, colRight = col + 1;
            int GxBlue = 0, GxGreen = 0, GxRed = 0;
            int GyBlue = 0, GyGreen = 0, GyRed = 0;
            for (int id = rowUp; id <= rowDown; id++)
            {
                for (int idx = colLeft; idx <= colRight; idx++)
                {
                    if (id >= 0 && id < height && idx >= 0 && idx < width)
                    {
                        // Calculate values of each channel follow Gx
                        GxBlue += (image[id][idx].rgbtBlue * Gx[id - rowUp][idx - colLeft]);
                        GxGreen += (image[id][idx].rgbtGreen * Gx[id - rowUp][idx - colLeft]);
                        GxRed += (image[id][idx].rgbtRed * Gx[id - rowUp][idx - colLeft]);

                        // Calculate values of each channel follow Gy
                        GyBlue += (image[id][idx].rgbtBlue * Gy[id - rowUp][idx - colLeft]);
                        GyGreen += (image[id][idx].rgbtGreen * Gy[id - rowUp][idx - colLeft]);
                        GyRed += (image[id][idx].rgbtRed * Gy[id - rowUp][idx - colLeft]);
                    }

                }
            }

            // Assign total values of RGB (capped at 255)
            newImage[row][col].rgbtBlue = round(sqrt(pow(GxBlue, 2)  + pow(GyBlue, 2))) > 255 ?
                                          255 : round(sqrt(pow(GxBlue, 2)  + pow(GyBlue, 2)));
            newImage[row][col].rgbtGreen = round(sqrt(pow(GxGreen, 2)  + pow(GyGreen, 2))) > 255 ?
                                           255 : round(sqrt(pow(GxGreen, 2)  + pow(GyGreen, 2)));
            newImage[row][col].rgbtRed = round(sqrt(pow(GxRed, 2)  + pow(GyRed, 2))) > 255 ?
                                         255 : round(sqrt(pow(GxRed, 2)  + pow(GyRed, 2)));
        }
    }

    // Assign new values for original image.
    for (int rowCount = 0; rowCount < height; rowCount++)
    {
        for (int colCount = 0; colCount < width; colCount++)
        {
            image[rowCount][colCount] = newImage[rowCount][colCount];
        }
    }
    return;
}
