#include <iostream>
#include "book.h"
#include "util.h"
#include <set>
#include <string>
#include <sstream>
using namespace std;

Book::Book(const string category, const string name, double price, 
      int qty, string isbn, string author) 
      : Product(category, name, price, qty){
        isbn_ = isbn; //set isbn_ to isbn
        author_ = author; //set author_ to author 
}

Book::~Book(){ } //deconstructor

set<string> Book::keywords() const{
  set<string> wordSet;
  set<string> tempWords;
  wordSet = parseStringToWords(name_);
  wordSet.insert(isbn_);
  tempWords = parseStringToWords(author_);
  set<string>::iterator it;
  for(it = tempWords.begin(); it != tempWords.end(); ++it){
    wordSet.insert(*it);
  } 
  return wordSet;
}
    
string Book::displayString() const{
  stringstream s1, s2;
  s1 << price_;
  s2 << qty_;
   //displating products info
  //<name>
  //Author: <author> ISBN: <isbn>
  //<price> <quantity> left.
  string infoString = name_ + "\n" +
                      "Author: " + author_ + " ISBN: " + isbn_ + "\n" +
                      s1.str() + " " + s2.str() + " left.";
  return infoString;
}
void Book::dump(ostream &os) const{
  Product::dump(os);
  os << isbn_ << "\n"
     << author_ << endl;
}
