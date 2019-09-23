#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "imageUtils.h"
#include "colorUtils.h"

Pixel **loadImage(const char *filePath, int *height, int *width) {
  int x,y,n;
  unsigned char *data = stbi_load(filePath, &x, &y, &n, 4); //4 = force RGBA channels
  *height = y;
  *width = x;

  //contiguous allocation:
  Pixel **image = (Pixel **)malloc(sizeof(Pixel *) * y);
  image[0] = (Pixel *)malloc(sizeof(Pixel) * (y * x));
  for(int i=1; i<y; i++) {
    image[i] = (*image + (x * i));
  }

  int rowIndex = 0;
  int colIndex = 0;
  for(int i=0; i<(x * y * 4); i+=4) { //for each row
      image[rowIndex][colIndex].red   = data[i+0];
      image[rowIndex][colIndex].green = data[i+1];
      image[rowIndex][colIndex].blue  = data[i+2];
      colIndex++;
      if(colIndex == x) {
        //go to next row, reset column
        rowIndex++;
        colIndex=0;
      }
  }
  stbi_image_free(data);
  return image;
}

void saveImage(const char *fileName, Pixel **image, int height, int width) {

  // Convert height x width Pixel array to single array with
  // 3 (RGB) channels, ignoring the alpha channel and assume 100% opaque
  unsigned char *data = (unsigned char *) malloc(height * width * 3);
  int x = 0;
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      data[x+0] = image[i][j].red;
      data[x+1] = image[i][j].green;
      data[x+2] = image[i][j].blue;
      x+=3;
    }
  }
  //write
  stbi_write_jpg(fileName, width, height, 3, data, 100);
  free(data);
  return;
}

Pixel ** copyImage(Pixel **image, int height, int width) {
  Pixel **copy = (Pixel **)malloc(sizeof(Pixel *) * height);
  copy[0] = (Pixel *)malloc(sizeof(Pixel) * (height * width));
  for(int i=1; i<height; i++) {
    copy[i] = (*copy + (width * i));
  }

  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      copy[i][j] = image[i][j];
    }
  }
  return copy;
}

void imageToGrayScale(Pixel **image, int height, int width, Mode m) {

  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      toGrayScale(&image[i][j].red,
				      &image[i][j].green,
				      &image[i][j].blue, m);
    }
  }
  return;
}

void imageToSepia(Pixel **image, int height, int width) {
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      toSepia(&image[i][j].red,
				      &image[i][j].green,
				      &image[i][j].blue);
    }
  }
  return;
}
