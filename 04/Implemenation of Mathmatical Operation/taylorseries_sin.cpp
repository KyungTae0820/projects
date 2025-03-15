#include <iostream>
#include <cmath>

using namespace std;

int fact(int); 

int main(int argc, char *argv[])
{
   
   // Prompt the user
   cout << "Enter x in radians:  ";
   double x;
   // get input
   cin >> x;
   
   // Do some operations
   double a = x;
   double b = pow(x,3)/fact(3);
   double c = pow(x,5)/fact(5);
   double d = pow(x,7)/fact(7);
   // Print the result to the user
    cout << a - b + c - d << endl;
  
   return 0;
   
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
   int result = 1;
   for (int i = 1; i <= n; i++) {
      result = result * i;
   }
   return result;
}

