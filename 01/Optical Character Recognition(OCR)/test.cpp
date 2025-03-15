#include "bigint.h"
#include <iostream>
using namespace std;

int main() {

   BigInt a("1");
   cout << a.to_string() <<endl;
   BigInt b("100");
   cout << b.to_string() <<endl;
   b.minus(a);    // increase b by a
   cout << b.to_string() <<endl;
      
   return 0;
}
