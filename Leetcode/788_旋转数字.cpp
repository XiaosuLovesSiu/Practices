//暴力法求解。事实上可以略微进行剪枝。

#include <vector>
using namespace std;

class Solution {
public:
    int rotatedDigits(int n) {
        int res=0;
        for(int i=1;i<=n;i++)
        {
            int i0=i;
            vector<int> dig;
            while(i0!=0)
            {
                dig.push_back(i0%10);
                i0/=10;
            }
            //现在数组dig中倒序盛装了n的各数位。
            //我们知道，n是好数，等价于n的各数位中至少含有2、5、6、9中的一个，并且不含3、4、7。
            bool contain=false,avoid=true;
            for(int d : dig)
            {
                if(d==3 || d==4 || d==7)
                {
                    avoid=false;
                    break;
                }
                else if(d==2 || d==5 || d==6 || d==9) contain=true;
            }
            res+=static_cast<int>(contain && avoid);
        }
        return res;
    }
};