//一个比较麻烦但确实是O(n)时间的解法

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int right = nums.size() - 1;
        vector<int> arr(right + 1, 0);
        int fi = 0;
        if(nums[right]<=0)
        {
            for(int i=0;i<=right;i++)
            {
                arr[i]=nums[right-i]*nums[right-i];
            }
            return arr;
        }
        if(nums[0]>=0)
        {
            for(int i=0;i<=right;i++)
            {
                arr[i]=nums[i]*nums[i];
            }
            return arr;
        }
        //处理边界情况。
        while (nums[fi] < 0) {
            fi++;
        }
        // fi指向第一个数组中非负数。
        int si = fi - 1;
        int ni = 0;
        while (0 <= si && fi <= right) {
            if (-nums[si] > nums[fi]) {
                arr[ni] = nums[fi] * nums[fi];
                fi++;
            } else {
                arr[ni] = nums[si] * nums[si];
                si--;
            }
            ni++;
        }
        //处理剩余的元素
        if(si<0)
        {
            while(fi<=right)
            {
                arr[ni]=nums[fi] * nums[fi];
                fi++;
                ni++;
            }
        }
        if(fi>right)
        {
            while(si>=0)
            {
                arr[ni] = nums[si] * nums[si];
                si--;
                ni++;
            }
        }
        return arr;
    }
};