#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n,a,b,temp;
    cin >> n;
    vector<int> plus,res;
    plus.push_back(0);
    for(int i=0;i<n;i++)
    {
        cin >> temp;
        plus.push_back(temp+plus[i]);
    }
    while(cin>>a>>b)
    {
        res.push_back(plus[b+1]-plus[a]);
    }
    for(int i=0;i<res.size();i++)
    {
        cout<<res[i]<<endl;
    }
    return 0;
}