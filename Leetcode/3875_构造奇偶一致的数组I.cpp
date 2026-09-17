//数学法。
//若nums1所有元素均为偶数，则可以直接构造nums2=nums1。
//否则，一定能找到nums1中一个奇数，对于nums1中每个元素，若为奇数则直接赋值，否则减去那个奇数再赋值。
//所以可以构造出一个奇数数组nums2。
//由上可知，无论nums1如何，结果一定是true。

#include <vector>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};