//方法一：基于模拟的一种暴力算法。

#include <string>
using namespace std;

class Solution1 {
public:
    string rotate(string s)
    {
        int temp=s[0];
        for(int i=1;i<s.size();i++) s[i-1]=s[i];
        s[s.size()-1]=temp;
        return s;
    }
    bool rotateString(string s, string goal) {
        for(int i=0;i<s.size();i++)
        {
            if(s==goal) return true;
            s=rotate(s);
        }
        return false;
    }
};

//方法二：显然若true则s和goal长度必一致，在此前提下，在s+s中查找goal,若找到则true。
//此外，find需要用到KMP算法，我尚未掌握。
class Solution2 {
public:
    bool rotateString(string s, string goal) {
        return (s.size() == goal.size() && (s + s).find(goal) != string::npos);
    }
};
