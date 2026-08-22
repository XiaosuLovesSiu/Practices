//初识滚动数组与动态规划。

#include <vector>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if(n==1) return 1;
        vector<int> memo(n+1,0);
        memo[1]=1;
        memo[2]=2;
        int i=3;
        while(i<=n)
        {
            memo[i]=memo[i-1]+memo[i-2];
            i++;
        }
        return memo[i-1];
    }
};