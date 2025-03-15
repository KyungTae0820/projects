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
  vector<double> c1_scales = {95.0,84.0,72.0,51.0,0.0};
  ScaleCourse c1("CTAN 101L",2,c1_scales);
  //course 2
  vector<double> c2_scales = {84.0,70.0,50.0,40.0,0.0};
  ScaleCourse c2("CTAN 301L",3,c2_scales);
  //course 3
  vector<double> c3_scales = {90.0,80.0,70.0,60.0,0.0};
  ScaleCourse c3("CTAN 220",4,c3_scales);
  //course 4
  PassFailCourse c4("CMPP 541a",4,65);
  //course and grade
  Student stu2("Traveler de Hoŕse");
  stu2.setMajor("Cinematic Arts");
  stu2.addCourse(&c1,97.5);//A
  stu2.addCourse(&c2,49.99);//D
  stu2.addCourse(&c3,59);//F
  stu2.addCourse(&c4,60);//NP
  stu2.printReport();
  //Total credit = 2+3+4 = 9
  //GPA = (2*4+3*1+4*0)/(2+3+4) = 1.22
  return 0;
}
