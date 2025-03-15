#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "student.h"

using namespace std;


Student::Student(string name){
  name_ = name;
}


void Student::setMajor(string major){
  major_ = major;
}

//Add course to the courses_ vector
//Add course_grade to the grades_ vector
void Student::addCourse(Course* course, double course_grade){
  courses_.push_back(course);
  grades_.push_back(course_grade);
}

//Compute the overall GPA
double Student::getTotalGPA() const {
  double GPA = 0.0;
  double sum = 0.0;
  int creditNum = 0;
  for(unsigned int i = 0; i < courses_.size(); i++){
    double a = grades_[i];
    if(courses_[i]->getFinalLetterGrade(a) == "A"){
      sum += 4.0*courses_[i]->getNumCredit();
      creditNum += courses_[i]->getNumCredit();
    }
    else if(courses_[i]->getFinalLetterGrade(a) == "B"){
      sum += 3.0*courses_[i]->getNumCredit();
      creditNum += courses_[i]->getNumCredit();
    }
    else if(courses_[i]->getFinalLetterGrade(a) == "C"){
      sum += 2.0*courses_[i]->getNumCredit();
      creditNum += courses_[i]->getNumCredit();
    }
    else if(courses_[i]->getFinalLetterGrade(a) == "D"){
      sum += 1.0*courses_[i]->getNumCredit();
      creditNum += courses_[i]->getNumCredit();
    }
    else if(courses_[i]->getFinalLetterGrade(a) == "F"){
      sum += 0.0*courses_[i]->getNumCredit();
      creditNum += courses_[i]->getNumCredit();
    }
  }
  GPA = sum/creditNum;
  return GPA; //to be changed.
}

//Get the total course credits.
int Student::getSemesterCourseCredit() const {
  int creditSum = 0;
  for(unsigned int i = 0; i < courses_.size(); i++){
    double a = grades_[i];
    if(courses_[i]->getFinalLetterGrade(a) == "A" ||
       courses_[i]->getFinalLetterGrade(a) == "B" ||
       courses_[i]->getFinalLetterGrade(a) == "C" ||
       courses_[i]->getFinalLetterGrade(a) == "D" ||
       courses_[i]->getFinalLetterGrade(a) == "F" ||
       courses_[i]->getFinalLetterGrade(a) == "P"){
        creditSum += courses_[i]->getNumCredit();
    }
    else{}
  }
  return creditSum; //to be changed.
}

void Student::printReport() const
{
  cout<<"Name: "<<name_<<endl;
  cout<<"Major: "<<major_<<endl;
  cout<<"Courses Taken: "<<endl;
  cout << '|' << setw(10) <<"Course";
  cout << '|' << setw(10) <<"Credit";
  cout << '|' << setw(10) <<"RawGrade";
  cout << '|' << setw(12) <<"LetterGrade";
  cout <<endl;
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  for(size_t i = 0; i < courses_.size(); i++){
    cout << '|' << setw(10) << courses_[i]->getName();
    cout << '|' << setw(10) << courses_[i]->getNumCredit();
    cout << '|' << setw(10) << grades_[i];
    cout << '|' << setw(12) << courses_[i]->getFinalLetterGrade(grades_[i]);
    cout << endl;
  }
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  cout<<"Total Credits: "<<getSemesterCourseCredit()<<endl;
  cout<<"Overall GPA: "<< setprecision(2) << std::fixed << getTotalGPA()<<endl;
}
