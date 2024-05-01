#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
        int average=0;
        //Loop over pixels;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                //Take average of red,green,and blue
             average =round((image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue) / 3.0);
            //  Update pixel values
            image[i][j].rgbtRed =average;
            image[i][j].rgbtGreen =average;
            image[i][j].rgbtBlue= average;
            }
        }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
       int sepiaRed, sepiaGreen, sepiaBlue;
    for(int i= 0;i<height;i++){
        for(int j=0;j<width; j++){
            //comute sepia values
           sepiaRed = round(.393 *   image[i][j].rgbtRed+ .769 * image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue);
           sepiaGreen = round(.349 *   image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen  + .168 * image[i][j].rgbtBlue);
           sepiaBlue = round(.272 *   image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen  + .131 * image[i][j].rgbtBlue);
            //update pixel with sepia values
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
      // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp=image[i][j];
             image[i][j]=image[i][width-1-j];
             image[i][width-1-j]=temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of image
    RGBTRIPLE copy[height][width];
    for(int i= 0;i<height;i++){
        for(int j=0;j<width;j++){
            copy[i][j]=image[i][j];
        }
    }
     for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
        int red_sum = 0, green_sum = 0, blue_sum = 0;
        int neighbor_count = 0;
          for(int h=-1;h<=1;h++){
            for(int w=-1;w<=1;w++){
                 int nb_i=i+h;
                 int nb_j=j+w;
             if (nb_i >= 0 && nb_i < height && nb_j >= 0 && nb_j < width)
                {
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
