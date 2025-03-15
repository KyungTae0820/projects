#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "course.h"
#include "scalecourse.h"
#include "passfailcourse.h"
#include "student.h"

using namespace std;

//******************************************
//this file is complete, please don't change anything
//******************************************

int main(int argc, char *argv[]){
  if(argc < 2) {
    cout << "Please provide a test argument." << endl;
    return 1;
  }
  int test = atoi(argv[1]);
  if(test == 1) {
    //course 1
    PassFailCourse c1("DSCI 250",2,70);
    //course 2
    vector<double> c2_scales = {90.0,80.0,70.0,60.0,0.0};
    ScaleCourse c2("CS 270",4,c2_scales);
    //course 3
    PassFailCourse c3("CS 170",3,60);
    //course 4
    vector<double> c4_scales = {94.0,82.0,70.0,56.0,0.0};
    ScaleCourse c4("CS 103L",4,c4_scales);
    //course 5
    vector<double> c5_scales = {92.5,82.5,70.0,60.0,0.0};
    ScaleCourse c5("CS 585",4,c5_scales);
    //course and grade
    Student stu1("Tommy Trojan");
    stu1.setMajor("Computer Science");
    stu1.addCourse(&c1,70);//P
    //  stu1.addCourse(&c2,90.5);//A
    stu1.addCourse(&c3,59);//NP
    stu1.addCourse(&c4,94);//A
    stu1.addCourse(&c5,92);//B
    stu1.printReport();
    //Total credit = 4+4+4+2 = 14
    //GPA = (4*4+4*4+4*3)/(4+4+4) = 3.67

  }
  else if(test == 2) {
    //course 1
    vector<double> c1_scales = {84.0,70.0,50.0,40.0,0.0};
    ScaleCourse c1("CTAN 301L",3,c1_scales);
    //course 2
    PassFailCourse c2("CMPP 541a",4,65);
    //course 3
    vector<double> c3_scales = {95.0,84.0,72.0,51.0,0.0};
    ScaleCourse c3("CTAN 101L",2,c3_scales);
    //course 3
    vector<double> c4_scales = {90.0,80.0,70.0,60.0,0.0};
    ScaleCourse c4("CTAN 220",4,c4_scales);
    //course and grade
    Student stu2("Traveler de Hoŕse");
    stu2.setMajor("Cinematic Arts");
    stu2.addCourse(&c1,49.99);//D
    stu2.addCourse(&c2,60);//NP
  //  stu2.addCourse(&c3,97.5);//A
    stu2.addCourse(&c4,59);//F
    stu2.printReport();
    //Total credit = 3+4 = 7
    //GPA = (2*4+3*1+4*0)/(2+3+4) = 0.43

  }
  return 0;
}
