//倒序的动态规划做法。

#include <vector>
using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n=cost.size()-1;
        vector<int> costly(n+1,0);
        costly[n]=cost[n];
        costly[n-1]=cost[n-1];
        int q=n-2;
        while(q>=0)
        {
            costly[q]=cost[q]+((costly[q+1]>costly[q+2])? costly[q+2]: costly[q+1]);
            q--;
        }
        return (costly[0]>costly[1])? costly[1]: costly[0]; 
    }
};