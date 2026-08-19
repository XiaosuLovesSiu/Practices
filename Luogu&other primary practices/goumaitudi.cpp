#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin>>n>>m;
    vector<int> rowSum(n,0);
    vector<int> colSum(m,0);
    int whole=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int temp;
            cin>>temp;
            rowSum.at(i)+=temp;
            colSum.at(j)+=temp;
            whole+=temp;
        }
    }
    int rans=whole,cans=whole;
    for(int rdiv=0;rdiv<n;rdiv++)
    {
        int trc=0;
        for(int k=0;k<=rdiv;k++)
        {
            trc+=rowSum.at(k);
        }
        int sigtrans=whole-2*trc;
        int trans=(sigtrans>=0)?sigtrans:-sigtrans;
        if(trans<rans) rans=trans;
    }
    for(int cdiv=0;cdiv<m;cdiv++)
    {
        int tcc=0;
        for(int k=0;k<=cdiv;k++)
        {
            tcc+=colSum.at(k);
        }
        int sigtcans=whole-2*tcc;
        int tcans=(sigtcans>=0)?sigtcans:-sigtcans;
        if(tcans<cans) cans=tcans;
    }
    int res=(rans>=cans)?rans:cans;
    cout<<res;
    return 0;
}