#include <iostream>
using namespace std;
int func(int n, int x)
{
    if(n==0)
    {
        return 1;
    }
    else if(n==1)
    {
        return 2*x;
    }
    else
    {
        int t =2*x*func(n-1,x)-(2*n-2)*func(n-2,x);
        return t;
    }
}
int main()
{
    int n;
    int x;
    cin >> n >> x;
    cout << func(n,x) << endl;
    return 0;
}