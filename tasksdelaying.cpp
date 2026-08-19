#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
long day,delay,tasknum;
int judge(long machnum,long* p)
{
    vector<long> label(tasknum+1,0);  //0：未呈递；1：已呈递，未完成；2：已呈递并完成
    long check=1,process=0; 
    //check：第check个任务是第一个尚未被呈递的  process；已经完成了第process个ji以前的所有任务
    for(long d=1;d<=day;d++)
    {
        for(long ind=check;ind<=tasknum;ind++)
        {
            if (p[ind]<=d) 
            {
                label[ind]=1;
                check=ind+1;
            }
            else 
            {
                check=ind;
                break;
            }
        }
        long i=1;
        while(i<=machnum && label[process+i]==1 && process+i<=tasknum)
        {
            label[process+i]=2;
            i++;
        }
        process=process+i-1;
        for(long j=process+1;j<=check-1;j++)
        {
            if (p[j]+delay<=d) return 0;
        }
    }
    if(label[tasknum]==2) return 1;
    else return 0;    
}
int main()
{
    cin >> day >> delay >> tasknum ;
    vector<long> v(tasknum+1,0);
    for(long i=1;i<=tasknum;i++)  cin>>v[i];
    //v[i]表示第i个任务被呈递时的天数
    int machnum=0;
    sort(v.begin(),v.end());
    long* p = &v[0];

    long l = 1, r = tasknum;
    while (l+1 < r) {
        long mid = (l + r) / 2;
        if (judge(mid, p))
        {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << endl;
    
    return 0;
}