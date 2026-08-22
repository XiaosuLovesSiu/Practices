//在动态规划的基础上，通过滚动数组实现了原地算法，空间复杂度降至O(1)。
 
#include <vector>
using namespace std;
 
class Solution {
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n==1) return nums[0];
        if(n==2) return (nums[0]>nums[1])? nums[0]: nums[1];
        nums[n-3]+=nums[n-1];
        int i=n-4;
        while(i>=0)
        {
            nums[i]+= (nums[i+2]>nums[i+3])? nums[i+2]: nums[i+3];
            i--;
        }
        return (nums[0]>nums[1])? nums[0]: nums[1];
    }
};