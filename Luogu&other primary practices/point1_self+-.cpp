#include <iostream>
using namespace std;
int main()
{
    double a = 100;
    double *p = &a;
    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << p << endl;
    cout << "Value at address p: " << *p << endl;
    p++;
    cout << "Address after incrementing p: " << p << endl;
    return 0;
}