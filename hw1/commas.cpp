// name: Anna Andreu 
// email: aandreu@usc.edu
/********************************************************
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 ********************************************************/
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;
  /*====================*/
  /* Start of your code */

  cin >> n;

  int digit_count= 0;
  long long mod= 0;
  int zero_count= 0;

   if (n > -1000 && n < 1000){ // if less than 4 digits
    cout << n << endl;
    return 0;
  }
  
  if (n < 0){ // if negative
    n*= -1;
    cout << "-" ;
  }

  long long num= n; 
  
  
  if (num % 3 == 0)  { // Ex. 123,456
    
    while( num > 0) {
        num = num / 1000; 
        digit_count++;
      } 
      num = n;
      
      double power= pow(1000.0, (double) digit_count );
      mod= power;
      mod /= 1000;
      
  for (int i= 1; i <= digit_count ; i++) { // Ex. 123,456,789
        if (n/mod == 12){
            cout << "0";
        }
        cout << n/mod;
        if (i != digit_count){
            cout << ',';
        }
        n= num; 
        n= n % mod; 
        mod /= 1000;
  }
}




  if (num % 3 == 1){ // Ex. 1,234
    
        while( num > 10) {
        num = num / 1000; 
        digit_count++;
      } 
      if (digit_count ==2){
          if (num/10 == 1){
              zero_count++;
          }
      }
      num = n;
      
      while (num >= 10){
          if (zero_count==1 && num==10){
              break;
          }
          num/=10;
        }
        cout << num;  
        cout << "," ;
        num= n;
        
      
      double power= pow(1000.0, (double) digit_count );
      mod= (int)power;
      n= n % mod; 
      mod /= 1000;
      
  for (int i= 1; i <= digit_count ; i++) { //123,456,789
        cout << n/mod;
        if (n/mod == 0){
          cout << "00";
      }
        if (i != digit_count){
            cout << ',';
        }
        n= num; 
        n= n % mod; 
        mod /= 1000;
  }

  }

  if (num % 3 == 2){ // Ex. 12,345
    while (num >= 100){
          num/=10;
        }
        cout << num;  
        cout << "," ;
        num= n;
        
        while( num > 10) {
        num = num / 1000; 
        digit_count++;
      } 
      num = n;
      
      double power= pow(1000.0, (double) digit_count );
      mod= power;
      n= n % mod; 
      mod /= 1000;
      
  for (int i= 1; i <= digit_count ; i++) { //123,456,789
        cout << n/mod;
        if (i != digit_count){
            cout << ',';
        }
        n= num; 
        n= n % mod; 
        mod /= 1000;
  }
  }

  /* End of your code */
  /*==================*/
  
  return 0;
}