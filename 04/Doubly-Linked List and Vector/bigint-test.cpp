#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
   BigInt myInt("103");
   cout << myInt.to_string() << endl;


   BigInt a("D19", 16);
   cout << a.to_string() <<endl;
   BigInt b("3E6", 16);
   cout << b.to_string() <<endl;
   b.add(a);    // increase b by a
   cout << b.to_string() <<endl;
      
   return 0;
}
