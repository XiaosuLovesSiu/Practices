#include <iostream>
#include <cmath>
#include <bitset>
using namespace std;
int main()
{
    //unsigned long long i=pow(15,10);
    //cout << i <<endl;
    int k,N;
    cin >> k >> N;
    bitset<10> b(N);
    unsigned long long ans = 0;
    for(int i=0;i<=9;i++)
    {
        ans+=b[i]*pow(k,i);
    }
    cout << ans <<endl;
    return 0;
}