#include <iostream>
#include <cstring>
using namespace std;

#include <queue>
char *format_line(char *ipt)
{
    char *res = new char[1000];
    queue<char> q;
    int len = strlen(ipt);
    int ind=0;
    for (int i = 0; i < len; i++)
    {
        if (ipt[i] == ' ')
        {
            if (q.empty())
                continue;
            while(!q.empty())
            {
                res[ind] = q.front();
                q.pop();
                ind++;
            }
            res[ind]=' ';
            ind++;
        }
        else if (q.empty())
        {
            if ('a' <= ipt[i] && ipt[i] <= 'z')
                q.push(ipt[i] - 'a' + 'A');
            else
                q.push(ipt[i]);
        }
        else
        {
            if ('A' <= ipt[i] && ipt[i] <= 'Z')
                q.push(ipt[i] - 'A' + 'a');
            else
                q.push(ipt[i]);
        }
    }
    if(q.empty())
    {
        ind--;
        res[ind] = '\0';
    }
    else
    {
        while(!q.empty())
        {
            res[ind] = q.front();
            q.pop();
            ind++;
        }
        res[ind] = '\0';
    }
    return res;
}
int main()
{
    char input_line[100];
    cin.getline(input_line, 100);

    char *result_str = format_line(input_line);
    cout << result_str << endl;

    delete[] result_str;
    return 0;
}