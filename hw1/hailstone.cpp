// name: Anna Andreu 
// email: aandreu@usc.edu

#include <iostream>
using namespace std; 

int main(){

int num; 
int length= 0;
cout << "Enter a number: " << endl;
cin >> num;

while (num!= 1){
  if (num % 2 == 0){
    num/=2;
    cout << num << " " ;
    length++;
  }
  else{
    num= (num*3) + 1;
    cout << num << " " ;
    length++;
  }
}

cout << endl;
cout << "Length: " << length << endl;

  return 0;
}