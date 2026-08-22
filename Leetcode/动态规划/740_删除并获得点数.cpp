#include <map>
#include <vector>
using namespace std;

int maxi(int a,int b)
{
    if(a>b) return a;
    return b;
}

//方法一：一个能过本题但过于复杂的方法。试图转化为“打家劫舍”。

class Solution1 {
public:
    int deleteAndEarn(vector<int>& nums) {
        map<int,int> mappy;
        for(int i=0;i<nums.size();i++)
        {
            mappy[nums[i]]++;
        }
        int n=mappy.size();
        if(n==1) return (mappy.begin()->first)*(mappy.begin()->second);
        if(n==2)
        {
            auto q=mappy.begin();
            int a=(q->first)*(q->second);
            int memo=q->first;
            q++;
            int b=(q->first)*(q->second);
            if(q->first==memo+1) return (a>b)? a:b;
            else return a+b;
        }
        auto it=mappy.begin();
        auto xinyi=it;
        it++;
        xinyi->second=xinyi->first*xinyi->second;
        auto wenli=it;
        if(wenli->first==xinyi->first+1) wenli->second=wenli->first*wenli->second;
        else 
        {
            wenli->second=wenli->first*wenli->second+xinyi->second;
        }
        it++;
        int t;
        if(it->first==wenli->first+1)
        {
            t=xinyi->second;
        }
        else t=maxi(xinyi->second,wenli->second);
        it->second=it->first*it->second + t;
        auto chibao=it;
        it++;
        for(;it!=mappy.end();it++)
        {
            if(it->first==chibao->first+1)
            {
                it->second=it->first*it->second + maxi(wenli->second,xinyi->second);
            }
            else
            {
                it->second=it->first*it->second + maxi(wenli->second,chibao->second);
            }
            xinyi++;
            wenli++;
            chibao++;
        }
        return maxi(chibao->second,wenli->second);
    }
};

//方法二：转化为“打家劫舍”的标准方法。使用动态规划。

class Solution2 {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n=nums.size();
        vector<int> sum(10001,0);
        for(int i=0;i<n;i++)
        {
            sum.at(nums[i])+=nums[i];
        }
        sum[3]+=sum[1];
        for(int j=4;j<=10000;j++)
        {
            sum[j]+=maxi(sum[j-3],sum[j-2]);
        }
        return maxi(sum[10000],sum[9999]);
    }
};