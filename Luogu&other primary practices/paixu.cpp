#include <iostream>
using namespace std;
void s2(int &i, int &j)
{
    if(i>j)
    {
        int t;
        t=i;
        i=j;
        j=t;
    }
}
void sThree(int &i, int &j, int &k)
{
    s2(i, j);
    s2(j, k);
}
int main()
{
    int i, j, k;
    cin >> i >> j >> k;
    sThree(i,j,k);
    cout << "i=" << i << " j=" << j <<" k=" << k <<endl;
    return 0;
}