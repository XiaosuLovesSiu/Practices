#include <iostream>
#include <vector>
using namespace std;
int jc(int n)
{
    int res=1;
    for(;n>0;n--)
    {
        res*=n;
    }
    return res;
}
int main()
{
    for(int i=0;i<10;i++)
    {
        cout<<i<<"! = "<<jc(i)<<endl;
    }
    return 0;
}