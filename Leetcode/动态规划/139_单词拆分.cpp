/*
整理思路。
用dp[i]表示截至第i个字符（含）的字符串是否可字典表示。
dp[0]应是true。
dp[i]==true的充要条件是存在j<i使得dp[j]==true且j+1到i（闭区间）的字符串和字典中的某个元素相等
用哈希表记录之前已经是true的i。
*/
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //在s前面插入占位符，使索引和数组保持一致，减少思考量
        string copy="#";
        for(char signal : s)
        {
            copy.push_back(signal);
        }

        //将字典转化为set方便后续查找
        unordered_set<string> wordset;
        for(string word : wordDict)
        {
            wordset.insert(word);
        }

        vector<bool> dp(copy.size(),false);
        dp[0]=true;
        //建立过去是true的索引的哈希表
        unordered_set<int> indset;
        indset.insert(0);
        for(int i=1;i<copy.size();i++)
        {
            for(int index : indset)
            {
                string mid="";
                for(int k=index+1;k<=i;k++)
                {
                    mid.push_back(copy[k]);
                }
                if(wordset.find(mid)!=wordset.end())
                {
                    dp[i]=true;
                    indset.insert(i);
                    break;
                }
            }
        }
        return dp[copy.size()-1];
    }
};