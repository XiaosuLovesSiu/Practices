#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
int xb,yb,xh,yh;
vector<int> v(2,0);
vector<vector<int>> u(9,v);
long long memo[10000]; //memo[xt*25+yt]表示memo[xt][yt]
long long routenum(int xt,int yt)
{
    if(xt<0||yt<0||xt>xb||yt>yb) return 0;
    else if (memo[xt*25+yt]!=-1) return memo[xt*25+yt];
    else if(xt==xb&&yt==yb) return 1;
    else if(xt==xb&&yt<yb) memo[xt*25+yt] = routenum(xb,yt+1);
    else if(yt==yb&&xt<xb) memo[xt*25+yt] = routenum(xt+1,yb);
    else memo[xt*25+yt]=routenum(xt+1,yt)+routenum(xt,yt+1);
    return memo[xt*25+yt];
}
int main()
{
    cin >> xb >> yb >> xh >> yh;
    
    u[0][0]=xh;
    u[1][0]=xh+1;
    u[2][0]=xh+1;
    u[3][0]=xh-1;
    u[4][0]=xh-1;
    u[5][0]=xh+2;
    u[6][0]=xh+2;
    u[7][0]=xh-2;
    u[8][0]=xh-2;

    u[0][1]=yh;
    u[1][1]=yh+2;
    u[2][1]=yh-2;
    u[3][1]=yh+2;
    u[4][1]=yh-2;
    u[5][1]=yh+1;
    u[6][1]=yh-1;
    u[7][1]=yh+1;
    u[8][1]=yh-1;

    memset(memo,-1,sizeof(memo));
    memo[xb*25+yb]=1;
    for(int i=0;i<9;i++)
    {
        if(u[i][0]>=0&&u[i][0]<=xb&&u[i][1]>=0&&u[i][1]<=yb) memo[u[i][0]*25+u[i][1]]=0;
    }
    cout << routenum(0,0) << endl;
    return 0;
}