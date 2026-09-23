//动态规划的用处。

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

//此外，改用滚动pair可以节约空间。下面是一个结果对1000000007取模的解法。

class Solution2 {
private:
    const int mod=1000000007;
public:
    int fib(int n) {
        if(n<2) return n;
        else if(n<5) return n-1;
        pair<int,int> fibo={0,1};
        for(int i=1;i<n;i++)
        {
            int temp=(fibo.first+fibo.second)%mod;
            fibo.first=fibo.second;
            fibo.second=temp;
        }
        return fibo.second;
    }
};