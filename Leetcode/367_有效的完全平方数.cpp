//二分查找平方为x的整数

class Solution {
public:
    bool isPerfectSquare(int x) {
        unsigned long long left=0,right=1024*1024;
        unsigned long long mid;
        while(true)
        {
            mid=left+(right-left)/2;
            if(mid*mid==x) return true;
            else if(mid*mid>x) right=mid;
            else left=mid;
            if(left==right-1) break;
        }
        return false;
    }
};