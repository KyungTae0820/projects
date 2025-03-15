#ifndef SCALECOURSE_H
#define SCALECOURSE_H


#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

class ScaleCourse : public Course{
  public:
    ScaleCourse(string name_, int credit_, vector<double> scales_);
    string getFinalLetterGrade(double grade);

  private:
    vector<double> scales;
};


#endif