#include <iostream>
using namespace std;
int main()
{
    int length,num,count=0;
    cin >> length >> num;
    int starts[num],ends[num];
    for(int i=0;i<num;i++)
    {
        cin >> starts[i] >> ends[i];
    }
    for(int tree=0;tree<=length;tree++)
    {
        for(int j=0;j<num;j++)
        {
            if(starts[j]<=tree && tree<=ends[j])
            {
                count++;
                break;
            }
        }
    }
    cout << length + 1 - count;
    return 0;
}