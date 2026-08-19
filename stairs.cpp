#include <iostream>
using namespace std;
int stairs(int level)
{
    if(level==1)
    {
        return 1;
    }
    else if(level==2)
    {
        return 2;
    }
    else
    {
        return stairs(level-1) + stairs(level-2);
    }
}

int main()
{
    int n;
    cin >> n;
    cout << stairs(n) << endl;
    return 0;
}