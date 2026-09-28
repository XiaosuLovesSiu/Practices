//简单的计数问题。

#include <string>
using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        int res=0,process=0;
        for(char ch : s)
        {
            if(ch=='(')
            {
                process+=1;
                res=(res<process) ? process : res;
            }
            else if(ch==')') process-=1;
        }
        return res;
    }
};