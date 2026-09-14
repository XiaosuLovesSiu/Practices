#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Solution {
public:

    pair<float,float> solve(int a,int b,int c)
    {
        int delta=b*b-4*a*c;
        if(delta<0)
           return {-1,-1};
        else if(delta==0)
            return {-b/(2*a),-b/(2*a)};
        else
        {
            float x1=(-b-sqrt(delta))/(2*a);
            float x2=(-b+sqrt(delta))/(2*a);
            if(x1>x2)
            {
                float temp=x1;
                x1=x2;
                x2=temp;
            }
            return {x1,x2};
        }
    }
};

int main()
{
    int a=1,b=-3,c=2;
    auto result=Solution().solve(a,b,c);
    cout << fixed << setprecision(3) << result.first << " " << result.second << endl;
    a=2;
    b=-5;
    result=Solution().solve(a,b,c);
    cout << fixed << setprecision(3) << result.first << " " << result.second << endl;
    a=-3;
    b=10;
    result=Solution().solve(a,b,c);
    cout << fixed << setprecision(3) << result.first << " " << result.second << endl;
    return 0;
}