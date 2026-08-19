# include <iostream>
using namespace std;
int hare(int month)
{
    if (month==1)
    {
        return 2;
    }
    else if (month==2)
    {
        return 3;
    }
    else
    {
        return hare(month-1)+hare(month-2);
    }

}
int main() 
{
    int input;
    cin >> input;
    cout << hare(input) << endl;
    return 0;
}