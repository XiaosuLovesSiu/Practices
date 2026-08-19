#include <iostream>
using namespace std;
int main() 
{
    bool a = true;
    int h=0,day=0;
    do{
        h = h+2;
        day++;
        if(h>=10)
        {
            goto label;
        }
        else
        {
            h = h-1;
        }
    } while(a);
    label:
    cout << "cost of days: " << day << endl;
    return 0;
}