#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course{
  public:
    Course(string name_, int credit_);
    string getName();
    int getNumCredit();
    virtual string getFinalLetterGrade(double grade) = 0;

  private:
    int credit;
    string name;
};
#endif