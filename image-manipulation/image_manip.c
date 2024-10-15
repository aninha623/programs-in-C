#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "image_manip.h"
#include "ppm_io.h"
#define max(x,y) ((x)>(y) ? (x) : (y)) //for some reason, max/min not working right even tho math.h is imported
#define min(x,y) ((x)<(y) ? (x) : (y))


////////////////////////////////////////
// Definitions of the functions       //
// declared in image_manip.h go here! //
////////////////////////////////////////

//______grayscale______
/* convert an image to grayscale (NOTE: pixels are still
* RGB, but the three values will be equal)
*/
Image grayscale( const Image in ){
    //create new img to be returned
    Image out = make_image(in.rows, in.cols); 

    //error handling: error in making output image
    if (!out.data){
        fprintf(stderr, "Failed to allocate memory for output image.\n");
        out.rows = 0;
        out.cols = 0;
        out.data = NULL;
        return out;
    }
    
    //take dimensions of image
    int dimensions = in.rows * in.cols;

    //iterate through every pixel
    for (int index =0; index<dimensions; index++){

        //variables to store color data temporarily
        double red = (in.data[index].r*0.3);
        double green = (in.data[index].g * 0.59);
        double blue = (in.data[index].b * 0.11);
        unsigned char gray = (unsigned char) (red + green + blue);

        //populate output image color channels
        out.data[index].r = gray;
        out.data[index].g = gray;
        out.data[index].b = gray;
    }

    return out;
}

/* _______alpha blend________
* blend two images into one using the given alpha factor
*/
Image blend( const Image in1, const Image in2 , double alpha ){

    //take dimensions for new img
    int new_rows = max(in1.rows, in2.rows);
    int new_cols = max(in1.cols, in2.cols);

    int affected_rows = min(in1.rows, in2.rows);
    int affected_cols = min(in1.cols, in2.cols);

    //create new img
    Image out = make_image(new_rows, new_cols);

    //error handling: error in making output image
    if (!out.data){
        fprintf(stderr, "Failed to allocate memory for output image.\n");
        out.rows = 0;
        out.cols = 0;
        out.data = NULL;
        return out;
    }

    //loop through each pixel for dimensions where blend will be applied
    for (int row=0; row<new_rows; row++){
        for (int column=0; column<new_cols; column++){
            
            //variables to store color data temporarily
            double red = 0;
            double green = 0;
            double blue = 0;

            //current index
            int index1 = (row*in1.cols) + column;
            int index2 = (row*in2.cols) + column;
            int index = (row*new_cols) + column;

            //modify overlapping area of images
            if ((row < affected_rows) && (column < affected_cols)){
                //multiply all color channels by alpha value for image 1
                red = red + (in1.data[index1].r * alpha);
                green = green + (in1.data[index1].g * alpha);
                blue = blue + (in1.data[index1].b * alpha);

                //multiply all color channels by alpha value for image 2
                red = red + (in2.data[index2].r * (1-alpha));
                green = green + (in2.data[index2].g * (1-alpha));
                blue = blue + (in2.data[index2].b * (1-alpha));

                //fix bounds just in case the pixel is negative or greater than 255
                if (red < 0){
                    red = 0;
                }
                else if (red > 255){
                    red = 255;
                }
                if (green < 0){
                    green = 0;
                }
                else if (green > 255){
                    green = 255;
                }
                if (blue < 0){
                    blue = 0;
                }
                else if (blue > 255){
                    blue = 255;
                }

                //cast red green and blue back into unsigned char
                red = (unsigned char) red;
                green = (unsigned char) green;
                blue = (unsigned char) blue;

                //populate output image
                out.data[index].r = red;
                out.data[index].g = green;
                out.data[index].b = blue;
            }

            //if any part of the image is greater than whatever overlap there is
            // in1 > in2
            else if (row < in1.rows && column < in1.cols){
                out.data[index].r = in1.data[index1].r;
                out.data[index].g = in1.data[index1].g;
                out.data[index].b = in1.data[index1].b;
            }   
            // in2 > in1
            else if (row < in2.rows && column < in2.cols){
                out.data[index].r = in2.data[index2].r;
                out.data[index].g = in2.data[index2].g;
                out.data[index].b = in2.data[index2].b;
            }
            
        }
    }

    return out;
}

/* _______rotate-ccw________
* rotate the input image counter-clockwise
*/
Image rotate_ccw( const Image in){

    //take dimensions of in
    int og_rows = in.rows;
    int og_cols = in.cols;
    //create new image
    Image out = make_image(og_cols, og_rows);

    //error handling: error in making output image
    if (!out.data){
        fprintf(stderr, "Failed to allocate memory for output image.\n");
        out.rows = 0;
        out.cols = 0;
        out.data = NULL;
        return out;
    }

    //loop through dimensions of original image
    for (int row = 0; row<og_cols; row++){
        for (int column = 0; column<og_rows; column++){

            //populate out image
            out.data[(((og_cols - 1 - row) * og_rows) + column)] = in.data[((og_cols * column) + row)];
            
        }
    }
    return out;

}
/* _______pointilism________
* apply a painting like effect i.e. poitilism technique.
*/
Image pointilism( const Image in , unsigned int seed ){

    //take dimensions of in
    int rows = in.rows;
    int columns = in.cols;
    //create new image
    Image out = make_image(rows, columns);

    //error handling: error in making output image
    if (!out.data){
        fprintf(stderr, "Failed to allocate memory for output image.\n");
        out.rows = 0;
        out.cols = 0;
        out.data = NULL;
        return out;
    }

    //take 3% of image
    int total_size = rows * columns;
    int centers = (int)(total_size * .03);

    //set seed
    srand(seed);

    //loop for 3% of total image pixels
    for (int pixel =0; pixel<centers; pixel++){
        //take random selections
        int point_center = (rand() % total_size); //randomly select a pixel to be the center
        int radius = ((rand() % 5) + 1); // random radius between 1 and 5

        //represent point_center as a coordinate
        Point center;
        center.x = point_center % columns; //remainder of point_center divided by columns = column coordinate
        center.y = point_center / columns; //point_center divided by columns gives the row coordinate

        Pixel center_pixel = in.data[center.y*columns + center.x];

        //assign neighboring pixels radially outwards to be the same
        //rgb values as the randomized center
        switch (radius){
        case 1:
            //iterate row index, handling edge cases
            for (int row = max(0, (center.y-1)); row < min(rows, (center.y + 2)); row++){
                //iterate column index
                for (int column =max(0, (center.x-1)); column < min(columns, (center.x + 2)); column++){
                    
                    //take distances from the current pixel and the center pixel
                    int horizontal = column - center.x; //horizontal distance from center
                    int vertical = row - center.y; //vertical distance from pixel
                    
                    //check bounds
                    if ((((horizontal*horizontal)+(vertical*vertical))^(1/2)) <= (1)){
                        //find current pixel index
                        int position = ((row* columns) + column);
                        //assign neighboring pixel rbg values to be the same as the center
                        out.data[position] = center_pixel;
                        }
                    }
                }

            break;
        case 2:
            //iterate row index, handling edge cases
            for (int row =max(0, (center.y-2)); row < min(rows, (center.y + 3)); row++){
                //iterate column index
                for (int column =max(0, (center.x-2)); column < min(columns, (center.x + 3)); column++){
                    
                    //take distances from the current pixel and the center pixel
                    int horizontal = column - center.x; //horizontal distance from center
                    int vertical = row - center.y; //vertical distance from pixel
                    
                    //check bounds
                    if ((((horizontal*horizontal)+(vertical*vertical))^(1/2)) <= (4)){
                        //find current pixel index
                        int position = ((row* columns) + column);
                        //assign neighboring pixel rbg values to be the same as the center
                        out.data[position] = center_pixel;
                        }
                    }
                }

            break;
        case 3:
            //iterate row index, handling edge cases
            for (int row =max(0, (center.y-3)); row < min(rows, (center.y + 4)); row++){
                //iterate column index
                for (int column =max(0, (center.x-3)); column < min(columns, (center.x + 4)); column++){
                    
                    //take distances from the current pixel and the center pixel
                    int horizontal = column - center.x; //horizontal distance from center
                    int vertical = row - center.y; //vertical distance from pixel
                    
                    //check bounds
                    if ((((horizontal*horizontal)+(vertical*vertical))^(1/2)) <= (9)){
                        //find current pixel index
                        int position = ((row* columns) + column);
                        //assign neighboring pixel rbg values to be the same as the center
                        out.data[position] = center_pixel;
                        }
                    }
                }
            break;
        case 4:
            //iterate row index, handling edge cases
            for (int row =max(0, (center.y-4)); row < min(rows, (center.y + 5)); row++){
                //iterate column index
                for (int column =max(0, (center.x-4)); column < min(columns, (center.x + 5)); column++){
                    
                    //take distances from the current pixel and the center pixel
                    int horizontal = column - center.x; //horizontal distance from center
                    int vertical = row - center.y; //vertical distance from pixel
                    
                    //check bounds
                    if ((((horizontal*horizontal)+(vertical*vertical))^(1/2)) <= (16)){
                        //find current pixel index
                        int position = ((row* columns) + column);
                        //assign neighboring pixel rbg values to be the same as the center
                        out.data[position] = center_pixel;
                        }
                    }
                }
            break;
        case 5:
            //iterate row index, handling edge cases
            for (int row =max(0, (center.y-5)); row < min(rows, (center.y + 6)); row++){
                //iterate column index
                for (int column =max(0, (center.x-5)); column < min(columns, (center.x + 6)); column++){
                    
                    //take distances from the current pixel and the center pixel
                    int horizontal = column - center.x; //horizontal distance from center
                    int vertical = row - center.y; //vertical distance from pixel
                    
                    //check bounds
                    if ((((horizontal*horizontal)+(vertical*vertical))^(1/2)) <= (25)){
                        //find current pixel index
                        int position = ((row* columns) + column);
                        //assign neighboring pixel rbg values to be the same as the center
                        out.data[position] = center_pixel;
                        }
                    }
                }
            break;
    }

    }
    
    return out;
}
