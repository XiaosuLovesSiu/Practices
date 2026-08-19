#include <iostream>
using namespace std;
int main() 
{
    //int a = 10;
    //const int c = 20;
    //int c = a + b;
    //cout << '^'+32 << endl;
    int num ;
    cin >> num;
    switch(num)
    {
        case 1:
            cout << "Hello World" << endl;
            
        case 2:
            cout << "Hello C++" << endl;
            
        default:
            cout << "Invalid input" << endl;
    }
    cout << num+10 << endl;
    return 0;
}