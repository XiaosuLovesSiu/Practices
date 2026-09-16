#include <string>
#include <stack>
using namespace std;

//自己手搓了3个函数，完成了本题。这三个函数都可迁移到其他字符串题目中。
// transferToNum函数：将字符串中[l,r]区间的数字转化为整数
// read函数：将字符串中[l,r]区间的方程式解析为ax+b的形式，返回一个pair<int,int>，其中first为a，second为b
// transferToString函数：将整数x转化为字符串形式的"x=..."，其中...为x的值

//特别地，可以用string中的to_string函数将整数转化为字符串，更为方便。我手搓了一个函数，主要是为了练习栈的使用。

class Solution {
public:
    int transferToNum(const string& s,int l,int r)
    {
        int diff='1'-1;
        int res=0;
        for(int i=l;i<=r;i++)
        {
            res=res*10+s[i]-diff;
        }
        return res;
    }

    pair<int,int> read(const string& s,int l,int r)
    {
        pair<int,int> ans(0,0);
        int signal=1;
        int i=l,nstart=l;
        if(s[l]=='-')
        {
            signal=-1;
            i++;
            nstart++;
        }
        while(i<=r)
        {
            while(i<=r && s[i]!='+' && s[i]!='-') i++;
            if(s[i-1]=='x')
            {
                if(nstart==i-1) ans.first+=(signal*1);
                else ans.first+=signal*transferToNum(s,nstart,i-2);
            }
            else ans.second+=signal*transferToNum(s,nstart,i-1);

            if(i==r+1) return ans;
            else if(s[i]=='+') signal=1;
            else signal=-1;

            i++;
            nstart=i;
        }
        return ans;
    }

    string transferToString(int x)
    {
        string res="x=";
        if(x<0)
        {
            res.push_back('-');
            x*=-1;
        }
        stack<int> stk;
        while(x!=0)
        {
            stk.push(x%10);
            x/=10;
        }
        while(stk.empty()==false)
        {
            res.push_back(static_cast<char>(stk.top()+'0'));
            stk.pop();
        }
        if(res.size()==2) res.push_back('0');
        return res;
        //return "x=" + to_string(x);
    }

    string solveEquation(string equation) {
        
        int div=0;
        while(equation[div]!='=') div++;

        pair<int,int> left=read(equation,0,div-1);
        pair<int,int> right=read(equation,div+1,equation.size()-1);
        int a=left.first,b=left.second,c=right.first,d=right.second;

        int x1=a-c,x0=b-d;
        if(x1==0)
        {
            if(x0!=0) return "No solution";
            else return "Infinite solutions";
        }
        int xValue=-(x0/x1);
        
        return transferToString(xValue);
    }
};