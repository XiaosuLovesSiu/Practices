#include <vector>
#include <iostream>
#include <queue>
using namespace std;

bool valid(long long ind, long long sz)
{
    return (0<=ind && ind<sz);
}

int main()
{
    cout << "please input the size of the board(n*n), n<10000." << endl;
    long long sz;
    cin >> sz;
    vector<int> board(sz*sz,-1); 
    cout << "then input where the horse starts." << endl;
    int row,col;
    cin >> row >> col;

    queue<int> q;
    if (valid(row,sz) && valid(col, sz))
    {
        q.push(sz * row + col);
        board[sz * row + col] = 0;
    }
    else
    {
        cout << "invalid input" << endl;
        return 1;
    }
    cout << "queue structed." << endl;
    while(!q.empty())
    {
        int fr=q.front();
        int val=board[fr];
        vector<int> dr{2, 2, 1, 1, -2 ,-2, -1, -1};
        vector<int> dc{1, -1, 2, -2, 1, -1, 2, -2};
        long long r=fr/sz, c=fr%sz;
        for(int i=0;i<8;i++)
        {
            long long n = fr + sz*dr[i] + dc[i];
            if (valid(r + dr[i], sz) && valid(c + dc[i], sz) && board[n] == -1)
            {
                q.push(n);
                board[n] = val + 1;
            }
        }
        q.pop();
    }
    cout << "stimulation finished." << endl;
    int count=0, maxi=0;
    cout << "here's the board." << endl;
    for(int num : board)
    {
        if(num>maxi) maxi=num;
        cout << num;
        count++;
        if(count%sz==0) cout << endl;
    }
    cout << "max of steps cost: " << maxi << endl;
    return 0;
}