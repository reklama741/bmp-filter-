#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int loop_height = 0 ; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width ; loop_width++)
        {
            float color = image[loop_height][loop_width].rgbtBlue + image[loop_height][loop_width].rgbtRed +
                          image[loop_height][loop_width].rgbtGreen;
            image[loop_height][loop_width].rgbtBlue = round(color / 3) ;
            image[loop_height][loop_width].rgbtRed = round(color / 3) ;
            image[loop_height][loop_width].rgbtGreen = round(color / 3) ;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int loop_height = 0 ; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width / 2 ; loop_width++)
        {
            RGBTRIPLE temp = image[loop_height][width - 1 - loop_width];
            image[loop_height][width - 1 - loop_width] = image[loop_height][loop_width];
            image[loop_height][loop_width] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float colorR = 0;
    float colorG = 0;
    float colorB = 0;
    int block_count;
    RGBTRIPLE image_temp[height][width];
    for (int loop_height = 0 ; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width ; loop_width++)
        {
            colorR = 0;
            colorG = 0;
            colorB = 0;
            block_count = 0;
            for (int i = loop_width - 1; i <= loop_width + 1; i++)
            {
                if (i >= 0 && i < width)
                {
                    colorB += image[loop_height][i].rgbtBlue;
                    colorR += image[loop_height][i].rgbtRed;
                    colorG += image[loop_height][i].rgbtGreen;
                    block_count++;
                    if (loop_height - 1 >=  0)
                    {
                        colorB += image[loop_height - 1][i].rgbtBlue;
                        colorR += image[loop_height - 1][i].rgbtRed;
                        colorG += image[loop_height - 1][i].rgbtGreen;
                        block_count++;
                    }
                    if (loop_height + 1 < height)
                    {
                        colorB += image[loop_height + 1][i].rgbtBlue ;
                        colorR += image[loop_height + 1][i].rgbtRed;
                        colorG += image[loop_height + 1][i].rgbtGreen;
                        block_count++;
                    }
                }
            }
            RGBTRIPLE loop;
            loop.rgbtBlue = round(colorB / block_count);
            loop.rgbtRed = round(colorR / block_count);
            loop.rgbtGreen = round(colorG / block_count);
            image_temp[loop_height][loop_width] = loop;
        }

    }
    for (int loop_height = 0; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width; loop_width++)
        {
            image[loop_height][loop_width].rgbtBlue = image_temp[loop_height][loop_width].rgbtBlue;
            image[loop_height][loop_width].rgbtRed = image_temp[loop_height][loop_width].rgbtRed ;
            image[loop_height][loop_width].rgbtGreen = image_temp[loop_height][loop_width].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float colorRx = 0;
    float colorGx = 0;
    float colorBx = 0;
    float colorRy = 0;
    float colorGy = 0;
    float colorBy = 0;
    RGBTRIPLE image_temp[height][width];
    for (int loop_height = 0 ; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width ; loop_width++)
        {
            int x1_3, x2;
            x1_3 = -2;
            x2 = -4;
            int y1_3, y2;
            y1_3 = -2;
            y2 = -4;

            colorRx = 0;
            colorGx = 0;
            colorBx = 0;
            colorRy = 0;
            colorGy = 0;
            colorBy = 0;
            for (int i = loop_width - 1; i <= loop_width + 1; i++)
            {
                x1_3++;
                x2 += 2;
                if (i >= 0 && i < width)
                {
                    colorBx += image[loop_height][i].rgbtBlue * x2;
                    colorRx += image[loop_height][i].rgbtRed * x2;
                    colorGx += image[loop_height][i].rgbtGreen * x2;
                    if (loop_height - 1 >=  0)
                    {
                        colorBx += x1_3 * image[loop_height - 1][i].rgbtBlue;
                        colorRx += x1_3 * image[loop_height - 1][i].rgbtRed;
                        colorGx += x1_3 * image[loop_height - 1][i].rgbtGreen;
                    }
                    if (loop_height + 1 < height)
                    {
                        colorBx += x1_3 * image[loop_height + 1][i].rgbtBlue ;
                        colorRx += x1_3 * image[loop_height + 1][i].rgbtRed;
                        colorGx += x1_3 * image[loop_height + 1][i].rgbtGreen;
                    }
                }

            }
            for (int i = loop_height - 1; i <= loop_height + 1; i++)
            {
                y1_3++;
                y2 += 2;
                if (i >= 0 && i < height)
                {
                    colorBy += image[i][loop_width].rgbtBlue * y2;
                    colorRy += image[i][loop_width].rgbtRed * y2;
                    colorGy += image[i][loop_width].rgbtGreen * y2;
                    if (loop_width - 1 >=  0)
                    {
                        colorBy += y1_3 * image[i][loop_width - 1].rgbtBlue;
                        colorRy += y1_3 * image[i][loop_width - 1].rgbtRed;
                        colorGy += y1_3 * image[i][loop_width - 1].rgbtGreen;
                    }
                    if (loop_width + 1 < height)
                    {
                        colorBy += y1_3 * image[i][loop_width + 1].rgbtBlue ;
                        colorRy += y1_3 * image[i][loop_width + 1].rgbtRed;
                        colorGy += y1_3 * image[i][loop_width + 1].rgbtGreen;
                    }
                }
            }
            RGBTRIPLE loop;
            loop.rgbtBlue = (sqrt(colorBx * colorBx + colorBy * colorBy) > 255) ? 255 : round(sqrt(colorBx * colorBx + colorBy * colorBy)) ;
            loop.rgbtRed = (sqrt(colorRx * colorRx + colorRy * colorRy) > 255) ? 255 : round(sqrt(colorRx * colorRx + colorRy * colorRy)) ;
            loop.rgbtGreen = (sqrt(colorGx * colorGx + colorGy * colorGy) > 255) ? 255 : round(sqrt(colorGx * colorGx + colorGy * colorGy)) ;
            image_temp[loop_height][loop_width] = loop;
        }

    }
    for (int loop_height = 0; loop_height < height; loop_height++)
    {
        for (int loop_width = 0; loop_width < width; loop_width++)
        {
            image[loop_height][loop_width].rgbtBlue = image_temp[loop_height][loop_width].rgbtBlue;
            image[loop_height][loop_width].rgbtRed = image_temp[loop_height][loop_width].rgbtRed ;
            image[loop_height][loop_width].rgbtGreen = image_temp[loop_height][loop_width].rgbtGreen;
        }
    }
    return;
}
