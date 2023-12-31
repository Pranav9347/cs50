#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float p = image[i][j].rgbtBlue;
            float q = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;
            float average = (p + q + r) / 3;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a = image[i][j].rgbtBlue;
            int b = image[i][j].rgbtGreen;
            int c = image[i][j].rgbtRed;
//Algorithm for applying sepia filter:
            if ((.272 * c + .534 * b + .131 * a) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            if ((.349 * c + .686 * b + .168 * a) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            if ((.393 * c + .769 * b + .189 * a) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                float f = .272 * c + .534 * b + .131 * a ;
                float g = .349 * c + .686 * b + .168 * a;
                float h = .393 * c + .769 * b + .189 * a;

                image[i][j].rgbtBlue = round(f);
                image[i][j].rgbtGreen = round(g);
                image[i][j].rgbtRed = round(h);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < ((width - 1) / 2); j++)
            {

            // To swap the pixel in jth position with the opposite one if width is an odd number:
                BYTE x = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][(width - (j + 1))].rgbtBlue;
                image[i][(width - (j + 1))].rgbtBlue = x;

                BYTE y = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][(width - (j + 1))].rgbtGreen;
                image[i][(width - (j + 1))].rgbtGreen = y;

                BYTE z = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][(width - (j + 1))].rgbtRed;
                image[i][(width - (j + 1))].rgbtRed = z;
            }
        }
    }
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {

            for (int j = 0; j < ((width) / 2); j++)
            {

                  // To swap the pixel in jth position with the opposite one if width is an even number:
                BYTE x = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][(width - (j + 1))].rgbtBlue;
                image[i][(width - (j + 1))].rgbtBlue = x;

                BYTE y = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][(width - (j + 1))].rgbtGreen;
                image[i][(width - (j + 1))].rgbtGreen = y;

                BYTE z = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][(width - (j + 1))].rgbtRed;
                image[i][(width - (j + 1))].rgbtRed = z;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // For Blue pixels:
    RGBTRIPLE blurimage[height][width];
    float average = 0;
    int m, n, w;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            w = 0;

            for (m = -1; m < 2; m++)
            {
                if (i + m < 0)
                {
                    m = 0;
                }
                for (n = -1; n < 2; n++, w++)
                {
                    if (j + n < 0)
                    {
                        n = 0;
                    }
                    average = average + image[i + m][j + n].rgbtBlue;
                    if (j + n == width)
                    {
                        break;
                    }
                }
                //Preventing segmentation faults
                if (i + m == height)
                {
                    break;
                }

            }
            blurimage[i][j].rgbtBlue = round(average / w);
        }
    }
    //Assigning the new blurred pixel to the output pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurimage[i][j].rgbtBlue;
        }
    }

// For Green pixels:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            w = 0;

            for (m = -1; m < 2; m++)
            {
                if (i + m < 0)
                {
                    m = 0;
                }
                for (n = -1; n < 2; n++, w++)
                {
                    if (j + n < 0)
                    {
                        n = 0;
                    }
                    average = average + image[i + m][j + n].rgbtGreen;
                    if (j + n == width)
                    {
                        break;
                    }
                }
                if (i + m == height)
                {
                    break;
                }

            }
            blurimage[i][j].rgbtGreen = round(average / w);
        }
    }
    //Assigning the new blurred pixel to the output pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = blurimage[i][j].rgbtGreen;
        }
    }
    // For Red pixels:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            w = 0;

            for (m = -1; m < 2; m++)
            {
                if (i + m < 0)
                {
                    m = 0;
                }
                for (n = -1; n < 2; n++, w++)
                {
                    if (j + n < 0)
                    {
                        n = 0;
                    }
                    average = average + image[i + m][j + n].rgbtRed;
                    if (j + n == width)
                    {
                        break;
                    }
                }
                //Preventing segmentation faults
                if (i + m == height)
                {
                    break;
                }

            }
            blurimage[i][j].rgbtRed = round(average / w);
        }
    }
    //Assigning the new blurred pixel to the output pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurimage[i][j].rgbtRed;
        }
    }
    return;
}
