#include <iostream>
using namespace std;
 
// 检查整数序列是否为递增数列
// 若为递增数列，返回0；否则返回第一个不递增的位置（从0开始计数）
int check_increasing(int a[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        if(a[i]>=a[i+1]) return i+1;
    }
    return 0;
}
 
int main()
{
    int n;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << check_increasing(a, n);
    return 0;
}