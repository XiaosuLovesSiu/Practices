#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int sum=0,count=0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin >> a;
        if(a==-1) break;
        if((a%3==0||a%5==0) && a<1000)
        {
            sum+=a;
            count++;
        }
        if(count==10) break;
    }
    cout << sum;
    return 0;
}