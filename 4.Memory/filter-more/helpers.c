#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
     int average = 0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        RGBTRIPLE tmp;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int neighbor_count = 0;

            // Iterate around neighboring pixels
            for (int h = -1; h <= 1; h++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    int nb_i = i + h;
                    int nb_j = j + w;

                    // Check neighbors
                    if (nb_i >= 0 && nb_i < height && nb_j >= 0 && nb_j < width)
                    {
                        // The color value of the outer edge is set to 0
                        red_sum += copy[nb_i][nb_j].rgbtRed;
                        green_sum += copy[nb_i][nb_j].rgbtGreen;
                        blue_sum += copy[nb_i][nb_j].rgbtBlue;

                        neighbor_count++;
                    }
                }
            }

            // Compute average and update pixel
            image[i][j].rgbtRed = round((float) red_sum / neighbor_count);
            image[i][j].rgbtGreen = round((float) green_sum / neighbor_count);
            image[i][j].rgbtBlue = round((float) blue_sum / neighbor_count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
       // Kenels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red, green, blue;
            int gx_red = 0, gy_red = 0;
            int gx_green = 0, gy_green = 0;
            int gx_blue = 0, gy_blue = 0;
            // Iterate around neighboring pixels
            for (int h = -1; h <= 1; h++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    int pi = i + h;
                    int pj = j + w;

                    // The color value of the outer edge is set to 0
                    red = green = blue = 0;
                    if (pi >= 0 && pi < height && pj >= 0 && pj < width)
                    {
                        red = copy[pi][pj].rgbtRed;
                        green = copy[pi][pj].rgbtGreen;
                        blue = copy[pi][pj].rgbtBlue;
                    }

                    // Compute x and y
                    gx_red += Gx[h + 1][w + 1] * red;
                    gy_red += Gy[h + 1][w + 1] * red;
                    gx_green += Gx[h + 1][w + 1] * green;
                    gy_green += Gy[h + 1][w + 1] * green;
                    gx_blue += Gx[h + 1][w + 1] * blue;
                    gy_blue += Gy[h + 1][w + 1] * blue;
                }
            }

            // Compute color distance
            int dRed = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int dGreen = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int dBlue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // Update pixel
            image[i][j].rgbtRed = (dRed > 255) ? 255 : dRed;
            image[i][j].rgbtGreen = (dGreen > 255) ? 255 : dGreen;
            image[i][j].rgbtBlue = (dBlue > 255) ? 255 : dBlue;
        }
    }


    return;
}
