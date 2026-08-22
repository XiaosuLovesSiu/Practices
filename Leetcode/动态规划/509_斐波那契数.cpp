//滚动数组的用处。

#include <vector>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if(n==0) return 0;
        if(n==1) return 1;
        vector<int> fibbo(n+1,0);
        fibbo[1]=1;
        int i=2;
        while(i<=n)
        {
            fibbo[i]=fibbo[i-1]+fibbo[i-2];
            i++;
        }
        return fibbo[n];
    }
};