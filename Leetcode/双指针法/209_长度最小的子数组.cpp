//初见滑动窗口

#include <algorithm>
    
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size(),left=0,right=0;
        int res=1e6;
        int sumInWindow=nums[0];
        while(right<n)
        {
            if(sumInWindow>=target)
            {
                res=min(res,right-left+1);
                sumInWindow-=nums[left];
                left++;
            }
            else
            {
                right++;
                if(right>=n) break;
                sumInWindow+=nums[right];
            }
        }
        return (res==1e6)?0:res;
    }
};