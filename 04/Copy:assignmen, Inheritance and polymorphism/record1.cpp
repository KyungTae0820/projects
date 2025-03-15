#include <iostream>
#include <string>
#include <vector>
#include "course.h"
#include "scalecourse.h"
#include "passfailcourse.h"
#include "student.h"

using namespace std;

int main(int argc, char *argv[]){
  //course 1
  vector<double> c1_scales = {94.0,82.0,70.0,56.0,0.0};
  ScaleCourse c1("CS 103L",4,c1_scales);
  //course 2
  PassFailCourse c2("CS 170",3,60);
  //course 3
  vector<double> c3_scales = {90.0,80.0,70.0,60.0,0.0};
  ScaleCourse c3("CS 270",4,c3_scales);
  //course 4
  vector<double> c4_scales = {92.5,82.5,70.0,60.0,0.0};
  ScaleCourse c4("CS 585",4,c4_scales);
  //course 5
  PassFailCourse c5("DSCI 250",2,70);
  //course and grade
  Student stu1("Tommy Trojan");
  stu1.setMajor("Computer Science");
  stu1.addCourse(&c1,94);//A
  stu1.addCourse(&c2,59);//NP
  stu1.addCourse(&c3,90.5);//A
  stu1.addCourse(&c4,92);//B
  stu1.addCourse(&c5,70);//P
  stu1.printReport();
  //Total credit = 4+4+4+2 = 14
  //GPA = (4*4+4*4+4*3)/(4+4+4) = 3.67
  return 0;
}
