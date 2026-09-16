#include <string>
#include <stack>
#include <map>
using namespace std;

//方法一：通过递归方法，不断消除左右直接完全闭合的括号。
//代码可读性较差，如果使用pair<char,char>来存储括号的对应关系，代码可读性会更好。
class Solution1 {
public:
    bool isValid(string s) {
        bool clear=true,progress=false;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]!='#')
        {
            clear=false;
            if(s[i]=='(')
            {
                int j=i+1;
                label1:
                if(s[j]==')')
                {
                    s[i]='#';
                    s[j]='#';
                    i=j;
                    progress=true;
                }
                else if(s[j]=='#')
                {
                    j++;
                    goto label1;
                }
            }
            else if(s[i]=='{')
            {
                int j=i+1;
                label2:
                if(s[j]=='}')
                {
                    s[i]='#';
                    s[j]='#';
                    i=j;
                    progress=true;
                }
                else if(s[j]=='#')
                {
                    j++;
                    goto label2;
                }
            }
            else if(s[i]=='[')
            {
                int j=i+1;
                label3:
                if(s[j]==']')
                {
                    s[i]='#';
                    s[j]='#';
                    i=j;
                    progress=true;
                }
                else if(s[j]=='#')
                {
                    j++;
                    goto label3;
                }
            }
        }
    }
    if(clear==true) return true;
    if(progress==false) return false;
    return isValid(s);
    }
};

//方法二：使用栈来存储左括号，遇到右括号时判断栈顶元素是否与之匹配，如果匹配则弹出栈顶元素，否则返回false。最后判断栈是否为空即可。

class Solution2
{
public:
    bool isValid(string s)
    {
        map<char,char> mp;
        mp.insert({'(',')'});
        mp.insert({'[',']'});
        mp.insert({'{','}'});
        
        stack<char> stk;
        for(char single : s)
        {
            if(mp.find(single)!=mp.end())
            {
                stk.push(single);
            }
            else
            {
                if(stk.empty())
                {
                    return false;
                }
                else if(single==mp[stk.top()])
                {
                    stk.pop();
                }
                else return false;
            }
        }
        if(stk.empty()) return true;
        return false;
    }
};