#include "helpers.h"
#include "math.h"

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
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int newBlue, newGreen, newRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            newGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            newBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (newRed > 255)
            {
                newRed = 255;
            }
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
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
            // Form a 3x3 box
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            cell_count = 0;
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
