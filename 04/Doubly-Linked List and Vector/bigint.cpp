#include <iostream>
#include "bigint.h"

using namespace std;

BigInt::BigInt(std::string s, int base){ // convert string to BigInt
    ubase = base;
    for(int i = s.size()-1; i >= 0; i--){
      int c = s[i] - '0';
      if(c<10){
          v1.push_back(c);
      }
      else{
        v1.push_back(c-7);
      }
      
    }
}

std::string BigInt::to_string() const{// get string representation
  string a  = "";
  for(int i = v1.size()-1; i >= 0 ; i--){
    if(v1[i] < 10){
      char c = v1[i] + '0';
      a += c;
    }
    else{
      char c = v1[i] + 7 + '0';
      a += c;
    }
  }
  return a;
} 

void BigInt::add(BigInt b){// add another BigInt to this one
    int diff1 = v1.size() - b.v1.size();
    int diff2 = b.v1.size() - v1.size();
    if(diff1 >= 0){
      for(int i = 0; i < diff1; i++){
          b.v1.push_back(0);
      }
    }
    else{
      for(int i = 0; i < diff2; i++){
          v1.push_back(0);
        }
    }
    int carry = 0;
    for(size_t i = 0; i < v1.size(); i++){
      int temp = v1[i] + b.v1[i]+ carry;
      v1[i] = temp%ubase;
      carry = temp/ubase;
    }
    if(carry > 0){
      v1.push_back(carry);
    }
}