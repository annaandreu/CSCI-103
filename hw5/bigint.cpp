#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    int temp= 0; 

    if (s[0] == '-'){ // find if negative 
      isPositive = false;
      
    }
    else{
      isPositive = true; 
      temp--; // gets rid of total junk value 
    }
    // convert string to int 
    for (int i = (s.length()-1); i > temp; i--){ // 0-9
      if ( (int)(s[i]) >= 48 && (int)(s[i]) <= 57 ){ 
          vec.push_back( (int)(s[i] - 48) ); 
    }
      else { // A-Z
      vec.push_back((int)(s[i] - 55)); 
      }
    }

}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
  
  base= setbase; 

  if (input == 0){
    vec.push_back(0); 
}  
  if (input < 0){
    isPositive= false;
    input*= -1;
  }
  else{
    isPositive= true;
  }

  while (input > 0){
    vec.push_back(input % base);
    input/=base;
  }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
  vec = b.vec;
  base= b.base;
  isPositive= b.isPositive;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
  vec = b.vec;
  base= b.base;
  isPositive= b.isPositive;

  return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
  string num;
  if (!(isPositive)){
      num.push_back('-');
    }

  for (int k= vec.size() -1; k >=0; k--){
    if( vec[k] >= 0 && vec[k] <= 9){ 
        num.push_back((char)(vec[k] + 48));
    }
    else {
        num.push_back((char)(vec[k] + 55)); 
    }
  }
  

  return num; 
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{ 

    /************* You complete *************/
    int number= 0;   
    
    for(int p = vec.size(); p > 0; p--) {
      number = number * base + vec[p-1];

      if ((unsigned int)(number) > (unsigned int)(INT_MAX)){
        if (isPositive == false){ 
          return INT_MIN;
        }
        else{
        return INT_MAX;
        }
      }
    }
    if (number== 0 && isPositive){ 
      return INT_MAX;
    }
    else if (number== 0 && isPositive == false){
      return INT_MIN; 
    }
        
    if (isPositive == false){ 
      number *= -1; 
      }

 
  return number;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    // if diff signs 
    if ( isPositive && b.isPositive == false){ // + > -
      return 1;
    }
    if (!(isPositive) && b.isPositive){ // + < -
      return -1; 
    } 

    //same signs 
    if( isPositive && b.isPositive){ // positive same sign 
      if ( vec.size() > b.vec.size() ){
      return 1;
      }
      if( vec.size() < b.vec.size() ){
      return -1; 
     }
    }

    if( !(isPositive) && b.isPositive == false){ // negative same sign 
      if ( vec.size() < b.vec.size() ){
      return 1;
      }
      if(vec.size() > b.vec.size()){
      return -1; 
      }
    }

  // same length 
    if( isPositive && b.isPositive){ // positive, same sign, same size
      for (int c= (vec.size()); c > 0; c--) {
          if ( vec[c-1] <  b.vec[c-1] ){
            return -1;
          } 
          if ( vec[c-1] > b.vec[c-1] ) {
            return 1; 
          }
      }
    }

    if( !(isPositive) && b.isPositive == false){ // negative, same sign, same size 
      for (int c= (vec.size()); c > 0; c--) {
          if ( vec[c-1] >  b.vec[c-1] ){
            return -1;
          } 
          if ( vec[c-1] < b.vec[c-1] ) {
            return 1; 
          }
      }
    } 

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
    
    //If ALL digits are the same, then they MUST be equal!!
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if (a.compare(b) == 0) {
        return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    if (a != b){
    return true;
  }
  else{
    return false;
  }
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == -1 || !a.compare(b); 

}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
     return a.compare(b) == 1 || !a.compare(b); 
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
     return a.compare(b) == 1;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  return a.compare(b) == -1; 
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
   BigInt copyA= a;
   copyA += b;

  return copyA;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
int carry=0; 
int value_of_a = 0;
int value_of_b = 0;
int addition= 0;

//if both pos or both neg
if ((isPositive && b.isPositive) || (isPositive == false && b.isPositive== false)){
   //if neg make both positive 
  for (unsigned int w=0; w < max(vec.size(), b.vec.size()); w++){
      if (w < vec.size()) {
            value_of_a = vec[w];
      }
      else {
        value_of_a= 0;
      }
      if (w < b.vec.size()){
        value_of_b = b.vec[w];
      }
      else {
        value_of_b = 0;
      }
      addition= value_of_a + value_of_b + carry; 
      
      // if sum bigger than base ,, carry first dig 
      if(addition >= base){
        carry= addition / base; 
      }
      else{
        carry=0;
      }
      
      //if in vec range,, second dig stay in vec 
      // if not, push back to add new dig 
      if (w < vec.size()) {
        vec[w] = addition % base;
      }
      else {
        vec.push_back(addition % base);
      }
  }
 // after everything in range loops and finishes      
 // if theres anything leftover
      if (carry != 0) {
        vec.push_back(carry);
      }  
  
 }


// POSITIVE + NEGATIVE
// A=pos , B= neg --> basically subtration w copy
if (isPositive && b.isPositive == false){
  BigInt copyB(b);
  BigInt Acopy(*this);
  copyB.isPositive = true;
  *this -= copyB;
  
  if (Acopy >= copyB){
    isPositive = true;
  }
  else if (Acopy < copyB){
    isPositive = false;
  }

}
// A=neg, B=pos --> make both pos then subtract, then switch sign
else if (isPositive== false && b.isPositive){
  BigInt copyB(b);
  isPositive = true;
  BigInt Acopy(*this);
  *this -= b;

  if(vec[0] == 0 && vec.size() == 1) {
    isPositive = true;
  } 
   

  if (Acopy > copyB){
    isPositive = false;
  }
  if(Acopy < copyB){
    isPositive= true;
  }
  
}

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt copy2= a;
   copy2 -= b;

  return copy2;
}
/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    int borrow= 0; 
    int subtract= 0;
    int value_of_a= 0;
    int value_of_b= 0;


// diff signs 
  // POSITIVE - NEGATIVE ,, +a - -b  --> basically addition
  if (isPositive && b.isPositive == false){
    BigInt copyB(b);
    BigInt Acopy(*this);
    copyB.isPositive = true;
    *this += copyB;

  if(Acopy >= b){
    isPositive= true;
  }
  }
 
  // NEGATIVE - POSITIVE ,, -a - +b --> make positive and add then change back 
  else if (isPositive== false && b.isPositive){
    isPositive = true;
    *this += b;
    isPositive = false;

  } 


// BOTH POSITIVE / BOTH NEGATIVE
if ((isPositive && b.isPositive) || (isPositive == false && b.isPositive == false)){
    BigInt copyA(*this);
    BigInt copyB(b);
    for (unsigned int v= 0; v < max(vec.size(), b.vec.size()); v++) {
     
      if (v < vec.size()) {
        value_of_a = vec[v];
      }
      else {
        value_of_a = 0;
      }
      if (v < b.vec.size()) {
        value_of_b = b.vec[v];
      }
      else {
      value_of_b = 0;
      }
// BOTH POSITIVE ,, POS - POS 
    
    if (isPositive && b.isPositive){
    //figure our which num is greater  
      if (*this > b){
        subtract = value_of_a - value_of_b - borrow; 
      }
      else {
        subtract = value_of_b - value_of_a - borrow;
      }
    }
// BOTH NEGATIVE ,, NEG - NEG
    else if (isPositive == false && b.isPositive == false){
    //figure our which num is greater  
      if (*this > b){
        subtract = value_of_b - value_of_a - borrow; 
      }
      else { // a < b
        subtract = value_of_a - value_of_b - borrow;
      }
    }

    if (subtract < 0) {
      subtract += base;
      borrow = 1;
    }
    else {
      borrow = 0;
    }
         
  if (v < vec.size()) {
    vec[v] = subtract;
  }
  else {
  vec.push_back(subtract);
  }
}

if(isPositive && b.isPositive == true){
  if(copyA < copyB){
    isPositive= false;
  }
}
if(isPositive == false && b.isPositive == false){
  if(copyA > copyB){
    isPositive= true;
  }
}
if (copyA == copyB){
  isPositive= true;
}
}

//get rid of total zeros 
for (unsigned int y = vec.size() - 1; y > 0; y--) {
  if (vec[y] == 0) {
    vec.pop_back();
  }
  else {
    break;
  }
  
} 
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt copy= a;
   copy *= b;

  return copy;
}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    // base case 
    //ZERO
    BigInt zero(0, base); // x0
  
    BigInt total(0, base);
    int product= 0;
    int carry= 0;

    for (unsigned int t= 0; t < b.vec.size(); t++){
      string empty(t,'0'); //?
      BigInt temp(empty, base);
      for (size_t x = 0; x < vec.size(); x++) {
        product = (vec[x] * b.vec[t]) + carry;
        carry = product / base;
        temp.vec.push_back(product % base);
        }
      if (carry != 0) {
        temp.vec.push_back(carry);
      }
      
     total+= temp;
      carry= 0; 
    }
    if((product== 0) && (b.vec.size() == 1 || vec.size() == 1)){
      *this= zero; 
      return *this;
    }

    if ((isPositive && b.isPositive== false) || (isPositive == false && b.isPositive)){
      total.isPositive= false; 
    }
   

    *this= total;
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy3= a;
    copy3 /= b;

    return copy3;
}

/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    BigInt quotient(base);
    BigInt remainder(base);
    
    divisionMain(b, quotient, remainder);
  
    *this = quotient;
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt acopy= a;
  acopy%= b;

  return acopy;
}

/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero. 
    }
    /************* You complete *************/

    BigInt quotient(base);
    BigInt remainder(base);
    
    divisionMain(b, quotient, remainder);
    
    *this = remainder;
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
//make both divs positive

//dividend
bool initialSign= isPositive; // to keep track of OG sign
isPositive= true; 

//divisor
BigInt positive_divisor= b; 
//b.isPositive would keep track of OG sign
positive_divisor.isPositive= true;  


int pos= vec.size() - 1;
BigInt divedend_seq(vec[pos], base);

while(divedend_seq < positive_divisor){
  pos--;
  divedend_seq.vec.insert(divedend_seq.vec.begin(), vec[pos]);
}

while (pos >= 0) { // reapeat steps 4-9
  int times= 0;
  while(divedend_seq >= positive_divisor){
    divedend_seq -= positive_divisor;
    times++;
  }

  quotient.vec.insert(quotient.vec.begin(), times);

  // if divedend_seq = 0
  if (divedend_seq.vec.size() == 1 && divedend_seq.vec[0] == 0){
    divedend_seq.vec.clear();
  }
// more digits in divedend_seq
if (pos - 1 >= 0) {
  divedend_seq.vec.insert(divedend_seq.vec.begin(), vec[pos -1]);
}
  pos--; 
}

//empty?
if (divedend_seq.vec.empty()){
  remainder.vec.push_back(0);
  remainder.isPositive = true; // 0 always positive 
}
else{
  remainder = divedend_seq;
  if (initialSign == true){ // determine if remainder +/-
    remainder.isPositive= true;
  }
  else{
    remainder.isPositive = false;
  }
}

if ((initialSign == b.isPositive) || (initialSign == false && b.isPositive == false)){
  quotient.isPositive= true;
}  
else{
  quotient.isPositive= false;
}
// base cases
// ZERO
BigInt zero(0, base);
zero.isPositive= true;
if (*this == zero){
  quotient= zero;
  remainder= zero;
  if(initialSign == false){
    remainder.isPositive = false;
  }
  else {
    remainder.isPositive = true;
  }
}



// divide my itself 
BigInt one(1, base);
if (*this == positive_divisor){
  quotient= one;
  remainder= zero;
  if((initialSign == true && b.isPositive) || (initialSign == false && b.isPositive == false)){
    quotient.isPositive = true;
  }
  else {
    quotient.isPositive = false;
  }
}
if (*this < positive_divisor) {
  quotient = zero;
  remainder = *this;
  if(initialSign == false){
    remainder.isPositive = false;
  }
  else {
    remainder.isPositive = true;
  }
  }
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt copy5= a;
  copy5.exponentiation(b);
  return copy5;
  
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    BigInt exponent= b;
    BigInt result(1, base);
    BigInt zero(0, base);
    BigInt one(1, base);
    BigInt two(2, base);

    while(exponent > zero){
      if(exponent % two == zero){ // if even 
        *this *= *this; 
        exponent/= two;
      }
      else{ // odd
        exponent -= one;
        result *= *this;  
      }
    }

    *this= result;
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
  BigInt coopy(a);
  coopy.modulusExp(b,m);
  return coopy;
}

/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    BigInt exponent(b);
    BigInt zero(0,base);
    BigInt one(1, base);
    BigInt two(2, base);
    BigInt result(1,base);

    while(exponent > zero){
      if (exponent % two == zero) { // even 
        *this *= *this;
        *this %= m;
        exponent/= two;
      }
      else { //odd
            exponent -=one;
            result *= *this;
            result %=m;
        }
    }
  
    *this =result;
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************