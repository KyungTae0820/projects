/* 
mazeio.h
Description: Input and output routines for BFS algorithms.
*/

#ifndef MAZEIO_H
#define MAZEIO_H

// read maze from the given filename, allocate and return maze 2D array,
// fill in rows and cols
char** read_maze(char* filename, int* rows, int* cols);

// print maze to cout
void print_maze(char** maze, int rows, int cols);

#endif
