#include <iostream>
using namespace std;
int main() 
{
    int space=3,star=1,i=1;
    for(;i<=4;i++)
    {
        for(int j=1;j<=space;j++)
        {
            cout << " ";
        }
        for(int k=1;k<=star;k++)
        {
            cout << "*";
        }
        cout << endl;
        space--;
        star+=2;
    }
    space=1;
    star=5;
    for(;i>0;i--)
    {
        for(int j=1;j<=space;j++)
        {
            cout << " ";
        }
        for(int k=1;k<=star;k++)
        {
            cout << "*";
        }
        cout << endl;
        space++;
        star-=2;
    }
}