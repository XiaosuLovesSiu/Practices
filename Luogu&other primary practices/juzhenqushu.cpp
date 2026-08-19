#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
void reposition(int row,int M,int *p);
int main()
{
    int N,M;
    cin >> N >> M;
    int a[N][M];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            cin >> a[i][j];
        }
    }
    int *p=&a[0][0];
    for(int i=0;i<N;i++)
    {
        reposition(i,M,p);
    }
    long long sum = 0;
    for(int j=0;j<M;j++)
    {
        for(int i=0;i<N;i++)
        {
            sum += a[i][j]*pow(2,j+1);
        }
    }
    cout << sum << endl;
    return 0;
}
void reposition(int row,int M,int *p)
{
    int array[M];
    for(int t=0;t<M;t++)
    {
        array[t] = *(p+row*M+t);
    }
    sort(array, array+M);
    for(int t=0;t<M;t++)
    {
        *(p+row*M+t) = array[t];
    }
}