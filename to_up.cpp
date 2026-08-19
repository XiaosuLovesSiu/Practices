#include <iostream>
using namespace std;
char toup(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 32;
    }
    else
    {
        return c;
    }
}
int main()
{
    char c0;
    cin >> c0;
    cout << toup(c0) << endl;
    return 0;
}