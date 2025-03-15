#ifndef PASSFAILCOURSE_H
#define PASSFAILCOURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

class PassFailCourse : public Course{
  public:
    PassFailCourse(string name_, int credit_, double threshold_);
    string getFinalLetterGrade(double grade);

  private:
    double threshold;
};


#endif