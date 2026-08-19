#include <iostream>
using namespace std;
int main()
{
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= 9; ++j)
        {
            for (int k = 1; k <= 9; ++k)
            {
                int num1;
                num1=i*100+j*10+k;
                int num2;
                num2=2*num1;
                int num3;
                num3=3*num1;
                int i1=num2/100;
                int j1=(num2/10)%10;
                int k1=num2%10;
                int i2=num3/100;
                int j2=(num3/10)%10;
                int k2=num3%10;
                if(i!=j && i!=k && j!=k && i1!=j1 && i1!=k1 && j1!=k1 && i2!=j2 && i2!=k2 && j2!=k2 && i!=i1 && i!=j1 && i!=k1 && i!=i2 && i!=j2 && i!=k2 && j!=i1 && j!=j1 && j!=k1 && j!=i2 && j!=j2 && j!=k2 && k!=i1 && k!=j1 && k!=k1 && k!=i2 && k!=j2 && k!=k2 && i1!=i2 && i1!=j2 && i1!=k2 && j1!=i2 && j1!=j2 && j1!=k2 && k1!=i2 && k1!=j2 && k1!=k2 && num1<1000 && num2<1000 && num3<1000 && num1>99 && num2>99 && num3>99 && i1!=0 && j1!=0 && k1!=0 && i2!=0 && j2!=0 && k2!=0)
                {
                    cout<<num1<<" "<<num2<<" "<<num3<<endl;
                }
            }
        }
    }
return 0;
}