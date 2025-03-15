#include <iostream>
#include "clothing.h"
#include "util.h"
#include <set>
#include <string>
#include <sstream>
using namespace std;

Clothing::Clothing(const string category, const string name, double price, 
      int qty, string size, string brand) 
      : Product(category, name, price, qty){
        size_ = size; //set size_ to size
        brand_ = brand; //set brand_ to brand 
}

Clothing::~Clothing(){ }; //deconstructor

set<string> Clothing::keywords() const{
  set<string> wordSet;
  set<string> tempWords;
  wordSet = parseStringToWords(name_);
  tempWords = parseStringToWords(brand_);
  set<string>::iterator it;
  for(it = tempWords.begin(); it != tempWords.end(); ++it){
    wordSet.insert(*it);
  } 
  return wordSet;
}
    
string Clothing::displayString() const{
  stringstream s1, s2;
  s1 << price_;
  s2 << qty_;
   //displating products info
  //<name>
  //Size: <size> Brand: <brand>
  //<price> <quantity> left.
  string infoString = name_ + "\n" +
                      "Size: " + size_ + " Brand: " + brand_ + "\n" +
                      s1.str() + " " + s2.str() + " left.";
  return infoString;
}
void Clothing::dump(ostream &os) const{
  Product::dump(os);
  os << size_ << "\n"
     << brand_ << endl;
}
