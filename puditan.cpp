#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
const int m=2e5+5;

int main()
{
    int n;
    cin >> n;

    vector<int> v(5,0);
    vector<vector<int>> u(n+1,v);//u[i][j]表示第i张地毯，j=1,2,3,4分别是地毯的起始点横纵坐标和x,y轴上长度
    for(int i=1;i<=n;i++) cin >> u[i][1] >> u[i][2] >> u[i][3] >> u[i][4];
    int x,y;
    cin >> x >> y;
    int t=-1;
    if(x<=0||y<=0||x>=m||y>=m) cout << -1;
    else
    {
        for(int i=1;i<=n;i++)
        {
            if((u[i][1]+u[i][3])>=x&&x>=u[i][1]&&u[i][2]+u[i][4]>=y&&y>=u[i][2])
            t=i;
        }
    }
    cout << t << endl;
    return 0;
}