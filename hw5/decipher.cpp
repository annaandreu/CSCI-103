#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/
try{
	ifstream ifile;
	ifile.open(argv[1]);

	int base;
	string d;
	string n;
	string code; 
	BigInt result;

	ifile >> base >> d >> n;
	BigInt bigd(d, base);
	BigInt bign(n, base);

	//for each secret code 
	while(ifile >> code){
		BigInt secret_code(code, base);
		result= modPow(secret_code, bigd, bign);
		cout << (char)result.to_int();
	}
	cout << endl;
}
 
 catch(const exception& e){
  cout<<e.what() << endl;
  return -1;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
	return 0;
}
