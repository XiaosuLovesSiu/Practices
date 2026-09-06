//仍然使用数学法。
//考虑nums1中最小的数。它对应的nums2中的元素必须是其本身。
//因此若符合题意的nums2数组存在，则其所有元素都与nums1中最小的数奇偶性相同。
//如果它是奇数，那么nums1之后所有的偶数都可以通过减去最小元得到奇数，即可以构造全奇数的nums2数组，返回true。
//否则，若nums1中存在奇数，则最小奇数对应的nums2中的元素必定为奇数，无法构造全偶数的nums2数组，返回false。
//特别地，若nums1中所有元素均为偶数，则可以直接构造nums2=nums1，返回true。
//代码如下。

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        sort(nums1.begin(),nums1.end());
        if(nums1[0]%2==1) return true;
        for(int i=0;i<nums1.size();i++)
        {
            if(nums1[i]%2==1) return false;
        }
        return true;
    }
};