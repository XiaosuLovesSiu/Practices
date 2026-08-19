#include <iostream>
#include <iomanip>
using namespace std;
double func(double a, double b, double c, double d,double x)
{
    return a*x*x*x + b*x*x + c*x + d;
}
int main()
{
    double a,b,c,d;
    cin >> a >> b >> c >> d;
    for(double x = -100.005; x <= 100.005; x += 0.001)
    {
        if(func(a,b,c,d,x)*func(a,b,c,d,x+0.001) <= 0)
        {
            cout<<fixed<<setprecision(2)<<x<<" ";
        }
    }
    return 0;
}