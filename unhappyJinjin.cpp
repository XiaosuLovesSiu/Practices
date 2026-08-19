#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    int a1,a2,s1,s2,d1,d2,f1,f2,g1,g2,h1,h2,j1,j2;
    cin >>a1>>a2>>s1>>s2>>d1>>d2>>f1>>f2>>g1>>g2>>h1>>h2>>j1>>j2;
    int a=a1+a2,s=s1+s2,d=d1+d2,f=f1+f2,g=g1+g2,h=h1+h2,j=j1+j2;
    int B=max({a,s,d,f,g,h,j});
    if(B<=8) cout<<0<<endl;
    else
    {
        if(a==B) cout<<1<<endl;
        else if(s==B) cout<<2<<endl;
        else if(d==B) cout<<3<<endl;
        else if(f==B) cout<<4<<endl;
        else if(g==B) cout<<5<<endl;
        else if(h==B) cout<<6<<endl;
        else cout<<7<<endl;
    }
    return 0;
}