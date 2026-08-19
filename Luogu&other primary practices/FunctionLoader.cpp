#include <iostream>
using namespace std;
int sum(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int avr(int a, int b) {
    return (a + b) / 2;
}
int comb(int n,int p)
{
    int fenzi=1,fenmu=1;
    for(int i=1;i<=p;i++)
    {
        fenzi*=(n-i+1);
        fenmu*=i;
    }
    return fenzi/fenmu;
}
int compare(int a, int b)
{
    if(a>b)
    {
        return 1;
    }
    else if (a<b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
void fLoader(string i,int a, int b)
{
    if(i=="sum")
    {
        cout << sum(a,b) << endl;
    }
    else if(i=="subtract")
    {
        cout << subtract(a,b) << endl;
    }
    else if(i=="avr")
    {
        cout << avr(a,b) << endl;
    }
    else if(i=="comb")
    {
        cout << comb(a,b) << endl;
    }
    else if(i=="compare")
    {
        cout << compare(a,b) << endl;
    }
    else
    {
        cout << "Unable to find the function" << endl;
    }
}
int main()
{
    string i;
    int a,b;
    cout << "name of function:" << endl;
    cin >> i;
    cout << "value of variable a and b:" << endl;
    cin >> a >> b;
    fLoader(i,a,b);
    return 0;
}