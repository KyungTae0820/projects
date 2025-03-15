/*********************************************************************
 File:     chromakey.cpp

 Author:   KyungTae Kim

 Email address: kyungtae@usc.edu

 Usage: ./chromakey.cpp in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/
//./chromakey colbert_gs.bmp campus1.bmp 100.00 output1.bmp output2.bmp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE],
             double threshold);

void method2(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE]);

void replace(bool mask[][SIZE],
             unsigned char inImage[][SIZE][RGB],
             unsigned char bgImage[][SIZE][RGB],
             unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6)
  {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold "
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }

  if (readRGBBMP(argv[1], inputImage))
  {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage))
  {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }

  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
 
  threshold = atof(argv[3]);//I followed this from Codio instruction 
  

  // Call Method 1 Function
  method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage))
  {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }

  // Call Method 2 Function
  method2(inputImage,chromaMask);
  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);
  
  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage))
  {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }

  return 0;
}

// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE],
             double threshold)
{
  double RedSum = 0; //Variable for Sum of Red values to calculate average
  double GreenSum = 0; //Variable for Sum of Green values to calculate average
  double BlueSum = 0; //Variable for Sum of Blue values to calculate average

  for (int i = 0; i < 256; i++) //calculating row0
  {
      int RedValue = inImage[i][0][0];
      RedSum += RedValue; //adding all the row 0 Red values

      int GreenValue = inImage[i][0][1];
      GreenSum += GreenValue; //adding all the row 0 Green values

      int BlueValue = inImage[i][0][2];
      BlueSum += BlueValue; //adding all the row 0 Blue values
  }

  for (int j = 0; j < 256; j++) //calculating cloumn0
  {
    int RedValue = inImage[0][j][0];
    RedSum += RedValue; //adding all the column 0 Red values

    int GreenValue = inImage[0][j][1];
    GreenSum += GreenValue; //adding all the column 0 Green values

    int BlueValue = inImage[0][j][2];
    BlueSum += BlueValue; //adding all the column 0 Blue values
  }

  double R1 = RedSum/511.0; //For the precision, I set it as double abnd I got 512
  double G1 = GreenSum/511.0; //by adding 256 + 256 which is pixel numbers on
  double B1 = BlueSum/511.0; //but -1 because there is overlap on row 0 and column 0

  for (int i = 0; i < 256; i++)
  {
    for (int j = 0; j < 256; j++)
    {
      int R2 = inImage[i][j][0]; //R2 is the actual value of Red
      int G2 = inImage[i][j][1]; //G2 is the actual value of Green
      int B2 = inImage[i][j][2]; //B2 is the actual value of Blue
      double Dist = sqrt((R1 - R2)*(R1 -R2) + (G1 - G2)*(G1 -G2) + (B1 - B2)*(B1 -B2));
      if(threshold < Dist){
        mask[i][j] = 1; //if Distance is smaller then threshold, it is foreground so 1 
      }
      else{
        mask[i][j] = 0; //else change which is background, 0
      }
    }
  }
}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE])
{
  int RedSum = 0; //Variable for Sum of Red values to calculate average
  int GreenSum = 0; //Variable for Sum of Green values to calculate average
  int BlueSum = 0; //Variable for Sum of Blue values to calculate average

  //Belows Variables are setted to get automated threshold value
  int MaxRedValue = 0;//Variable that hold maximum Red value
  int MaxGreenValue = 0;//Variable that hold maximum Green value
  int MaxBlueValue = 0;//Variable that hold maximum Blue value

  int MinRedValue = 256;//Variable that hold maximum Red value
  int MinGreenValue = 256;//Variable that hold maximum Green value
  int MinBlueValue = 256;//Variable that hold maximum Blue value

  int numRows =3, numCols=3;//variable that can be set by user through guess 
                            //to check appropriate range
  
  //adding all the column Red,Green, and Blue values from the range of the row that I guess
  //For authomated threshold value, find maximum Red, Green, and Blue value
  //For authomateed threshold value, find minimum Red, Green, and Blue value
  for (int i = 0; i < numRows; i++)
  {
     for (int j = 0; j < 256; j++)
    {
      int RedValue = inImage[i][j][0];
      RedSum += RedValue; 
      if(MaxRedValue < RedValue){
          MaxRedValue = RedValue;
      }
      else if(MinRedValue > RedValue){
          MinRedValue = RedValue;
      }

      int GreenValue = inImage[i][j][1];
      GreenSum += GreenValue; 
      if(MaxGreenValue < GreenValue){
          MaxGreenValue = GreenValue;
      }
      else if(MinGreenValue > GreenValue ){
          MinGreenValue = GreenValue;
      }
      
      int BlueValue = inImage[i][j][2];
      BlueSum += BlueValue; 
      if(MaxBlueValue < BlueValue){
          MaxBlueValue = BlueValue;
      }
      else if(MinBlueValue > BlueValue){
          MinBlueValue = BlueValue;
      }
    }
  }
  //adding all the row Red,Green, and Blue values from the range of the column that I guess
  //For authomated threshold value, find maximum Red, Green, and Blue value
  //For authomateed threshold value, find minimum Red, Green, and Blue value
  for (int j = 0; j < numCols; j++)
  {
     for (int i = 0; i < 256; i++)
    {
      int RedValue = inImage[i][j][0];
      RedSum += RedValue;
      if(MaxRedValue < RedValue){
          MaxRedValue = RedValue;
      }
      else if(MinRedValue > RedValue){
          MinRedValue = RedValue;
      }

      int GreenValue = inImage[i][j][1];
      GreenSum += GreenValue;
      if(MaxGreenValue < GreenValue){
          MaxGreenValue = GreenValue;
      }
      else if(MinGreenValue > GreenValue){
          MinGreenValue = GreenValue;
      }
      
      int BlueValue = inImage[i][j][2];
      BlueSum += BlueValue;
      if(MaxBlueValue < BlueValue){
          MaxBlueValue = BlueValue;
      }
      else if(MinBlueValue > BlueValue){
          MinBlueValue = BlueValue;
      }
    }
  }
  //For the precision, I set it as double I uses variables by multiplying
  //numRows and numCols all the pixel numberson row and column and
  //subtract overlap by multiplying numRows and numCols
  double R1 = RedSum/(256*(numRows+numCols)-(numRows*numCols)); 
  double G1 = GreenSum/(256*(numRows+numCols)-(numRows*numCols)); 
  double B1 = BlueSum/(256*(numRows+numCols)-(numRows*numCols)); 
                                                                 
  //Find AvgRed, Green, and Blue Vlaue in the setted amount of pixel
  //through numRow and numColumn
  double AvgRedValue = (MaxRedValue + MinRedValue)/2;
  double AvgGreenValue = (MaxGreenValue + MinGreenValue)/2;
  double AvgBlueValue = (MaxBlueValue + MinBlueValue)/2;

  double threshold;
  //check whether if the inputimage background's maximum or minimum RGB value has same value or not
  if(MaxRedValue == MinRedValue && MaxGreenValue == MinGreenValue && MaxBlueValue == MinBlueValue){
    threshold = (MaxRedValue + MaxGreenValue + MaxBlueValue)/3;
  }
  else{
    threshold = sqrt((MaxRedValue-AvgRedValue)*(MaxRedValue-AvgRedValue) + 
    (MaxGreenValue-AvgGreenValue)*(MaxGreenValue-AvgGreenValue) + (MaxBlueValue-AvgBlueValue)*(MaxBlueValue-AvgBlueValue));
  }

  //Find the actual value of RGB and uses that value to find 
  //distance of each pixel and compare the threshold and 
  //distance of each actual value and assign 0 or 1 each pixel's mask
  for (int i = 0; i < 256; i++)
  {
    for (int j = 0; j < 256; j++)
    {
      int R2 = inImage[i][j][0]; //R2 is the actual value of Red
      int G2 = inImage[i][j][1]; //G2 is the actual value of Green
      int B2 = inImage[i][j][2]; //B2 is the actual value of Blue

      double Dist = sqrt((R1 - R2)*(R1 -R2) + (G1 - G2)*(G1 -G2) + (B1 - B2)*(B1 -B2));
      if(threshold < Dist){
        mask[i][j] = 1; //if Distance is smaller then threshold, it is foreground so 1 
      }
      else{
        mask[i][j] = 0; //else change which is background, 0
      }
    }
  }
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
             unsigned char inImage[SIZE][SIZE][RGB],
             unsigned char bgImage[SIZE][SIZE][RGB],
             unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
  for (int k = 0; k < 3; k++) //[RGB [k] dimension/ [1][2][3]]
  {
    for (int i = 0; i < 256; i++)
    {
      for (int j = 0; j < 256; j++)
      {
        if (mask[i][j] == 0)
        {
          outImage[i][j][k] = bgImage[i][j][k];
        }
        else if (mask[i][j] == 1)
        {
          outImage[i][j][k] = inImage[i][j][k];
        }
      }
    }
  }
}
