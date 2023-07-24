/* 
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given ifile into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the ifile of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
	
   // *** You complete **** CHECKPOINT 1
   ifstream ifile(filename);

    ifile >> *rows; 
    ifile >> *cols; 

   if (ifile.fail()){ // couldn't open file or read integers 
      return NULL;
    }
    char** maze = new char*[*rows]; // allocate dynamic mem for rows 

    for (int i=0; i < *rows; i++){
       maze[i]= new char[*cols]; // for as many rows,, allocate as many cols 

    for(int k=0; k < *cols; k++){
       ifile >> maze[i][k]; // store actual contents of 2d array
    }
    }
    return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
	
   // *** You complete **** CHECKPOINT 1
   cout << rows << " " << cols << endl;
   for (int r=0; r < rows; r++){
      for (int c=0; c < cols; c++){
         cout << maze[r][c];
      }
      cout << endl;
   }
	
}



