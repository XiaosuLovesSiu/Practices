#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int length,popu;
int main()
{
    cin >> length >> popu;
    if(popu==0) cout << "0 0";
    else
    {
    vector<int> v(popu+1,0); //v[i]表示第i个士兵的初始位置
    for(int i=1;i<=popu;i++) cin >> v[i];
    sort(v.begin(),v.end());
    int tmin=0;
    for(int i=1;i<=popu;i++)
    {
        if (min(v[i],length+1-v[i])>tmin) tmin=min(v[i],length+1-v[i]);
    }
    int tmax=max(length+1-v[1],v[popu]);

    cout << tmin << " " << tmax << endl;
    return 0;
    }
}