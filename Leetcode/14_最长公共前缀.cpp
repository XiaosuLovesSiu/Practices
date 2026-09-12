//从头开始检查每一位。

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n=strs.size(),ind=0;
        string res;
        for(int i=0;i<n;i++)
        {
            if(strs[i]=="") return res;
        }
        while(true)
        {
            for(int i=0;i<n;i++)
            {
                if(ind>=strs[i].size() || strs[i][ind]!=strs[0][ind]) return res;
            }
            res.push_back(strs[0][ind]);
            ind++;
        }
        return res;
    }
};