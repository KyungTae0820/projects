#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"

using namespace std;

Str::Str(){
    data_ = new char[1];
    data_[0] = '\0';
    this->size_ = 0;
}
Str::Str(const Str& s){
    data_ = new char[s.size()+1];
    strcpy(data_, s.data_);
    // for(int i = 0; i <len; i++){
    //   data_[i] = s[i];
    // }
    // data_[len] = '\0';
    size_ = s.size();
}
Str::Str(const char* s){
  if(s == NULL){
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
  }
  else{
    data_ = new char[strlen(s)+1];
    strcpy(data_, s);
    // for(int i = 0; i <len; i++){
    //   data_[i] = s[i];
    // }
    // data_[len] = '\0';
    size_ = strlen(s);
  }
}
Str::~Str(){
  delete [] data_;
}
size_t Str::size() const{
  // int i = 0;
  // while(data_[i] != '\0'){
  //   i++;
  // }
  return size_;
}
Str& Str::operator=(const Str& s){
  if(this == &s){//s refers to rhs
    return *this;
  }
  if(data_ != NULL){
     delete [] data_;
  }
  data_ = new char[s.size_+1];
  strcpy(data_, s.data_);
  size_ = s.size();
  return *this;
}
Str& Str::operator=(const char* s){
  if(data_ != NULL){
      delete [] data_;
  }
  if(s == NULL){
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
  }
  else{//s refers to rhs
    size_ = strlen(s);
    data_ = new char[size_+1];
    strcpy(data_, s);
  }
  return *this;
}
Str& Str::operator+=(const Str& s){
  // char* ch = new char[this->size()];
  // int count = 0;
  // strcpy(ch, this->data_);
  // delete [] data_;
  // int len = strlen(ch) + s.size();
  // data_ = new char[len+1];
  // for(unsigned int i = 0; i < strlen(ch); i++){
  //   this->data_[i] = ch[i];
  // }
  // for(int i = strlen(ch); i < len; i++){
  //   this->data_[i] = s.data_[count];
  //   count++;
  // }
  // this->data_[len] = '\0';
  // this->size_ = this->size();
  // delete [] ch;
  // return *this;
  size_ += s.size();
  char* ch = new char[size_+1];
  strcpy(ch, this->data_);
  strcat(ch, s.data_);
  delete [] data_;
  data_ = ch;
  return *this;
}
Str& Str::operator+=(const char* s){
  // char* ch = new char[this->size()];
  // int count = 0;
  // strcpy(ch, this->data_);
  // delete [] data_;
  // int len = strlen(ch) + strlen(s);
  // data_ = new char[len+1];
  // for(unsigned int i = 0; i < strlen(ch); i++){
  //   this->data_[i] = ch[i];
  // }
  // for(int i = strlen(ch); i <= len; i++){
  //   this->data_[i] = s[count];
  //   count++;
  // }
  // this->data_[len] = '\0';
  // this->size_ = this->size();
  // delete [] ch;
  // return *this;
  if(s == NULL){
    return *this;
  }
  size_ += strlen(s);
  char* ch = new char[size_+1];
  strcpy(ch, this->data_);
  strcat(ch, s);
  delete [] data_;
  data_ = ch;
  return *this;
}
Str Str::operator+(const Str& rhs) const{//const should not modified
  Str temp(*this);
  temp += rhs;
  return temp;
}
Str Str::operator+(const char* rhs) const{
  Str temp(*this);
  temp += rhs;
  return temp;
}
bool Str::operator==(const Str &rhs) const{
  if(this->size() == rhs.size()){
    if(strcmp(this->data_, rhs.data_) == 0){
      return true;
    }
  }
  return false;
}
bool Str::operator==(const char* rhs) const{
  if(this->size() == strlen(rhs)){
    if(strcmp(this->data_, rhs) == 0){
      return true;
    }
  }
  return false;
}
bool Str::operator!=(const Str &rhs) const{
  if(this->size() != rhs.size()){
    return true;
  }
  else if(this->size() == rhs.size()){
    if(strcmp(this->data_, rhs.data_) != 0){
      return true;
    }
  }
  return false;
}
bool Str::operator!=(const char* rhs) const{
  if(this->size() != strlen(rhs)){
    return true;
  }
  else if(this->size() == strlen(rhs)){
    if(strcmp(this->data_, rhs) != 0){
      return true;
    }
  }
  return false;
}

const char* Str::data() const
{
  return data_;
}

char& Str::operator[](unsigned int i)
{
  if(i >= size_ ){
    throw std::out_of_range("Index is out of range");
  }
  return data_[i];
}

char const & Str::operator[](unsigned int i) const
{
  if(i >= size_ ){
    throw std::out_of_range("Index is out of range");
  }
  return data_[i];
}

bool Str::operator<(const Str &rhs) const
{
  return (strcmp(data_, rhs.data_) < 0);
}

bool Str::operator>(const Str &rhs) const
{
  return (strcmp(data_, rhs.data_) > 0);
}

std::istream& operator>>(std::istream& istr, Str& s)
{
  std::string stemp;
  istr >> stemp;
  s = stemp.c_str();
  return istr;
}

//Added implementation of operator <<
std::ostream& operator<<(std::ostream& ostr, const Str& s)
{
  ostr << s.data_;
  return ostr;
}