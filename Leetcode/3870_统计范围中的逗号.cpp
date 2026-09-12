//由于本题中n的范围是1到100,000，本题出现的所有数最多只会用到1个逗号。
class Solution {
public:
    int countCommas(int n) {
        if(n<1000) return 0;
        return n-999;
    }
};