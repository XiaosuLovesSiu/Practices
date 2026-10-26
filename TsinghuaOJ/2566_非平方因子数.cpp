#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> vec(n+1,1);
    int sdepth=sqrt(n);
    for(int i=2; i<=sdepth; i++)
    {
        int sq=i*i;
        for(int ind=sq; ind<=n; ind+=sq)
        {
            vec[ind]=0;
        }
    }
    int count=0;
    for(int i=1;i<=n;i++)
    {
        if(vec[i]==1) count++;
    }
    cout << count;
    return 0;
}