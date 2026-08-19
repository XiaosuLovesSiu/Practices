#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    int a;//始发站上车数
    int n;//车站数
    int m;//终点站下车人数
    int x;//要求的hu[x]
    int res;
    cin>>a>>n>>m>>x;
    vector<vector<int>> up(n+1,vector<int>(2,0));//up[i][j]表示第i站上车人数的j次项系数
    up[1][0]=a;
    vector<vector<int>> hu(n+1,vector<int>(2,0));//hu[i][j]表示第i站开出时车上人数的j次项系数
    up[2][1]=1;
    for(int i=3;i<=n-1;i++)
    {
        up[i][0]=up[i-1][0]+up[i-2][0];
        up[i][1]=up[i-1][1]+up[i-2][1];
    }
    hu[1][0]=a;
    hu[2][0]=a;
    if(x==n) res=0;
    else if(x==1||n==3) res=a;
    else 
    {
        for(int i=3;i<=n-1;i++)
        {
            hu[i][0]=hu[i-1][0]+up[i-2][0];
            hu[i][1]=hu[i-1][1]+up[i-2][1];
        }
        int t=(m-hu[n-1][0])/hu[n-1][1];
        res=hu[x][1]*t+hu[x][0];
    }
    cout << res << endl;
    return 0;
}