#include <iostream>
#include "quad.h"
using namespace std;

int main()
{
    Point p0[4] = {{-1,-1}, {4,-1}, {5,5}, {0,5}};

    Quad q0(p0);
    cout << "q0 isValid returns " << q0.isValid() << endl;
    cout << q0.conv_to_string() << endl;

    Quad q1;
    q1.setPoint(0,{0,0});
    q1.setPoint(1,{3,0});
    q1.setPoint(2,{5,6});
    cout << "q1 isValid returns " << q1.isValid() << endl;
    q1.setPoint(3,{2,6});
    cout << "q1 isValid returns " << q1.isValid() << endl;

    // Add more testing code
    Quad q2;
    q2.setPoint(0,{0,1});
    q2.setPoint(1,{2,0});
    q2.setPoint(2,{5,6});
    cout << "q2 isValid returns " << q2.isValid() << endl;
    q2.setPoint(3,{2,6});
    cout << "q2 isValid returns " << q2.isValid() << endl;
    
    Quad q3;
    q3.setPoint(0,{0,1});
    q3.setPoint(1,{1,1});
    q3.setPoint(2,{1,0});
    cout << "q3 isValid returns " << q3.isValid() << endl;
    q3.setPoint(3,{0,0});
    cout << "q3 isValid returns " << q3.isValid() << endl;

    
    
    return 0;
}
