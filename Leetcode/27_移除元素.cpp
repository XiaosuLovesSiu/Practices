//一个暴力的解法。
    
#include <vector>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int right=nums.size()-1,k=nums.size();
        for(int i=0;i<=right;i++)
        {
            if(nums[i]==val)
            {
                for(int j=i;j<=right-1;j++)
                {
                    nums[j]=nums[j+1];
                }
                right--;
                i--;
                k--;
            }
        }
        return k;
    }
};