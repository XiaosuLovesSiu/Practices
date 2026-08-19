#include <iostream>
#include <cmath>
using namespace std;
double tiaohe(int x)
{
    double sum=0;
    for(int i=1;i<=x;i++)
    {
        sum+=1.0/i;
    }
    return sum;
}
int main()
{
    int n;
    cin>>n;
    double sum=0;
    for(long long i=1;i<=pow(3,15);i++)
    {
        sum+=1.0/i;
        if(sum>n)
        {
            cout<<i<<endl;
            break;
        }
    }
    return 0;
}