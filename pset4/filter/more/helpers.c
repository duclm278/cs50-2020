#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum, average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            average = round((float) sum / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = (width - 1) / 2; j <= n; j++)
        {
            tmp.rgbtBlue = image[i][j].rgbtBlue;
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            tmp.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = tmp.rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = tmp.rgbtGreen;
            image[i][width - 1 - j].rgbtRed = tmp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Add new color of each pixel to tmp
    RGBTRIPLE tmp[height][width];
    int sumBlue, sumGreen, sumRed, cell_count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            cell_count = 0;

            // Form a 3x3 box
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        sumBlue += image[k][l].rgbtBlue;
                        sumGreen += image[k][l].rgbtGreen;
                        sumRed += image[k][l].rgbtRed;
                        cell_count++;
                    }
                }
            }

            tmp[i][j].rgbtBlue = round((float) sumBlue / cell_count);
            tmp[i][j].rgbtGreen = round((float) sumGreen / cell_count);
            tmp[i][j].rgbtRed = round((float) sumRed / cell_count);
        }
    }

    // Copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Gx && Gy
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    // Add new color of each pixel to tmp
    RGBTRIPLE tmp[height][width];
    int sumGxBlue, sumGxGreen, sumGxRed;
    int sumGyBlue, sumGyGreen, sumGyRed;
    int Blue, Green, Red;
    int G_count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumGxBlue = 0;
            sumGxGreen = 0;
            sumGxRed = 0;

            sumGyBlue = 0;
            sumGyGreen = 0;
            sumGyRed = 0;
            
            G_count = 0;

            // Form a 3x3 box
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        sumGxBlue += image[k][l].rgbtBlue * Gx[G_count];
                        sumGxGreen += image[k][l].rgbtGreen * Gx[G_count];
                        sumGxRed += image[k][l].rgbtRed * Gx[G_count];
                        
                        sumGyBlue += image[k][l].rgbtBlue * Gy[G_count];
                        sumGyGreen += image[k][l].rgbtGreen * Gy[G_count];
                        sumGyRed += image[k][l].rgbtRed * Gy[G_count];
                    }
                    G_count++;
                }
            }

            // Combine Gx and Gy into a single value
            Blue = round(sqrt(sumGxBlue * sumGxBlue + sumGyBlue * sumGyBlue));
            Green = round(sqrt(sumGxGreen * sumGxGreen + sumGyGreen * sumGyGreen));
            Red = round(sqrt(sumGxRed * sumGxRed + sumGyRed * sumGyRed));
            
            // Make sure values are capped at 255
            if (Blue > 255)
            {
                tmp[i][j].rgbtBlue = 255;
            }
            else
            {
                tmp[i][j].rgbtBlue = Blue;
            }
            if (Green > 255)
            {
                tmp[i][j].rgbtGreen = 255;
            }
            else
            {
                tmp[i][j].rgbtGreen = Green;
            }
            if (Red > 255)
            {
                tmp[i][j].rgbtRed = 255;
            }
            else
            {
                tmp[i][j].rgbtRed = Red;
            }
        }
    }

    // Copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}
