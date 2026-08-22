//动态规划法，滚动数组思想

#include <vector>
using namespace std;

class Solution {
public:
    int tribonacci(int n) {
        if(n==0) return 0;
        if(n==1||n==2) return 1;
        vector<int> tri(n+1,0);
        tri[1]=1;
        tri[2]=1;
        int i=3;
        while(i<=n)
        {
            tri[i]=tri[i-1]+tri[i-2]+tri[i-3];
            i++;
        }
        return tri[n];
    }
};