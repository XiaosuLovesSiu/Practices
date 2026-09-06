/*
方法一：试图dp。
一维：
dp[i]应该为s[i]（含）以前的字符串中最长回文子串长度。
dp[i+1]应该是dp[i]和含s[i+1]的最长回文子串的最大值。
但这个算法的时间复杂度会很高。
在最后的呈现中甚至用滚动pair优化掉了dp数组。
总结：时间复杂度O(n^3)，空间复杂度O(1)。空间复杂度未考虑答案数组。
*/
#include <string>
using namespace std;
int judge(int searcher,int explorer,string &s)
{
    for(int i=searcher,j=explorer;i<j;i++,j--)
    {
        if(s[i]!=s[j]) return 0;
    }
    return explorer-searcher+1;
}
class Solution1 {
public:
    string longestPalindrome(string s) {
        int n=s.size();
        pair<int,int> respair(1,0);
        for(int explorer=0;explorer<n;explorer++)
        {
            int res=1;
            int searcher=0;
            while(searcher<=explorer)
            {
                while(s[searcher]!=s[explorer]) searcher++;
                int temp=judge(searcher,explorer,s);
                if(temp==0)
                {
                    searcher++;
                }
                else
                {
                    res=(res>temp)? res:temp;
                    break;
                }
            } 
            if(respair.first<res) respair=pair<int,int>(res,explorer);
        }
        string restr;
        for(int i=respair.second;i>respair.second-respair.first;i--)
        {
            restr.push_back(s[i]);
        }
        return restr;
    }
};

/*
方法二：中心扩展法。此为看题解思路后自己完成的代码。
枚举所有可能成为回文串中心的点，向两边扩展，直到不满足回文串条件为止。
总结：时间复杂度O(n^2)，空间复杂度O(1)。空间复杂度未考虑答案数组。
*/
int read(int sind,int find,string &s)
{
    int p=sind,q=find;
    while(p>=0&&q<s.size()&&s[p]==s[q])
    {
        p--;
        q++;
    }
    return q-p-1;
}

class Solution2 {
public:
    string longestPalindrome(string s) {
        int n=s.size();
        int find=0,sind=0;
        pair<int,int> respair(1,0);
        //respair(回文串长度，sind与find之和)
        while(find<n)
        {
            int temp=read(sind,find,s);
            if(respair.first<temp) respair=pair<int,int>(temp,sind+find);
            if(sind==find) find++;
            else sind++;
        }
        
        string restr;
        int startpos=(respair.second+1)/2-respair.first/2;
        for(int i=startpos;i<startpos+respair.first;i++)
        {
            restr.push_back(s[i]);
        }
        return restr;
    }
};