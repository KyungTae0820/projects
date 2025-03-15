#include <iostream>
#include <string>
#include <vector>
#include "course.h"

using namespace std;

Course::Course(string name_, int credit_){
    name = name_;
    credit = credit_;
}
string Course::getName(){
  return name;
}
int Course::getNumCredit(){
  return credit;
}
// string Course::getFinalLetterGrade(double grade)
// {
//   if(grade >= 94.0){
//     return "A";
//   }
//   else if(82.0 <= grade && grade < 94.0){
//     return "B";
//   }
//   else if(70.0 <= grade && grade < 82.0){
//     return "C";
//   }
//   else if(56.0 <= grade && grade < 70.0){
//     return "D";
//   }
//   return "F";
// }

