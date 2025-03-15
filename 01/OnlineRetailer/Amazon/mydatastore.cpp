#include "mydatastore.h"
using namespace std;

myDatastore::myDatastore() {} //Constructor

myDatastore::~myDatastore(){ //Desctructor
  set<Product*>::iterator it;
  for(it = allProducts.begin(); it !=allProducts.end(); ++it){
    delete *it;
  }
  map<string, User*>::iterator it2;
  for(it2 = allUsers.begin(); it2 != allUsers.end(); ++it2){
    User* deleteUser = it2->second;
    delete deleteUser;
  }
} 

void myDatastore::addProduct(Product* p){
  allProducts.insert(p);
  set<string> pKey = p->keywords();
  set<string>::iterator it;
  for(it = pKey.begin(); it != pKey.end(); ++it){
      findProducts[*it].insert(p); 
  }
}

void myDatastore::addUser(User* u){
  allUsers.insert(make_pair(u->getName(), u));
}

vector<Product*> myDatastore::search(vector<string>& terms, int type){
  set<Product*> searchingProduct;
  vector<string>::iterator it;
  bool firstTerm = true;
  for(it = terms.begin(); it != terms.end(); ++it){
    if(findProducts.find(convToLower(*it)) != findProducts.end()){
       if(firstTerm){//No Item
          searchingProduct = findProducts[convToLower(*it)];
          firstTerm = false;
        }
        else{
          if(type == 1){ //setUnion or
            searchingProduct = setUnion(findProducts[convToLower(*it)],searchingProduct);
          }
          else{
            searchingProduct = setIntersection(findProducts[convToLower(*it)],searchingProduct);
          }
        }
    }
  }
  vector<Product*> searchedProduct(searchingProduct.begin(), searchingProduct.end());
  return searchedProduct;
}

void myDatastore::dump(ostream& ofile){
  //Products
  ofile << "<products>" << endl;
  set<Product*>::iterator it;
  for(it = allProducts.begin(); it != allProducts.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;
  //Users
  ofile << "<users>" << endl;
  map<string, User*>::iterator it2;
  for(it2 = allUsers.begin(); it2 != allUsers.end(); ++it2){
    it2->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void myDatastore::add_to_Cart(string user, Product* p){
  if(allUsers.find(user) != allUsers.end()){
        carts[user].push_back(p);
  }
  else{//when there is not products
    cout << "Invalid request: Cannot Find Products" << endl;
    return;
  }
}

void myDatastore::view_Cart(string user){
  if(carts.find(user) == carts.end()){
    cout << "Invalid username" << endl;
  }
  else if(carts.find(user) != carts.end()){
    for(unsigned int i = 0; i < carts[user].size(); i++){
      cout << "Item " << i+1 << endl; 
      cout << carts[user][i]->displayString() <<endl;
    }
  }
}

void myDatastore::buy_Cart(string user){
  if(carts.find(user) == carts.end()){
    cout << "Invalid username" << endl;
    return;
  }
  else{
    for(unsigned int i = 0; i < carts[user].size(); i++ ){
      if(carts[user][i]->getPrice() <= allUsers[user]->getBalance()){
        if(carts[user][i]->getQty() >= 1){
          carts[user][i]->subtractQty(1);
          double productPrice =  carts[user][i]->getPrice();
          allUsers[user]->deductAmount(productPrice);
          carts[user].erase(carts[user].begin() + i);
          i--;
        }
      }
    }
  }
}