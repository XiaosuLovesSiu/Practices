#include <iostream>
#include <iomanip>
using namespace std;
void print_calenda(int days, int first_day, int week_start)
{
    if (days < 28 || days > 31 || first_day < 1 || first_day > 7 || week_start < 1 || week_start > 7)
    {
        cout << "ERROR";
        return;
    }

    int prepare = (first_day + 7 - week_start) % 7;

    for (int i = 0; i < prepare; i++)
    {
        cout << "   ";
    }

    for (int i = 1; i <= days; i++)
    {
        if (i < 10)
        {
            cout << "0" << i << " ";
        }
        else
        {
            cout << i << " ";
        }
        prepare++;
        if (prepare == 7)
        {
            cout << endl;
            prepare = 0;
        }
    }
}

int main()
{
    int days, first_day, week_start;
    cin >> days >> first_day >> week_start;

    print_calenda(days, first_day, week_start);

    return 0;
}