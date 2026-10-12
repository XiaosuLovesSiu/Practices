#include <iostream>
using namespace std;

void printday(int day)
{
    if(0<day&&day<10)
    {
        cout << " " << day << " ";
    }
    else
    {
        cout << day << " ";
    }
}

int main()
{
    int year,run;
    cin >> year;
    run=0;
    if(year%4==0)
    {
        run=1;
    }
    int dayofmonth[13]={0,31,28+run,31,30,31,30,31,31,30,31,30,31};
    int dayofyear=365+run;
    int weekofstart=((year-2023)*365+(year-2021)/4+6)%7+1;
    cout << "01 ";
    int ind=1;
    for(;ind<weekofstart;ind++)
    {
        cout << "   ";
    }
    for(int t=1;t<=12;t++)
    {
        for(int i=1;i<=dayofmonth[t];i++)
        {
            int day=0;
            if(ind!=8)
            {
                printday(i);
            }
            else
            {
                cout << endl;
                if(i+6>dayofmonth[t] && t!=12)
                {
                    if(t==9 || t==10 || t==11) cout << t+1 << " ";
                    else cout << "0" << t+1 << " ";
                }
                else cout << "   ";
                printday(i);
                ind=1;
            }
            ind++;
            
        }
    }
    return 0;
}