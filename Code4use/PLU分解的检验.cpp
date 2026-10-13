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
    vector<vector<double>> P = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };

    vector<vector<double>> A = {
        {0, 0, 1, 2},
        {0, 0, 3, 0},
        {1, -1, 0, 1},
        {2, 0, -1, 3}
    };

    vector<vector<double>> L = {
        {1, 0, 0, 0},
        {0.5, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 3, 1}
    };

    vector<vector<double>> U = {
        {2, 0, -1, 3},
        {0, -1, 0.5, -0.5},
        {0, 0, 1, 2},
        {0, 0, 0, -6}
    };

    if(matmul_ikj(P, A) == matmul_ikj(L, U)) {
        cout << "P*A = L*U" << endl;
    } else {
        cout << "P*A != L*U" << endl;
    }

    return 0;
}