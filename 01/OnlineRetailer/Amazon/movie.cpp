#include <iostream>
#include "movie.h"
#include "util.h"
#include <set>
#include <string>
#include <sstream>
using namespace std;

Movie::Movie(const string category, const string name, double price, 
      int qty, string genre, string rating) 
      : Product(category, name, price, qty){
        genre_ = genre; //set genre_ to genre
        rating_ = rating; //set rating_ to rating 
}

Movie::~Movie(){ } //deconstructor

set<string> Movie::keywords() const{
  set<string> wordSet;
  wordSet = parseStringToWords(name_);
  string cSrc = convToLower(genre_);
  wordSet.insert(cSrc);
  return wordSet;
}
    
string Movie::displayString() const{
  stringstream s1, s2;
  s1 << price_;
  s2 << qty_;
   //displating products info
  //<name>
  //Genre: <genre> Rating: <rating>
  //<price> <quantity> left.
  string infoString = name_ + "\n" +
                      "Genre: " + genre_ + " Rating: " + rating_ + "\n" +
                      s1.str() + " " + s2.str() + " left.";
  return infoString;
}
void Movie::dump(ostream &os) const{
  Product::dump(os);
  os << genre_ << "\n"
     << rating_ << endl;
}
