#include "stack.h"
#include <iostream>
using namespace std;
int main(){
  Stack<int> s1;
  Stack<double> s2;
  Stack<char> s3;

  s1.push(1);
  s1.push(2);
  s1.push(3);
  s2.push(1.1);
  s2.push(2.2);
  s2.push(3.3);
  s3.push('a');
  s3.push('b');
  s3.push('c');
  

  cout << "Print int" << endl;
  while(!s1.empty()){
    cout << s1.top() << endl;
    s1.pop();
  }

  cout << "Print double" << endl;
  while(!s2.empty()){
    cout << s2.top() << endl;
    s2.pop();
  }

  cout << "Print char" << endl;
  while(!s3.empty()){
    cout << s3.top() << endl;
    s3.pop();
  }
  //check for error message pop()
  //s3.pop();

  //check for error message top()
  s3.top();
  return 0;
}