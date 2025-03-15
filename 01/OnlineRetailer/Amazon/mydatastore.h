#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include "datastore.h"
#include <map>
#include "util.h"
#include "db_parser.h"
#include "product.h"

using namespace std;


class myDatastore : public DataStore {
  public:
    myDatastore(); //Constructor
    ~myDatastore(); //Desctructor
    void addProduct(Product* p);
    void addUser(User* u);
    vector<Product*> search(vector<string>& terms, int type);
    void dump(ostream& ofile);
    void add_to_Cart(string user, Product* p);
    void view_Cart(string user);
    void buy_Cart(string user);
    
  private:
    set<Product*> allProducts; //set that cotains all products
    map<string, User*> allUsers; //m that contains all user
    map<string, set<Product*>> findProducts; //find the products that user wants to find
    map<string, vector<Product*>> carts; //cart that individual have corresspoding to name
};
#endif