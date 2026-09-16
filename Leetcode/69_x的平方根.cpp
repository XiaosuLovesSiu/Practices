//二分法寻找平方为x的整数
#include <iostream>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
		unsigned long long xl=x;
        unsigned long long left=0,right=1024*1024;
        unsigned long long mid;
        while(true)
        {
            mid=left+(right-left)/2;
            if(mid*mid==xl) return mid;
            else if(mid*mid>xl) right=mid;
            else left=mid;
            if(left==right-1) break;
        }
        return left;
    }
};

int main()
{
	Solution s;
	int x;
	cin>>x;
	cout<<s.Solution::mySqrt(x)<<endl;
	return 0;
}
