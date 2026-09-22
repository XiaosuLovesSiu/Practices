#include <string>
#include <climits>
using namespace std;

//字符串中的数处理能力进一步强化

class Solution {
public:
    int myAtoi(string s) {
        int ind=0,n=s.size(),sgn=0;
        int diff='1'-1;
        int max=INT_MAX;
        unsigned long long res=0;
        while(s[ind]==' ') ind++;
        if(s[ind]=='-')
        {
            sgn=-1;
            ind++;
        }
        else
        {
            sgn=1;
            if(s[ind]=='+') ind++;
        }
        while(ind<n && '0'<=s[ind] && s[ind]<='9')
        {
            res=res*10+s[ind]-diff;
            if(res>max)
            {
                if(sgn<0) return INT_MIN;
                else return max;
            }
            ind++;
        }
        return static_cast<int>(sgn*res);
    }
};