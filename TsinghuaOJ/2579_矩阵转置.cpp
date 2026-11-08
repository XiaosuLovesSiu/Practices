#include <iostream>
using namespace std;

/// 实现transposeMatrix函数
int** transposeMatrix(int** ori, int M, int N)
{
    int** tr = new int*[N];
    for (int i = 0; i < N; i++)
    {
        tr[i] = new int[M];
    }
    for(int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tr[j][i] = ori[i][j];
        }
    }
    return tr;
}

int main()
{
    int M, N;
    cin >> M >> N;

    /// 声明指针original、transposed
    int** original = new int*[M];
    int** transposed = nullptr;
    /// 动态分配原始矩阵original
    for (int i = 0; i < M; i++)
    {
        original[i] = new int[N];
    }
    // 输入原始矩阵
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> original[i][j];
        }
    }

    /// transposeMatrix 对传入矩阵做转置操作并返回结果
    transposed = transposeMatrix(original, M, N);

    // 输出转置矩阵
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }

    // 释放动态分配的原始矩阵
    for (int i = 0; i < M; i++)
    {
        delete[] original[i];
    }
    delete[] original;

    // 释放动态分配的转置矩阵
    for (int i = 0; i < N; i++)
    {
        delete[] transposed[i];
    }
    delete[] transposed;

    return 0;
}

