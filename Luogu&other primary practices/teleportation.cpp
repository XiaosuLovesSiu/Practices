#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int main()
{
    int a,b,x,y;
    cin >> a >> b >> x >> y ;
    int p1=abs(b-a),p2=abs(a-x)+abs(b-y),p3=abs(a-y)+abs(b-x);
    cout << min({p1,p2,p3});
    return 0;
}