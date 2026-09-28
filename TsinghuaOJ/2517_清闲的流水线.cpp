#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N,a,res=0;
    cin >> N;
    for(int i=0;i<N;i++)
    {
        cin >> a;
        if(a%2==1)
        {
            res+=(a-a%3);
            cout << a%3;
        }
        else cout << a;
    }
    cout << endl;
    cout << res;
    return 0;
}