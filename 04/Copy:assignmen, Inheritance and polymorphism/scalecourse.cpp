#include <iostream>
#include <string>
#include <vector>
#include "scalecourse.h"

using namespace std;

ScaleCourse::ScaleCourse(string name_, int credit_, vector<double> scales_) 
  : Course(name_, credit_)
  {
      scales = scales_;
  }

string ScaleCourse::getFinalLetterGrade(double grade){
  if(grade >= scales[0]){
    return "A";
  }
  else if(scales[1] <= grade && grade < scales[0]){
    return "B";
  }
  else if(scales[2] <= grade && grade < scales[1]){
    return "C'";
  }
  else if(scales[3]<= grade && grade < scales[2]){
    return "D";
  }
  return "F";
}