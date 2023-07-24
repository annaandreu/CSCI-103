/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
     
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 //================================
   // When working on Checkpoint 4, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   //result = 1; // <--- TASK: CHANGE THIS FOR CHECKPOINT 4
	
  result = maze_search(mymaze, rows, cols); 
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated: CHECKPOINT 2
   for(int v=0; v<rows; v++){
      delete [] mymaze[v];
   }
   delete [] mymaze; 
  
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete **** CHECKPOINT 4
  
  Location start; 
  int begin= 0;
  int finish= 0;
  int unknown= 0;
  
  // scan through whole maze
  for (int j = 0; j < rows; j++){ // rows
     for (int h = 0; h < cols; h++){  // columns 
       if (maze[j][h] == 'S'){ // find start location and mark
         begin++; 
         start.row = j;
         start.col= h;
       }
      if (maze[j][h] == 'F'){ // find end location and mark
        finish++; 
      }
      if (maze[j][h]== '!'){
        unknown++;
      }
}
  }
  
// initialize queue 
int maxlen= rows * cols; 
Queue theQueue(maxlen);

//initialize 'explored' array (false)
bool **explored= new bool*[rows]; 

for(int n = 0; n < rows; n++){
    explored[n]= new bool[cols]; // make 2d
  for (int b = 0; b < cols; b++){
    explored[n][b] = false; // not explored yet = false
  }
}
//initialize 'predecessor' array (.row & .col = 0)
Location **predecessor = new Location *[rows];
for (int v=0; v < rows; v++ ){
  predecessor[v]= new Location[cols]; // make 2d
  for (int y=0; y < cols; y++){
    predecessor[v][y].row = 0; // row before = 0; 
    predecessor[v][y].col = 0; // col before = 0; 
  }
}

if ( begin != 1 || finish != 1 ){ // if no start or finish / more than 1 of either
        for (int w = 0; w < rows; w++){ // delete data allocated 
          delete [] explored[w];
          delete [] predecessor[w];
        }
        delete [] explored;
        delete [] predecessor;
        return -1; 
     }

     if (unknown > 0){
       for (int w = 0; w < rows; w++){ // delete data allocated 
          delete [] explored[w];
          delete [] predecessor[w];
        }
        delete [] explored;
        delete [] predecessor;
        cout << "Error, input format incorrect." << endl;
     }
  
theQueue.add_to_back(start); // start location to queue

Location north, west, south, east;
bool solution = false;
Location currentLoc;

while(!theQueue.is_empty()){
  currentLoc= theQueue.remove_from_front();
  explored[currentLoc.row][currentLoc.col] = 1; 

  // NORTH neighbor
  north.row= currentLoc.row - 1;
  north.col= currentLoc.col;

// if in maze bounds 
  if ( (north.row >= 0 && north.row < rows) && (north.col >= 0 && north.col < cols ) ){
   // check path 
    if (maze[north.row][north.col] == '.' && explored[north.row][north.col] == false){
      theQueue.add_to_back(north);
      explored[north.row][north.col]= true; 
      predecessor[north.row][north.col]= currentLoc;
    }
    else if (maze[north.row][north.col] == 'F'){
      solution= true; 
      break;
    }
    
  }

// WEST neighbor
west.row= currentLoc.row;
west.col= currentLoc.col - 1;

if ( (west.row >= 0 && west.row < rows) && (west.col >= 0 && west.col < cols ) ){
   
    if (maze[west.row][west.col] == '.' && explored[west.row][west.col] == false){
      theQueue.add_to_back(west);
      explored[west.row][west.col]= true; 
      predecessor[west.row][west.col]= currentLoc;
    }
    else if (maze[west.row][west.col] == 'F'){
      solution= true; 
      break;
    }
  }

// SOUTH neighbor
  south.row= currentLoc.row + 1;
  south.col= currentLoc.col;
  if ( (south.row >= 0 && south.row < rows) && (south.col >= 0 && south.col < cols ) ){
   
    if (maze[south.row][south.col] == '.' && explored[south.row][south.col] == false){
      theQueue.add_to_back(south);
      explored[south.row][south.col]= true; 
      predecessor[south.row][south.col]= currentLoc;
    }
    else if (maze[south.row][south.col] == 'F'){
      solution= true; 
      break;
    }
  }

// EAST neighbor
  east.row= currentLoc.row;
  east.col= currentLoc.col + 1;
  if ( (east.row >= 0 && east.row < rows) && (east.col >= 0 && east.col < cols ) ){
   
    if (maze[east.row][east.col] == '.' && explored[east.row][east.col] == false){
      theQueue.add_to_back(east);
      explored[east.row][east.col]= true; 
      predecessor[east.row][east.col]= currentLoc;
    }
    else if (maze[east.row][east.col] == 'F'){
      solution= true; 
      break;
    }
  }
}

// if path found 
if (solution == true){
  while (maze[currentLoc.row][currentLoc.col] != 'S'){
    maze[currentLoc.row][currentLoc.col] = '*';
    currentLoc= predecessor[currentLoc.row][currentLoc.col];
  }

  for (int w = 0; w < rows; w++) {// delete data allocated 
    delete [] explored[w];
    delete [] predecessor[w];
  }
  delete [] explored;
  delete [] predecessor;

  return 1; 
}
else { // path not found
  for (int w = 0; w < rows; w++) { // delete allocated data 
    delete [] explored[w];
    delete [] predecessor[w];
  }
  delete [] explored;
  delete [] predecessor;
  return 0; 
}

}
