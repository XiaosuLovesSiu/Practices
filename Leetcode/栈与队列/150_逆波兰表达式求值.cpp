//刚好在离散数学课程上学习了逆波兰表达式，用栈实现了其运算。

#include <string>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int transferToNum(const string& s)
    {
        int sgn=1,i=0;
        int diff='1'-1;
        int res=0;
        if(s[i]=='-')
        {
            sgn=-1;
            i++;
        }
        else if(s[i]=='+') i++;
        for(;i<s.size();i++)
        {
            res=res*10+s[i]-diff;
        }
        return sgn*res;
    }
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(string str : tokens)
        {
            if(str=="+")
            {
                int temp=stk.top();
                stk.pop();
                temp+=stk.top();
                stk.pop();
                stk.push(temp);
            }
            else if(str=="-")
            {
                int temp=-stk.top();
                stk.pop();
                temp+=stk.top();
                stk.pop();
                stk.push(temp);
            }
            else if(str=="*")
            {
                int temp=stk.top();
                stk.pop();
                temp*=stk.top();
                stk.pop();
                stk.push(temp);
            }
            else if(str=="/")
            {
                int temp=stk.top();
                stk.pop();
                temp=stk.top()/temp;
                stk.pop();
                stk.push(temp);
            }
            else
            {
                stk.push(transferToNum(str));
            }
        }
        return stk.top();
    }
};