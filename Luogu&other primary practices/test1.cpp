#include <iostream>
using namespace std;
void func(int *n, int *x)
{
    int temp;
    temp=*n;
    *n=*x;
    *x=temp;
}

int main()
{
    int a=100;
    int b=9;
    int *a1 = &a;
    int *a2 = &b; 
    func(a1,a2);
    cout<<*a1<<endl<<*a2<<endl;
}