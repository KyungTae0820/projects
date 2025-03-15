#ifndef BOOK_H
#define BOOK_H
#include "product.h"


using namespace std;


class Book : public Product{
  public: 
    Book(const string category, const string name, 
    double price, int qty,
    string isbn, string author);
    ~Book(); //deconstructor
    //implementing the keywords() which returns the appropriate keywords to index the product
    set<string> keywords() const;
    //displayString() [to create a string that contains the product info]
    string displayString() const;
    //dump() [that outputs the database format of the product info]
    void dump(ostream &os) const;

  private:
    string isbn_;
    string author_;
};
#endif
