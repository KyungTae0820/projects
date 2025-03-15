#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"


using namespace std;


class Clothing : public Product{
  public: 
    Clothing(const string category, const string name, 
    double price, int qty,
    string size, string brand);
    ~Clothing(); //deconstructor
    //implementing the keywords() which returns the appropriate keywords to index the product
    set<string> keywords() const;
    //displayString() [to create a string that contains the product info]
    string displayString() const;
    //dump() [that outputs the database format of the product info]
    void dump(ostream &os) const;

  private:
    string size_;
    string brand_;
};
#endif