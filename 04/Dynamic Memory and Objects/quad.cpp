#include <iostream>
#include <cmath>
#include <cstdlib>//for abs
#include "quad.h"
using namespace std;

// Global score helper functions for Quad member functions.
// Since I define at the top, and these are only meant to be used
// internally, I will forego the prototype

// Returns true if two doubles are within 0.001 of each other
//  Should be used for all equality and non-equality comparison
//  of doubles
bool same(double a, double b) 
{
    if(abs(a-b) < 0.001){
        return true;
    }
    return false;
}

//Returns the distance between two points
double dist(Point a, Point b) 
{
    return sqrt( pow(a.px-b.px,2) + pow(a.py-b.py,2));
}


// Quad member function definitions
Quad::Quad()
{
    for(int i=0; i < 4; i++){
        pts_[i].px = 0; // give default values;
        pts_[i].py = 0; // give default values;
        boolp[i] = false;
    }
}
Quad::Quad(Point mypts[])
{
    for(int i=0; i < 4; i++){
        pts_[i] = mypts[i];
        boolp[i] = true;
    }
}

double Quad::perim() const{
    Point A = pts_[0];
    Point B = pts_[1];
    Point C = pts_[2];
    Point D = pts_[3];
    
    double a = dist(A,B);
    double b = dist(B,C);
    double c = dist(C,D);
    double d = dist(D,A);
    return a+b+c+d;
}

double Quad::area() const{
  if(isRectangle() == true || isSquare() == true){
    Point A = pts_[0];
    Point B = pts_[1];
    Point C = pts_[2];

    double a = dist(A,B);
    double b = dist(B,C);
    return a*b;
  }
  else if(isRhombus() == true){
    Point A = pts_[0];
    Point B = pts_[1];
    Point C = pts_[2];
    Point D = pts_[3];

    double a = dist(A,C);
    double b = dist(B,D);
    return (a*b)/2;
  }
  else{//isParallelogram calculation
    Point A = pts_[0];
    Point B = pts_[1];
    Point C = pts_[2];
    Point D = pts_[3];

    double totalTheta = getInteriorAngle(1, 0, 3) + getInteriorAngle(1, 2, 3);
    double a = dist(A,B);
    double b = dist(B,C);
    double c = dist(C,D);
    double d = dist(D,A);
    double s = (a+b+c+d)/2;
    return sqrt((s-a)*(s-b)*(s-c)*(s-d)- a*b*c*d*pow(cos(totalTheta/2),2));
  }
}
//setPoint - member function 1
void Quad::setPoint(int idx, Point p){
    pts_[idx] = p;
    boolp[idx] = true;
}
//isValid - member function 2
bool Quad::isValid() const{
  //Check if all 4 points have been set
  for(int i = 0; i < 4; i++){
    if(boolp[i] == false){
        return false;
    }
  }
  //check whether total sum of angle is 360 or not
  double angleSum = 0.0;
  if((getInteriorAngle(0, 1, 2)< 180) && (getInteriorAngle(1, 2, 3)< 180) 
      && (getInteriorAngle(2, 3, 0)< 180) && (getInteriorAngle(3, 0, 1)< 180)){
    angleSum += getInteriorAngle(0,1,2);
    angleSum += getInteriorAngle(1,2,3);
    angleSum += getInteriorAngle(2,3,0);
    angleSum += getInteriorAngle(3,0,1);
  }
  else if((getInteriorAngle(1, 0, 3)< 180) && (getInteriorAngle(0, 3, 2)< 180) 
      && (getInteriorAngle(3, 2, 1)< 180) && (getInteriorAngle(2, 1, 0)< 180)){
    angleSum += getInteriorAngle(1,0,3);
    angleSum += getInteriorAngle(0,3,2);
    angleSum += getInteriorAngle(3,2,1);
    angleSum += getInteriorAngle(2,1,0);
  }
  //Check the value of angle sum
  if(same(angleSum, 2*M_PI)){
    return true;
  }
  else{
    return false;
  }
}

//Code to Check which quadrilateral is
bool Quad::isParallelogram() const {
  if(isValid() == false){
    return false;
  }
  Point A = pts_[0];
  Point B = pts_[1];
  Point C = pts_[2];
  Point D = pts_[3];

  double a = dist(A,B);
  double b = dist(B,C);
  double c = dist(C,D);
  double d = dist(D,A);

  if(same(a,c) && same(b,d)){
    return true;
  }
  return false;
}

bool Quad::isRectangle() const{
  if((isParallelogram()==true) && same(getInteriorAngle(0, 1, 2),(M_PI/2)) && same(getInteriorAngle(1, 2, 3),(M_PI/2)) 
      && same(getInteriorAngle(2, 3, 0),(M_PI/2)) && same(getInteriorAngle(3, 0, 1),(M_PI/2))){
        return true;
  }
  return false;
}

bool Quad::isRhombus() const{
  Point A = pts_[0];
  Point B = pts_[1];
  Point C = pts_[2];
  Point D = pts_[3];

  double a = dist(A,B);
  double b = dist(B,C);
  double c = dist(C,D);
  double d = dist(D,A);
  if((isParallelogram()==true) && same(a,b) && same(b,c)&& same(c,d) && same(d,a)){
      return true;
  }
  return false;
}

bool Quad::isSquare() const{
  if(isParallelogram() == true && isRectangle() == true && isRhombus() == true){
    return true;
  }
  return false;
}

std::string Quad::conv_to_string() const
{
    string retval = "";
    if(isValid() == false) {
        return "invalid";
    }
    for(int i = 0; i < 4; i++){
        retval += "(" + to_string(pts_[i].px) + "," + to_string(pts_[i].py) + ")";
      if(i < 3){
        retval += " ";
      }
    }
    return retval;
}

double Quad::getInteriorAngle(int ext1, int vert, int ext2) const
{
    Point B = pts_[ext1];
    Point A = pts_[vert];
    Point C = pts_[ext2];

    double sideAB = dist(A, B);
    double sideAC = dist(A, C);
    double sideBC = dist(B, C);

    double degreeTheta = acos((pow(sideAB,2)+ pow(sideAC,2) - pow(sideBC,2))/(2*sideAB*sideAC)); 
    
    return degreeTheta;
}