#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<char> string;
    char a;
    while(cin>>a)
    {
        if('0'<=a&&a<='9')
        {
            string.push_back('n');
            string.push_back('u');
            string.push_back('m');
            string.push_back('b');
            string.push_back('e');
            string.push_back('r');
        }
        else string.push_back(a);
    }
    for(char t : string)
    {
        cout<<t;
    }
    cout<<endl;
}