#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>
using namespace std;

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
//pushfront
void ULListStr::push_front(const std::string& val){
  if(size_ == 0){
    Item* newNode = new Item;
    head_ = newNode;
    tail_ = newNode;
    head_->first = 0;
    head_->last = 1;
    head_->val[head_->first] = val;
    size_++;
  }
  else if(head_->first == 0){
    Item* newNode = new Item;
    head_->prev = newNode;
    newNode->next = head_;
    newNode->prev = NULL;
    head_ = newNode;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val;
    size_++;
  }
  else{
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  }
}
//pushback
void ULListStr::push_back(const std::string& val){
  if(size_==0){
    Item* newNode = new Item;
    head_ = newNode;
    tail_ = newNode;
    head_->val[head_->last] = val;
    head_->last++;
    size_++;
  }
  //if the Node alreday exists and full
  else if(tail_->last == ARRSIZE){
    Item* newNode = new Item;
    tail_->next = newNode;
    newNode->prev = tail_;
    newNode->next = NULL;
    tail_ = newNode;
    newNode->val[newNode->last] = val;
    newNode->last++;
    size_++;
  }
  //if the Node already exists and not full
  else{
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }
}

//popfront
void ULListStr::pop_front(){
  if(size_ == 0) return;
  size_ = size_-1;//its pop(coming out)
  if(++(head_->first) == head_->last){
    if(size_ != 0){
      head_ = head_-> next;
      delete head_->prev;
      head_->prev = NULL;
    }
    else{//when there is just one Item
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
  }
}

//popback
void ULListStr::pop_back(){
  if(size_ == 0) return;//there is no Item
  size_ = size_-1;//there is at least one Item
  tail_->last--;
  if(tail_->first == tail_->last){
    if(size_ != 0){
      tail_->last = ARRSIZE;
      tail_ = tail_-> prev;//tail become the previous one
      delete tail_->next;//now the tail is the previous one so delete with tail->next which was original tail
      tail_->next = NULL; 
    }
    else{//when there is just one Item
      delete tail_;
      head_ = NULL;
      tail_ = NULL;
    }
  }
}

//return first element of array in linked list
std::string const & ULListStr::front() const{
  if(size_ == 0) return NULL;
  return head_->val[head_->first];
}

//return last element of array in linked list
std::string const & ULListStr::back() const{
  if(size_ == 0) return NULL;
  int ogIdx = tail_->last - 1; //as last data item is exclusive and one beyond the last value
  return tail_->val[ogIdx];
}

//getValatLoc
std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc >= size_) return NULL;
  for(Item* currItem = head_; currItem != NULL; currItem = currItem->next){
    if(currItem->last - currItem->first > loc){
      return &(currItem->val[currItem->first + loc]);
    }
    loc -= currItem->last - currItem->first;
  }
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}