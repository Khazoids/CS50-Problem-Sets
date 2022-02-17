#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp = image[0][0].rgbtRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //Initialize a copy of the image to be blurred.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int row[] = {i - 1, i, i + 1};
            int col[] = {j - 1, j, j + 1};

            int counter = 0;

            float avg_red = 0;
            float avg_green = 0;
            float avg_blue = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int row_coords = row[k];
                    int col_coords = col[l];

                    if (row_coords >= 0 && col_coords >= 0 && row_coords < height && col_coords < width)
                    {
                        avg_red += copy[row_coords][col_coords].rgbtRed;
                        avg_green += copy[row_coords][col_coords].rgbtGreen;
                        avg_blue += copy[row_coords][col_coords].rgbtBlue;

                        counter++;
                    }
                }
            }
        image[i][j].rgbtRed = round(avg_red / counter);
        image[i][j].rgbtGreen = round(avg_green / counter);
        image[i][j].rgbtBlue = round(avg_blue / counter);

        }
    }

return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    double p_red = 0;
    double p_green = 0;
    double p_blue = 0;


    int sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int sobel_y[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };


RGBTRIPLE copy[height][width];

for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        copy[i][j] = image[i][j];
    }
}

for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        int row[] = {i - 1, i, i + 1};
        int col[] = {j - 1, j, j + 1};

        double Gx_red = 0;
        double Gx_green = 0;
        double Gx_blue = 0;

        double Gy_red = 0;
        double Gy_green = 0;
        double Gy_blue = 0;

        for (int k = 0; k < 3; k++)
        {
            for (int l = 0; l < 3; l++)
            {
                int row_coords = row[k];
                int col_coords = col[l];

                if (row_coords < 0 || row_coords >= height || col_coords < 0 || col_coords >= width)
                {
                    Gx_red += 0;
                    Gx_green += 0;
                    Gx_blue += 0;

                    Gy_red += 0;
                    Gy_green += 0;
                    Gy_blue += 0;
                }
                else
                {
                    Gx_red += copy[row[k]][col[l]].rgbtRed * sobel_x[k][l];
                    Gx_green += copy[row[k]][col[l]].rgbtGreen * sobel_x[k][l];
                    Gx_blue += copy[row[k]][col[l]].rgbtBlue * sobel_x[k][l];

                    Gy_red += copy[row[k]][col[l]].rgbtRed * sobel_y[k][l];
                    Gy_green += copy[row[k]][col[l]].rgbtGreen * sobel_y[k][l];
                    Gy_blue += copy[row[k]][col[l]].rgbtBlue * sobel_y[k][l];
                }
            }
        }


        p_red = pow(Gx_red, 2) + pow(Gy_red , 2);
        p_green = pow(Gx_green, 2) + pow(Gy_green, 2);
        p_blue = pow(Gx_blue, 2) + pow(Gy_blue, 2);


        p_red = sqrt(p_red);
        p_green = sqrt(p_green);
        p_blue = sqrt(p_blue);

        if(p_red > 255)
        {
            p_red = 255;
        }

        if (p_green > 255)
        {
            p_green = 255;
        }

        if (p_blue > 255)
        {
            p_blue = 255;
        }

        image[i][j].rgbtRed = round(p_red);
        image[i][j].rgbtGreen = round(p_green);
        image[i][j].rgbtBlue = round(p_blue);
    }
}
    return;
}
