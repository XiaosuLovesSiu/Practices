//使用了dp，相比暴力方法减少了时间复杂度。此dp方法较难想出。
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        vector<int> lines(n,0);
        vector<vector<int>> data(m,lines);
        int res=0;
        for(int i=0;i<m;i++)
        {
            if(matrix[i][0]!='0')
            {
                data[i][0]=1;
                res=1;
            }
        }
        for(int j=1;j<n;j++)
        {
            if(matrix[0][j]!='0')
            {
                data[0][j]=1;
                res=1;
            }
        }
        for(int i=1;i<m;i++)
        {
            for(int j=1;j<n;j++)
            {
                if(matrix[i][j]!='0')
                {
                    data[i][j]=1+min({data[i-1][j-1],data[i][j-1],data[i-1][j]});
                    if(data[i][j]>res) res=data[i][j];
                }
            }
        }
        return res*res;
    }
};