#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
#include "course.h"

class Student{
  public:
    Student(std::string name);
    void setMajor(std::string major);
    void addCourse(Course* course, double course_grade);
    double getTotalGPA() const;
    int getSemesterCourseCredit() const;
    void printReport() const;
  private:
    std::string name_;
    std::string major_;
    std::vector<Course*> courses_;
    std::vector<double> grades_;
};

#endif