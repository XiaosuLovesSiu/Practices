#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
int maxim(int a,int b)
{
    if(a>b) return a;
    else return b;
}
int main()
{
    int fnum,l,r,sume=0;
    cin >> fnum >> l >> r;
    vector<int> ene(fnum+1,0);
    for(int i=1;i<=fnum;i++) cin>>ene[i];

    int result[fnum+1][305]; //result[index][sum]为考虑前index份食物后使得剩余和为sum的方案数
    memset(result,0,sizeof(result));
    for(int i=1;i<=fnum;i++) result[i][0]=1;
    result[fnum-1][ene[fnum]]=1;
    for(int index=fnum-1;index>=0;index--)
    {
        for(int i=1;i<=300;i++)
        {
            result[index][i]=result[index+1][i]+result[index+1][maxim(i-ene[index+1],0)];
            if (i-ene[index+1]<0) result[index][i]=result[index][i]-1;
        }
    }
    long res=0;
    for(int j=l;j<=r;j++) res=res+result[0][j];
    cout << res << endl;
    return 0;
}