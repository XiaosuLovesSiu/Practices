#include <iostream>
#include <vector>
using namespace std;

vector<vector<double>> matmul_ikj(
    const vector<vector<double>> &A,
    const vector<vector<double>> &B)
{

    int m = A.size(), k = A[0].size(), n = B[0].size();
    vector<vector<double>> C(m, vector<double>(n, 0.0));

    for (int i = 0; i < m; i++)
    {
        for (int l = 0; l < k; l++)
        { // l 在外
            for (int j = 0; j < n; j++)
            { // j 在内
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
    return C;
}

int main()
{
    int m,k,n;
    cout << "please input the size of matrix A (m x k): "<<endl;
    cin >> m >> k;
    cout << "then input the number n (stands for size of matrix B (k x n) ): "<<endl;
    cin >> n;
    cout << "please input the elements of matrix A (row by row): "<<endl;
    vector<vector<double>> A(m, vector<double>(k));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            cin >> A[i][j];
        }
    }
    cout << "please input the elements of matrix B (row by row): "<<endl;
    vector<vector<double>> B(k, vector<double>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }
    vector<vector<double>> C = matmul_ikj(A, B);
    cout << "The result of A * B is: "<<endl;
    for (const auto& row : C) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}