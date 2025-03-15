#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   cout << "Enter 3 integers (red, green, and blue), in that order:";
   float red, green, blue;
   cin >> red >> green >> blue;

   float white;
   if (max((red/255), (green/255)) > (blue/255)){
         white = max((red/255), (green/255));
   }
   else{
      white = (blue/255);
   }
   float cyan = (white - (red/255))/ white;
   float magenta = (white - (green/255))/white;
   float yellow = (white - (blue/255))/white;
   float black = 1 - white;
   
   cout << "cyan: " << cyan << endl;
   cout << "magenta: " << magenta << endl;
   cout << "yellow: " << yellow << endl;
   cout << "black: " << black << endl;
   
   return 0;
}