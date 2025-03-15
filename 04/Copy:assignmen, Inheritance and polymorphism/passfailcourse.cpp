#include <iostream>
#include <string>
#include <vector>
#include "passfailcourse.h"

using namespace std;

PassFailCourse::PassFailCourse(string name_, int credit_, double threshold_) 
    : Course(name_, credit_)
    {
      threshold = threshold_;
    }

string PassFailCourse::getFinalLetterGrade(double grade){
  if(grade >= threshold){
    return "P";
  }
  return "NP";
}