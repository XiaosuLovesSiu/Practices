//dp法
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<long long> stairs(N + 1, 1);
    for (int i = 0; i < M; i++)
    {
        int x;
        cin >> x;
        stairs[x] = 0;
    }
    if(stairs[N]==0)
    {
        cout << 0 << endl;
        return 0;
    }
    else
    {
        for(int j=N-2; j>=0; j--)
        {
            if(stairs[j]==1)
            {
                stairs[j]=stairs[j+1]+stairs[j+2];
            }
        }
        cout << stairs[0] << endl;
    }
    
    return 0;
}