#include <iostream>
using namespace std;
int concat(int i, int j)
{
    cout << i << j << endl;
    return 0;
}
int main()
{
    int i, j;
    cin >> i >> j;
    concat(i, j);
    return 0;
}