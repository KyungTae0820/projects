/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * Also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
    ifstream ifstr(filename);
    if(ifstr.fail())
    {
        return NULL;
    }
    ifstr >> *rows >> *cols;

    int r = *rows;
    int c = *cols;

    char** copyMaze = new char*[r];
    //allocating the copyMaze array to copy maze
    for(int i = 0; i < r; i++)
    {
    //   copyMaze[i] = new char[c];
    //   for(int j = 0; j < c; j++)
    //   {
    //     char buff[1];
    //     ifstr >> buff;
    //     strcpy(copyMaze[i], buff);
    //   }
        copyMaze[i] = new char[c];//need to receive all the character
    }
    //receive the value or copy the value from .in file.
    for(int i =0; i < r; i++){
      for(int j = 0; j < c; j++)
        {
            ifstr >> copyMaze[i][j];
        }
    }
    ifstr.close();
    return copyMaze;
}


/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
    cout << rows << " " << cols << endl; 
    for(int i =0; i< rows; i++){
        for(int j = 0; j< cols; j++){
            cout << maze[i][j];
        }
        cout << endl;
    }
}

