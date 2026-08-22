//双指针基础运用：左右两个往中间靠拢

#include <vector>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left=0,right=s.size()-1;
        while(left<right)
        {
            char temp=s[left];
            s[left]=s[right];
            s[right]=temp;
            left++;
            right--;
        }
    }
};