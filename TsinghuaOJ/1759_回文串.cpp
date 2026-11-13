#include <iostream>
#include <vector>

using namespace std;

char isValid(char ch)
{
    if(
        ('0' <= ch && ch <= '9')
        ||('a'<=ch && ch<='z')
    )
    {
        return ch;
    }
    else if('A' <= ch && ch <= 'Z')
    {
        return ch+'a'-'A';
    }
    return '+';
}

int main()
{
    char ch;
    vector<int> vec;
    while(cin >> ch)
    {
        if(isValid(ch) != '+')
        {
            vec.push_back(isValid(ch));
        }
    }
    int j=vec.size()-1;
    for(int i=0;i<j;i++,j--)
    {
        if(vec[i]!=vec[j])
        {
            cout << 0 << endl;
            return 0;
        }
    }
    cout << 1 << endl;
    return 0;
}