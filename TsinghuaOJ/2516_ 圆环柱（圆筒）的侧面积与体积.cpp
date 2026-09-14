#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI=3.141592653589793;

double sideArea(double R, double r,double h)
{
    return 2*PI*(R+r)*h;
}

double volume(double R, double r, double h)
{
    return PI*(R*R-r*r)*h;
}

int main()
{
    double R=5.0,r=2.0,h=10.0;
    cout << fixed << setprecision(5) << sideArea(R,r,h) << " " << volume(R,r,h) << endl;
    R=3.5;
    r=2.5;
    h=5.5;
    cout << fixed << setprecision(5) << sideArea(R,r,h) << " " << volume(R,r,h) << endl;
    R=0.1;
    r=0.001;
    h=11.1;
    cout << fixed << setprecision(5) << sideArea(R,r,h) << " " << volume(R,r,h) << endl;
    return 0;
}