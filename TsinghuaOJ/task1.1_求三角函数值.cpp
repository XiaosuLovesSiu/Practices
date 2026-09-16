#include <iostream>
#include <cmath>
using namespace std;

const double pi = acos(-1.0);

double swi(int x)
{
    return x*pi/180;
}

int main()
{
    double a=sin(swi(20));
    double b=cos(swi(20));
    double c=tan(swi(10));
    double d=cos(swi(10));
    cout << a*b-d/c << endl;
    return 0;
}