#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void check(vector<vector<int>> &matrix, bool &error, int i, int j)
{
    if (matrix[i][j] != 5)
        return;
    else
    {
        matrix[i][j] = -1;
        for (int i0 = i - 1; i0 >= 0; i0--)
        {
            int &val = matrix[i0][j];
            if (val == 5)
            {
                error = true;
            }
            else if (val >= 0 && val < 5)
            {
                val++;
                check(matrix, error, i0, j);
                break;
            }
        }
        for (int i0 = i + 1; i0 < matrix.size(); i0++)
        {
            int &val = matrix[i0][j];
            if (val == 5)
            {
                error = true;
            }
            else if (val >= 0 && val < 5)
            {
                val++;
                check(matrix, error, i0, j);
                break;
            }
        }
        for (int j0 = j - 1; j0 >= 0; j0--)
        {
            int &val = matrix[i][j0];
            if (val == 5)
            {
                error = true;
            }
            else if (val >= 0 && val < 5)
            {
                val++;
                check(matrix, error, i, j0);
                break;
            }
        }
        for (int j0 = j + 1; j0 < matrix[0].size(); j0++)
        {
            int &val = matrix[i][j0];
            if (val == 5)
            {
                error = true;
            }
            else if (val >= 0 && val < 5)
            {
                val++;
                check(matrix, error, i, j0);
                break;
            }
        }
    }
}

vector<vector<int>> attemptToPoint_full(vector<vector<int>> matrix, int x, int y, bool &error)
{
    int& battery = matrix[x][y];
    if(battery==-1)
    {
        battery=1;
        return matrix;
    }
    else
    {
        battery++;
        if(battery==5)
        {
            check(matrix, error, x, y);
        }
    }
    return matrix;
}

bool allClear(vector<vector<int>> matrix)
{
    for (auto row : matrix)
    {
        for (auto battery : row)
            if(battery!=-1) return false;
    }
    return true;
}

bool searchForNStepsDone(vector<vector<int>> matrix, int steps, bool& error, vector<pair<int,int>>& locations)
{
    if(steps==0)
    {
        return allClear(matrix);
    }
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if(matrix[i][j]==-1) continue;
            //上面这一句代表不再搜索添补牡丹的解法
            auto matrixed = attemptToPoint_full(matrix,i,j,error);
            if(searchForNStepsDone(matrixed, steps-1, error, locations))
            {
                locations.push_back({i, j});
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int steps;
    cout << "how many steps do we have?" << endl;
    cin >> steps;
    cout << "what's the size of the matrix? input rows and columns." << endl;
    int r,c;
    cin >> r >> c;
    cout << "then input the matrix row by row: " << endl;
    vector<vector<int>> matrix(r,vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> matrix[i][j];
        }
    }
    bool error = false;
    vector<pair<int, int>> locations;

    for (int i = 1; i <= steps; i++)
    {
        cout << "considering " << i << "-steps-cost solution..." << endl;
        if(searchForNStepsDone(matrix, i, error, locations)) break;
    }
    if(locations.empty()) cout << "cannot find an answer" << endl;
    else reverse(locations.begin(),locations.end());

    for(auto Pair : locations)
    {
        cout << '(' << Pair.first << ',' << Pair.second << ')' << ' ';
    }
    cout << "is it possible to have an error? : " << error << endl;
    return 0;
}

//这里的error有可能误报，但这个功能对我影响不大