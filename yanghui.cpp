#include <iostream>
using namespace std;
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

int main() 
{
    int times;
    cin >> times;
    int i0=1;
    int row=1;
    while(i0<=times)
    {
        for(int i=1;i<=row;i++)
        {
            cout << comb(row-1,i-1) << " ";
        }
        row++;
        cout << endl;
        i0++;
    }
    
    cout << endl;
}

