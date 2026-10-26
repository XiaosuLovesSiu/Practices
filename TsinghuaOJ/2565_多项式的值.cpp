#include <bits/stdc++.h>

using namespace std;

double Eval_Polynomial(const double a[], int n, double x)
{
    double xmain=1, res=0;
    for(int i=0;i<=n;i++)
    {
        if(i!=0) xmain*=x;
        res+=(a[i]*xmain);
    }
    return res;
}

int main()
{
    double x;

    cin >> x;

    double a[6];

    int n;

    cin >> n;

    for (int i = 0; i < n + 1; i++)
        cin >> a[i];

    // 求多项式在 x 处的值

    double res = Eval_Polynomial(a, n, x);

    cout << fixed << setprecision(3) << res << endl;

    return 0;
}