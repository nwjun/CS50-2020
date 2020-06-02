#include "helpers.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int average(float sum, int divider);
void trial(int width, int height, RGBTRIPLE image[height][width],int cur_width, int cur_height, int code);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int aver;
    int sum;
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;

            aver = average(sum, 3);

            image[i][j].rgbtBlue = aver;
            image[i][j].rgbtGreen = aver;
            image[i][j].rgbtRed = aver;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int max_row = width - 1, i, j, k;
    RGBTRIPLE temp;

    for(i = 0; i < height; i++)
    {
        for(j = 0, k = max_row; j < k; j++, k--)
        {
             temp = image[i][j];
             image[i][j] = image[i][k];
             image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            trial(width, height, image, j, i, 1);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            trial(width, height, image, j, i, 2);
        }
    }

    return;
}

int average(float sum, int divider)
{
    float ave;

    ave = sum / (float)divider;

    if(((int)(ave * 10) % 10) >= 5)
        ++ave;

    return (int)ave;
}

// code 1: blur, code 2: gx, code 3: gy
void trial(int width, int height, RGBTRIPLE image[height][width],int cur_width, int cur_height, int code)
{
    bool wtest[3] = {true, true, true}, htest[3] = {true, true, true};
    int i = 0, j = 0, m = 0, n = 0, num = 0;
    int blue = 0, red = 0, green = 0;
    int blue2 = 0, red2 = 0, green2 = 0;
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    double result_blue = 0, result_green = 0, result_red = 0;
    RGBTRIPLE copy[height][width];
    
    if((cur_height - 1) < 0 )
        htest[0] = false;

    if((cur_height + 1) >= height)
        htest[2] = false;

    if((cur_width - 1) < 0)
        wtest[0] = false;

    if((cur_width + 1) >= width)
        wtest[2] = false;

    for(i = 0; i < 3 ; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(htest[i] == true && wtest[j] == true)
            {
                switch(i)
                {
                    case 0: m = (cur_height - 1); break;
                    case 1: m = cur_height; break;
                    case 2: m = (cur_height + 1); break;
                }

                switch(j)
                {
                    case 0: n = (cur_width - 1); break;
                    case 1: n = cur_width; break;
                    case 2: n = (cur_width + 1); break;
                }
                
                switch(code)
                {
                    case 1:
                    {
                        blue += image[m][n].rgbtBlue;
                        green += image[m][n].rgbtGreen;
                        red += image[m][n].rgbtRed;
                        ++num;
                    break;    
                    }
                    
                    case 2:
                    {
                        blue += (image[m][n].rgbtBlue * gx[i][j]);
                        red += (image[m][n].rgbtRed * gx[i][j]);
                        green += (image[m][n].rgbtGreen *gx[i][j]);
                        
                        blue2 += (image[m][n].rgbtBlue *gy[i][j]);
                        red2 += (image[m][n].rgbtRed *gy[i][j]);
                        green2 += (image[m][n].rgbtGreen *gy[i][j]);
                    break;
                    }
                }
            }
        }
    }
    
    switch(code)
    {
        case 1:
        {
                copy[cur_height][cur_width].rgbtBlue = average(blue, num);
                copy[cur_height][cur_width].rgbtGreen = average(green, num);
                copy[cur_height][cur_width].rgbtRed = average(red, num);
        }break;
            
        case 2: 
        {
            result_blue = average(sqrt((blue*blue + blue2*blue2)), 1);
            result_red = average(sqrt((red*red + red2*red2)), 1);
            result_green = average(sqrt((green*green + green2*green2)), 1);
            
            if(result_blue > 255)
                result_blue = 255;
            
            if(result_green > 255)
                result_green = 255;
            
            if(result_red > 255)
                result_red = 255;    
                
            copy[cur_height][cur_width].rgbtBlue = result_blue;
            copy[cur_height][cur_width].rgbtGreen = result_green;
            copy[cur_height][cur_width].rgbtRed = result_red;
            
        }break;

    }
    
    if((cur_width == (width - 1)) && (cur_height == (height - 1)))
    {
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
                image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
                image[i][j].rgbtRed = copy[i][j].rgbtRed;              
            }
        }
    }
}