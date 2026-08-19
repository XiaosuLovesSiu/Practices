#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int memo[1005][105];
int tcost[105],value[105];

unsigned long long bestplan(int time,int herbnum,int index)
{
    unsigned long long result=0;
    if(herbnum<=index || time<=0) return 0;
    if (memo[time][index] != -1) return memo[time][index];
    if(time<tcost[index]) return bestplan(time,herbnum,index+1);
    unsigned long long take = value[index]+bestplan(time-tcost[index],herbnum,index+1);
    unsigned long long skip = bestplan(time,herbnum,index+1);
    result = (take > skip)? take:skip;
    memo[time][index]=result;
    return result;
}
int main()
{
    int time,herbnum;
    cin >> time >> herbnum;
    unsigned long long zvalue=0;
    memset(memo,-1,sizeof(memo));
    for(int i=0;i<herbnum;i++)
    {
        cin >> tcost[i] >> value[i];
    }
    zvalue = bestplan(time,herbnum,0);
    cout << zvalue <<endl;
    return 0;
}