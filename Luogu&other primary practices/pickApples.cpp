#include <iostream>
using namespace std;
int main()
{
    int h[10];
    cin >> h[0] >> h[1] >> h[2] >> h[3] >> h[4] >> h[5] >> h[6] >> h[7] >> h[8] >> h[9];
    int reach;
    cin >> reach;
    int realreach = reach+30;
    int num = 0;
    for(int i=0;i<10;i++)
    {
        if(h[i] <= realreach)
        {
            num++;
        }
    }
    cout << num << endl;
    return 0;
}