#include "delist.h"
#include <iostream>

using namespace std;

DEList::DEList(){//constructor
  head = NULL;
}

DEList::~DEList(){//destructor
  while(head != NULL){
    pop_front();
  }
}

bool DEList::empty() const{
  return head == NULL;
}

// returns number of items in the list
int DEList::size() const{
  int count = 0;
  DEItem* temp = head;
  while(temp != NULL){
    temp = temp->next;
    count++;
  }
  return count;
}

// returns front item or -1 if empty list
int DEList::front() const{
  if(head == NULL){
    return -1;
  }
  else{
    return head->val;
  }
}

// returns back item or -1 if empty list
int DEList::back() const{
  if(head == NULL){
    return -1;
  }
  else{
    DEItem* temp = head;
    while(temp->next != NULL){
      temp = temp->next;
    }
    return temp->val;
  }
}

// Adds a new integer to the front of the list
void DEList::push_front(int new_val){
  DEItem* newp = new DEItem();
  if(head == NULL){//empty list
    newp->next = NULL;
    newp->prev = NULL;
    newp->val = new_val;
    head = newp;
  }
  else{//not empty list
    newp->prev = NULL;
    newp->val = new_val;
    newp->next = head;
    head->prev = newp;
    head = newp;
  }
}
// Adds a new integer to the back of the list
void DEList::push_back(int new_val){
  DEItem* newp = new DEItem();
  if(head == NULL){//empty list
    newp->next = NULL;
    newp->prev = NULL;
    newp->val = new_val;
    head = newp;
  }
  else{//not empty list
    DEItem* temp = head;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newp;
    newp->prev = temp;
    newp->val = new_val;
    newp->next = NULL;
  }
}
// Removes the front item of the list (if it exists)
void DEList::pop_front(){
  if(head != NULL){
    DEItem* temp = head;
    if(size() > 1){
      head->next->prev = NULL;
      head = temp->next;
    }
    else{
      head = temp->next;
      temp->next = NULL;
    }
    delete temp;
  }
}
// Removes the back item of the list (if it exists)
void DEList::pop_back(){
  if(head != NULL){
    if(size() > 1){
      DEItem* temp = head;
      while(temp->next != NULL){
        temp = temp->next;
      }
      temp->prev->next = NULL; //(previous of temp)'s next is Null
      delete temp;
    }
    else{
      delete head;
      head = NULL;
    }
  }
}
// Converts the contents of the list to a string with spaces between 
// each element an NO trailing newline (and no space before the 
// first element or after the last element)
std::string DEList::conv_to_string() const{
  string a  = "";
  DEItem* temp = head;

  while(temp != NULL){
    if(temp->next == NULL){
      a += to_string(temp->val);
    }
    else{
      a += to_string(temp->val) + " ";
    }
     temp = temp->next;
  }
  return a;
}
  


