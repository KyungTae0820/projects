#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"


using namespace std;


class Movie : public Product{
  public: 
    Movie(const string category, const string name, 
    double price, int qty,
    string genre, string rating);
    ~Movie(); //deconstructor
    //implementing the keywords() which returns the appropriate keywords to index the product
    set<string> keywords() const;
    //displayString() [to create a string that contains the product info]
    string displayString() const;
    //dump() [that outputs the database format of the product info]
    void dump(ostream &os) const;

  private:
    string genre_;
    string rating_;
};
#endif