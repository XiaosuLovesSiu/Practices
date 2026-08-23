//依然自下而上dp 原地
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
int minFallingPathSum(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0) return -1;
    if (m == 1) return matrix[0][0];
    
    for (int i = m - 2; i >= 0; i--) 
    {
        matrix[i][0] += min(matrix[i+1][0], matrix[i+1][1]);
        for (int j = 1; j < m - 1; j++) 
        {
            matrix[i][j] += min({matrix[i+1][j-1], matrix[i+1][j], matrix[i+1][j+1]});
        }
        matrix[i][m-1] += min(matrix[i+1][m-2], matrix[i+1][m-1]);
    }
    int res=matrix[0][0];
    for(int scan=1;scan<m;scan++)
    {
        res=min(matrix[0][scan],res);
    }
    return res;
    }
};