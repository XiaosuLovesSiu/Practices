//待完成

#include <string>
#include <iostream>
using namespace std;

int main()
{
    int delta;
    cin >> delta;
    delta%=26;
    string pri;
    string res;
    char ch;
    while(cin >> ch)
    {
        pri.push_back(ch);
    }
    for(char ch : pri)
    {
        res.push_back(ch);
    }
}