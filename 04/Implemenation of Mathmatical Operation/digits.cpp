#include <iostream>
using namespace std;
int main(){
  cout << "Enter an integer between 0 and 999: " ;
  int x;
  cin >> x ; 
  int a, b, c;
  if(x >= 100)
  {
    a = x%10;
    b = (x / 10)%10;
    c = x/100;

    cout << a << endl << b << endl << c << endl;
  }
  else if(10 <= x && x < 100 )
  {
    a = x%10;
    b = (x / 10)%10;

    cout << a << endl << b << endl;
  }
  else{
    a = x;
    cout << a << endl;
  }

  return 0;


}