//-------------------
//------------------
//CS103L - Programming Assignment
//------------------


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "bmplib.h" 
#include "queue2.h"
using namespace std;

void usage() { 
    cerr << "usage: ./label <options>" << endl;
    cerr <<"Examples" << endl;
    cerr << "./label test_queue" << endl;
    cerr << "./label gray <input file> <outputfile>" << endl;
    cerr << "./label binary <inputfile> <outputfile>" << endl;
    cerr << "./label segment <inputfile> <outputfile>" << endl;
}

//==============================
//Function prototypes go here
void test_queue();
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width);
//--- TODO: you complete the rest --- CHECKPOINT 0
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width);
void gray2binary(unsigned char **in,unsigned char **out,int height,int width);
int component_labeling(unsigned char **binary_image,
                       int **labeled_image,int height,int width);
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,
               int num_segment,int height,int width);

//==============================
// The main function, you do not need to make any changes to this function 
// However, we encourage you to try to understand what's going on in the main function
int main(int argc,char **argv) {

    srand(time(0));
    if(argc < 2 )  {
        usage();
        return -1;
    }        
    unsigned char ***input=0;
    unsigned char **gray=0;
    unsigned char **binary=0;
    int **labeled_image=0;
    if( strcmp("test_queue",argv[1]) == 0 ) { 
        test_queue();
    } 
    else if(strcmp("gray",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough argument for gray" << endl;
            return -1;
        }
        int height, width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            return -1;
        }
        //dynamically allocated a 2D gray image array            
        gray = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        if(writeGSBMP(argv[3],gray,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);

    }
    else if(strcmp("binary",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for binary" << endl;
            return -1;
        }            
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array    
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        //call gray2binary to get the binary image from gray
        gray2binary(gray,binary,height,width);
        if(writeBinary(argv[3],binary,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
     
    }
    else if(strcmp("segment",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for segment" << endl;
            return -1;
        } 
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array  
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        rgb2gray(input,gray,height,width);
        gray2binary(gray,binary,height,width);
        //dynamically allocated a 2D array for labels.
        labeled_image = new int*[height];
        for(int i=0;i<height;i++){
          labeled_image[i] = new int[width];
          for(int j=0;j<width;j++){
            labeled_image[i][j] = 0;
          }
        }
        int segments = component_labeling(binary, labeled_image, height, width); 
        cout<<"Segments found: "<< segments << endl;
        //replace 3D input image with 0 to be used as output.
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                for(int k=0;k<RGB;k++){
                  input[i][j][k] = 0;
                } 
            }
        }
        //label2rgb
        label2RGB(labeled_image, input , segments, height, width);
        if(writeRGBBMP(argv[3],input,height,width) != 0) {
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
    }
   return 0;
}


//==============================
//Loop over the 'in' image array and calculate the single 'out' pixel value using the formula
// GS = 0.2989 * R + 0.5870 * G + 0.1140 * B 
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width) {

  //-- TODO: You complete -- CHECKPOINT 2
for (int i=0 ; i < height; i++){ // height
  for (int j=0; j< width; j++){ // width 
      out[i][j]= (char) (0.2989 * in[i][j][0] + 0.5870 * in[i][j][1] + 0.1140 * in[i][j][2]);
    }
  }

}

//==============================
//Loop over the 'in' gray scale array and create a binary (0,1) valued image 'out'
//Set the 'out' pixel to 1 if 'in' is above the THRESHOLD (already defined), else 0
void gray2binary(unsigned char **in,unsigned char **out,int height,int width) {

  //-- TODO: You complete -- CHECKPOINT 3

for (int f=0 ; f < height; f++){ // height
  for (int c=0; c< width; c++){ // width 
      if ( in[f][c] > THRESHOLD){
        out[f][c] = 1; 
      }
      else if ( in[f][c] < THRESHOLD){
        out[f][c] = 0;
      }
    }
}
}


//==============================
//This is the function that does the work of looping over the binary image and doing the connected component labeling
//See the guide for more detail.
//- Should return number of segments or components found
//- Two disjoint components should not share the same label.
int component_labeling(unsigned char **binary_image,int **label,int height,int width) {

  //-- TODO: You complete -- CHECKPOINT 4
for (int g= 0; g < height; g++){  // initialize every cell in 'label' array to 0
  for (int l= 0; l < width; l++){
    label[g][l] = 0;
  }
}

int current_label= 0;
int maxlen= height * width; 
Queue PixelQueue(maxlen); 
Location loc;
Location north, west, south, east;

//explored array 
bool **explored= new bool*[height];
for (int m = 0; m < height; m++){ 
  explored[m]= new bool[width];
  for (int n= 0; n < width; n++){
    explored[m][n]= true;
  }
}

// step 2-5
for (int c= 0; c < height; c++){ 
  for (int v= 0; v < width; v++){
    if (binary_image[c][v] == 1) { // if white      
      explored[c][v]= false; // mark as unexplored
    }
  } 
}
      
for (int t= 0; t < height; t++){ 
  for (int y= 0; y < width; y++){
    if (explored[t][y] == false && binary_image[t][y] == 1){ // if white & unexplored
      loc.row= t; 
      loc.col= y;
      current_label++;
      explored[loc.row][loc.col]= true; 
      label[loc.row][loc.col] = current_label;
      PixelQueue.push(loc);
    }
    


// BFS
while(!PixelQueue.is_empty()){
  
  // set loc
  Location pixel= PixelQueue.pop(); 

      // for each neigbor !!
// NORTH neighbor
  north.row= pixel.row - 1;
  north.col= pixel.col;

// if in bounds/ valid
  if ((north.row < height) && (north.col < width) ){
   // if pixel white and not explored
    if ((binary_image[north.row][north.col] == 1) && explored[north.row][north.col] == false){
      explored[north.row][north.col]= true; 
      label[north.row][north.col]= current_label; 
      PixelQueue.push(north);
    }  
  }

// WEST neighbor
west.row= pixel.row;
west.col= pixel.col - 1;

if ((west.col < height) && (west.col < width)){
   // if pixel white and not explored
    if ((binary_image[west.row][west.col] == 1) && explored[west.row][west.col] == false){
      explored[west.row][west.col]= true; 
      label[west.row][west.col]= current_label;
      PixelQueue.push(west);
    }  
  }
    

// SOUTH neighbor
  south.row= pixel.row + 1;
  south.col= pixel.col;
  if ((south.col < height) && (south.col < width)){
   // if pixel white and not explored
    if ((binary_image[south.row][south.col] == 1) && explored[south.row][south.col] == false){
      explored[south.row][south.col]= true; 
      label[south.row][south.col]= current_label;
      PixelQueue.push(south);
    }  
  }

// EAST neighbor
  east.row= pixel.row;
  east.col= pixel.col + 1;
  
  if ((east.row < height) && (east.col < width)){
   // if pixel white and not explored
    if ((binary_image[east.row][east.col] == 1) && explored[east.row][east.col] == false){
      explored[east.row][east.col]= true; 
      label[east.row][east.col]= current_label;
      PixelQueue.push(east);
    }  
  }
}
  }
}


//dellocate explored array
for (int m= 0; m < height; m++){  
  delete[] explored[m];
}
delete [] explored;

return current_label;

    return 0;//for now
}    


//==============================
//Randomly assign a widthor (RGB) to each segment or component
//No two segments should share the same widthor.
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,int num_segments,int height,int width)
{
  //-- TODO: You complete -- CHECKPOINT 5
 for(int x=0; x < height; x++){ // initialize black
    for(int f=0; f < width; f++){
      for(int v=0; v < RGB; v++){
        rgb_image[x][f][v]=0;          
        } 
    }
  }

  for(int e=1; e < num_segments + 1; e++){ // for num segs make ran color
    int red=(unsigned char)(rand()% 256);
    int green=(unsigned char)(rand()% 256);
    int blue=(unsigned char)(rand()% 256);    
    
    for(int r=0;r < height; r++){ 
        for(int u=0; u < width; u++){
            if(labeled_image[r][u]==e){ // each seg diff color
              rgb_image[r][u][0]= red;    
              rgb_image[r][u][1]= green; 
              rgb_image[r][u][2]= blue;  
            } 
        }
    }    
}

}


//========= CHECKPOINT 6 ==============
//fill out this function to delete all of the dynamic arrays created
//-- these arrays are created in the main function.
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width) {
    if(input) {
        //TODO: You complete -- delete allocated input image array here (3D)
    for (int q= 0; q < height; q++){  
      for (int w= 0; w < width; w++){
        delete [] input[q][w];
      }
      delete [] input[q];
    }
    delete [] input; 

    } 
    if(gray){
        //TODO: You complete -- delete allocated gray-scale image here (2D)
    for (int x= 0; x < height; x++){  
      delete [] gray[x];
    }
    delete [] gray;

    }
    if(binary){
        //TODO: You complete -- delete allocated binary image array here (2D)
      for (int x= 0; x < height; x++){  
        delete [] binary[x];
    }
    delete [] binary;
    }

    if(labeled_image){
        //TODO: You complete -- delete allocated labeled array here (2D)
      for (int x= 0; x < height; x++){  
        delete [] labeled_image[x];
    }
    delete [] labeled_image;

    }

}



//==============================
//This function is used to test your queue implementation.
//You do not need to change it
void test_queue() { 
    // create some locations;
    Location three_one, two_two;
    three_one.row = 3; three_one.col = 1; // height, width 
    two_two.row = 2; two_two.col = 2; //height, width
    

    //create an Queue with max capacity 5
    Queue q(5);

    cout << boolalpha;
    cout << q.is_empty() << endl;           // true
    q.push(three_one);
    cout << q.is_empty() << endl;           // false
    q.push(two_two);

    Location loc = q.pop();
    cout << loc.row << "," << loc.col << endl; // 3 1
    loc = q.pop();
    cout << loc.row << "," << loc.col<< endl; // 2 2
    cout << q.is_empty() << endl;           // true
}
//----------------
//----------------
//----------------


