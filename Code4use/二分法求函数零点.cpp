#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double e=exp(1.0);
const double pi=acos(-1.0);
const double epsilon=0.0000000001;

double func(double x)
{
    //在这里填入函数表达式。
    return exp(2*x)-x-4;
}
double m_func(double x)
{
    return -func(x);
}

double bs1(double l, double r)
{
    if(r-l<=epsilon) return r;
    //func(l)<0且func(r)>0的情形
    double mid=(l+r)/2;
    if(func(mid)==0) return mid;
    else if(func(mid)>0)
    {
        return bs1(l,mid);
    }
    else return bs1(mid,r);
}

double bs2(double l, double r)
{
    if(r-l<=epsilon) return r;
    //func(l)>0且func(r)<0的情形
    double mid=(l+r)/2;
    if(m_func(mid)==0) return mid;
    else if(m_func(mid)>0)
    {
        return bs2(l,mid);
    }
    else return bs2(mid,r);
}

int main()
{
    double l,r,res=0;
    int pcs;
    cout << "Please input the left and right side of a range, then input your expected precision. The three numbers should be divided by a space." << endl;
    cin >> l >> r >> pcs;
    if(pcs<=0 || pcs>15) cout << "invalid input: precision too high or invalid";
    else
    {
        if(func(l)==0) cout << fixed << setprecision(pcs) << l;
        if(func(r)==0) cout << fixed << setprecision(pcs) << r;
        if(func(l)<0)
        {
            if(func(r)<0) cout << "invalid input: both side of the range have a negative function value.";
            else cout << fixed << setprecision(pcs) << bs1(l,r);
        }
        else
        {
            if(func(r)>0) cout << "invalid input: both side of the range have a positive function value.";
            else cout << fixed << setprecision(pcs) << bs2(l,r);
        }
    }
    return 0;
}