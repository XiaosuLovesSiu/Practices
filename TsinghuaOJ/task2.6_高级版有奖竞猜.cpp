#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int res=0, count=0;
    int info;
    cin >> info;
    while(info!=0)
    {
        res+=(info%10)*pow(2,count);
        count++;
        info/=10;
    }
    cout << res << endl;
    return 0;
}