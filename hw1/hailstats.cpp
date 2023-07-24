// name: Anna Andreu 
// email: aandreu@usc.edu
#include <iostream>
using namespace std; 

int main(){

int range; 
int start= range;
int end= range;
int length= 0;
int min_length= 10000;
int max_length= 0;
int min_num= 0;
int max_num= 0;

cout << "Enter the range that you want to search: " ;
cin >> range;
start= range; // first number 

cin >> range; 
end= range; //second number 

if (end < start){
  cout << "Invalid range" << endl;
  return 0;
}

for (int i= start; i <= end; i++){
  int num= i;
  while (num!= 1){
    if (num % 2 == 0){
      num/=2;
      length++;
    }
    else{
      num= (num*3) + 1;
      length++;
    }
  }

    if (length > max_length){ // max
      max_length= length; 
      max_num= i; 
    }
    
    if (length == max_length){
      if (i < max_num){
        max_num= i;
      }
      else {
  
      }
    }

    if (length < min_length){
      min_length= length; 
      min_num= i; 
    }

    if (length == min_length){
      if (i < min_num){
        min_num= i;
      }
      else {
      }
    }

    length= 0; 
}

cout << "Minimum length: " << min_length << endl;
cout << "Achieved by: " << min_num << endl;
cout << "Maximum length: " << max_length << endl;
cout << "Achieved by: " << max_num << endl;



  return 0;
}