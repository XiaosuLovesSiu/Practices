#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Solution {
public:

    pair<int, pair<float,float>> solve(int a,int b,int c)
    {
        if(a==0)
        {
            if(b==0)
            {
                if(c==0) return {3, {-1, -1}}; //无穷多解
                else return {0, {-1, -1}}; //无解
            }
            else return {1, {-static_cast<float>(c)/b, -static_cast<float>(c)/b}}; //一元一次方程
        }
        long long delta=b*b-4*a*c;
        if(delta<0)
           return {0, {-1, -1}};
        else if(delta==0)
            return {1, {-b/(2.0*a),-b/(2.0*a)}};
        else
        {
            float x1=(-b-sqrt(delta))/(2.0*a);
            float x2=(-b+sqrt(delta))/(2.0*a);
            if(x1>x2)
            {
                float temp=x1;
                x1=x2;
                x2=temp;
            }
            return {2, {x1, x2}};
        }
    }
};

int main()
{
    int a,b,c;
    cin >> a >> b >> c;
    auto result=Solution().solve(a,b,c);
    if(result.first==0) cout << "No real roots" << endl;
    else if(result.first==1) cout << fixed << setprecision(3) << result.second.first << endl;
    else cout << fixed << setprecision(3) << result.second.first << " " << result.second.second << endl;
    return 0;
}