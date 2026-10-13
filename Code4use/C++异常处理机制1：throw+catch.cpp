//try、throw、catch配合进行的异常处理机制
#include <iostream>
#include <string>
using namespace std;

double divide(int a,int b)
{
    if(b==0)
    {
        throw "you can't divide by zero!";
    }
    return (double)a/b;
}

int main()
{
    try
    {
        cout << divide(10,2) << endl;
        cout << divide(10,0) << endl;
        cout << divide(10,5) << endl;//不会执行，因为上面一行抛出了异常，直接跳转到catch语句块
    }
    catch(const char* msg)
    {
        cout << "error: " << msg << endl;
    }
    return 0;
}