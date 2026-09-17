//再遇滑动窗口。
//使用了哈希表方法，unordered_map，记录每个水果的数量。

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& vec) {
        int si=0,ei=0,res=1;
        unordered_map<int,int> fruitMap;
        fruitMap[vec[0]]=0;
        for(;ei<vec.size();ei++)
        {
            fruitMap[vec[ei]]++;
            while(fruitMap.size()>2)
            {
                fruitMap[vec[si]]--;
                if(fruitMap[vec[si]]==0) fruitMap.erase(vec[si]);
                si++;
            }
            res=(res>=ei-si+1)? res : ei-si+1;
        }
    return res;
    }
};