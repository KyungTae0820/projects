#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this assignment
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width)
{
   // width drawing
   for (int j = left; j < left + width; j++)
   {
      if (top < 256 && top >= 0 && j < 256 && j >=0){
         image[top][j] = 0;
      }
      if ((top + height -1) < 256 && (top + height -1) >= 0 && j < 256 && j >= 0){
         image[top + height-1][j] = 0;
      }     
   }
   // height drawing
   for (int i = top; i < top + height; i++)
   {
      if (i < 256 && i >= 0 && left < 256 && left >=0){
         image[i][left] = 0;
      }
      if (i < 256 && i >= 0 && left + width-1 < 256 && left + width-1 >=0){
         image[i][left + width-1] = 0;
      }
   }
}

// Fill in this function:
void draw_ellipse(int cr, int cc, int height, int width)
{
   for (double theta = 0.0; theta < 2 * M_PI; theta += .01)
   {
      if (cr < 256 && cr >= 0 && cc < 256 && cc >=0){
         double x = cc;
         double y = cr;

         x += width* cos(theta) / 2 ;
         y += height * sin(theta) / 2;
         if (x < 256 && x >= 0 && y < 256 && y >=0){
            image[(int)y][(int)x] = 0;
         }
        
      }
        
   }
}

void print_menu()
{
   cout << "To draw a rectangle, enter: 0 top left height width" << endl;
   cout << "To draw an ellipse, enter: 1 cy cx height width" << endl;
   cout << "To save your drawing as 'output.bmp' and quit, enter: 2" << endl;
}

int main()
{
   // initialization
   print_menu();
   int x;
   int top, left, cc, cr, height, width;
   for (int i = 0; i < SIZE; i++)
   {
      for (int j = 0; j < SIZE; j++)
      {
         image[i][j] = 255;
      }
   }
   // Main program loop here
   while (x != 2)
   {
      cin >> x;
      if (x == 0)
      {
         cin >> top >> left >> height >> width;
         draw_rectangle(top, left, height, width);
      }
      else if (x == 1)
      {
         cin >> cc >> cr >> height >> width;
         draw_ellipse(cc, cr, height, width);
      }
   }
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);

   return 0;
}