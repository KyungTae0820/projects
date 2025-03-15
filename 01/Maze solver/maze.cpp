/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search
int maze_search(char**, int, int);

// Add other prototypes here for any functions
int checkPath(char** maze, bool** explored, int rows, int cols, Location loc);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }
    else if(argc > 3)
    {
      cout << "To many input file" << endl;
      return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols);

    result = maze_search(mymaze, rows, cols);
    if(result == 1){
      print_maze(mymaze, rows, cols);
    }
    else if(result == 0){
      cout << no_path_message << endl;
    }
    else if(result == -1){
      cout << invalid_maze_message << endl;
    }
    else{
      cout << invalid_char_message << endl;
    }

    // Delete all memory that read_maze allocated: CHECKPOINT 2
    for(int i = 0; i < rows; i++){
      delete [] mymaze[i];
    }
    delete [] mymaze; //as pointer pointer **

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    //Create your queue with an appropriate size i.e., rows*cols
    Queue q(rows*cols);// set q object

    //Declare the start locations and check its validity
    Location start;//set start point
    Location curr, N, W, S, E;
    //curr refers to current locations
    //N refers to North location from the current point
    //W refers to West location from the current point
    //S refers to West location from the current point
    //E refers to West location from the current point
    int startcount = 0;
    int finishcount = 0;
    for(int i = 0; i < rows; i++){
      for(int j =0; j < cols; j++){
        if(maze[i][j] == 'S'){
          startcount++;
          start.row = i;
          start.col = j;
          q.add_to_back(start);
          if(startcount > 1){//it should be 1
            return -1;//badly formatted maze because there are more than 2 start points
          }
        }
        else if(maze[i][j] == 'F'){
          finishcount++;
          if(finishcount > 1){//it should be 1
            return -1;//badly formatted maze because there are more than 2 finish points
          }
        }
        else if(maze[i][j] != '.' && maze[i][j] != '#' && 
                maze[i][j] != 'S' && maze[i][j] != 'F'){
                  return 2;//random value except for 1, 0, and -1 for invalide character
        }
        else{}
      }
    }
    if(startcount == 0 || finishcount == 0){
      return -1;////badly formatted maze as there is not start or finish point
    }

    //Dynamically allocate the predecessor and explored arrays. 
    Location** predecessor = new Location*[rows];
    bool** explored = new bool*[rows];
    for(int i = 0; i < rows; i++){
      predecessor[i] = new Location[cols];
      explored[i] = new bool[cols];
    }
    //explored should be all false at first time
    for(int i = 0; i < rows; i++){//Input bool values to the array
      for(int j = 0; j < cols; j++){
        explored[i][j] = false;
      }
    }
    //Perform the breadth-first search algorithm described earlier.
    //BFSalgorithm(connects to mark the start location)

    bool pathValid = false;
    while(q.is_empty() == false){
      curr = q.remove_from_front();
      explored[curr.row][curr.col] = true;
      //Set North point
      N.row = curr.row - 1;
      N.col = curr.col;

      //Set West point
      W.row = curr.row;
      W.col = curr.col - 1;

      //Set South point
      S.row = curr.row + 1;
      S.col = curr.col;

      //Set East point
      E.row = curr.row;
      E.col = curr.col + 1;

      int Npath = checkPath(maze, explored, rows, cols, N);
      int Wpath = checkPath(maze, explored, rows, cols, W);
      int Spath = checkPath(maze, explored, rows, cols, S);
      int Epath = checkPath(maze, explored, rows, cols, E);
      
      //North direction check
      if(Npath == 1){
        pathValid = true;
        break;//if F is found pathValid true so just exit BFS algorithm
      }
      else if(Npath == 2){
        q.add_to_back(N);
        explored[N.row][N.col] = true;
        predecessor[N.row][N.col] = curr;
      }
      else{}//segmentation fault case, impossible 

      //West direction check
      if(Wpath == 1){
        pathValid = true;
        break;//if F is found pathValid true so just exit BFS algorithm
      }
      else if(Wpath == 2){
        q.add_to_back(W);
        explored[W.row][W.col] = true;
        predecessor[W.row][W.col] = curr;
      }
      else{}//segmentation fault case, impossible 
      
      //South direction check
      if(Spath == 1){
        pathValid = true;
        break;//if F is found pathValid true so just exit BFS algorithm
      }
      else if(Spath == 2){
        q.add_to_back(S);
        explored[S.row][S.col] = true;
        predecessor[S.row][S.col] = curr;
      }
      else{}//segmentation fault case, impossible 
      
      //East direction check
      if(Epath == 1){
        pathValid = true;
        break;//if F is found pathValid true so just exit BFS algorithm
      }
      else if(Epath == 2){
        q.add_to_back(E);
        explored[E.row][E.col] = true;
        predecessor[E.row][E.col] = curr;
      }
      else{}//segmentation fault case, impossible 

      //just last check or clarification
      if(Npath == 1 || Wpath == 1 ||
         Spath == 1 || Epath == 1){
           pathValid = true;
           break;
      }
    }
    //if path is found, until current location of the maze reach
    //S, change the . to * and set current location to predecessor
    //the opposite way we did in storing the value to queue
    if(pathValid){
      while(maze[curr.row][curr.col] != 'S' && explored[curr.row][curr.col] == true){
        maze[curr.row][curr.col] = '*';
        curr = predecessor[curr.row][curr.col];
      }
      //Deallocate explored array
      for(int i = 0; i < rows; i++){
        delete [] explored[i];
        delete [] predecessor[i];
      }
      delete [] explored; //as pointer pointer **
      delete [] predecessor;

      return 1;//success
    }
    //if path is not found, still deallocate both explored and predecessor
    //to prevent memory leak
    else{//pathValid is false
      //Deallocate explored array
      for(int i = 0; i < rows; i++){
        delete [] explored[i];
        delete [] predecessor[i];
      }
      delete [] explored; //as pointer pointer **
      delete [] predecessor;

      return 0;//no path found
    }
    //return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}

//added another unction that check the path
int checkPath(char** maze, bool** explored, int rows, int cols, Location loc){
  int pathFound = 0;
  if(loc.row >=0 && loc.row < rows && loc.col >=0 && loc.col < cols){//should in range
    if(explored[loc.row][loc.col] == false){
      if(maze[loc.row][loc.col] == 'F'){
        pathFound = 1;
      }
      else if(maze[loc.row][loc.col] == '.'){
        pathFound = 2;
      }
      else{}//Do nothing if maze[loc.row][loc.col] is #
    }
  }
  return pathFound;
}
