//很容易想到应用栈。

#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    void reverseString(string& s)
    {
        int left=0,right=s.size()-1;
        while(left<right)
        {
            char temp=s[left];
            s[left]=s[right];
            s[right]=temp;
            left++;
            right--;
        }
    }
    string removeDuplicates(string s) {
        stack<char> stk;
        string rev;
        for(char ch : s)
        {
            if(stk.empty() || ch!=stk.top()) stk.push(ch);
            else stk.pop();
        }
        while(stk.empty()==false)
        {
            char temp=stk.top();
            stk.pop();
            rev.push_back(temp);
        }
        reverseString(rev);
        return rev;
    }
};