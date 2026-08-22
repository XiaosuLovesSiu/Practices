//拆分多位数每位上数字的标准做法。

class Solution {
public:
    bool checkDivisibility(int n) {
        int summy=0,multi=1,copy=n;
        while(n!=0)
        {
            int temp=n%10;
            n/=10;
            multi*=temp;
            summy+=temp;
        }
        summy+=multi;
        if(copy%summy==0) return true;
        return false;
    }
};