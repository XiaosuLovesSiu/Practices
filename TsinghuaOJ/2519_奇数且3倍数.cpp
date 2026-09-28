#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double res=0.0;
    int a,count=0;
    for(int i=0;i<6;i++)
    {
        cin >> a;
        if(a%2==1 && a%3==0)
        {
            count++;
            res+=a;
        }
    }
    if(count==0) cout << fixed << setprecision(4) << res;
    else cout << fixed << setprecision(4) << res/count;

    return 0;
}