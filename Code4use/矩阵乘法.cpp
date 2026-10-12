#include <iostream>
#include <vector>
using namespace std;

vector<vector<double>> matmul_ikj(
    const vector<vector<double>>& A,
    const vector<vector<double>>& B) 
{
    if (A.empty() || B.empty() || A[0].size() != B.size()) {
        return vector<vector<double>>();  // Return an empty matrix if dimensions are incompatible
    }

    int m = A.size(), mid = A[0].size(), n = B[0].size();
    vector<vector<double>> C(m, vector<double>(n, 0.0));
    
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < mid; k++) {        // k 在外
            for (int j = 0; j < n; j++) {    // j 在内
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
//this is a C++ function that performs matrix multiplication using the IKJ loop order.

int main() {
    // Example usage of the matmul_ikj function
    vector<vector<double>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };

    vector<vector<double>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    vector<vector<double>> C = matmul_ikj(A, B);

    // Output the result
    for (const auto& row : C) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}