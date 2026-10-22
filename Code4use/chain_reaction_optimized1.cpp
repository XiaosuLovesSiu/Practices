#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

struct MatrixHash
{
    size_t operator()(const vector<vector<int>> &mat) const
    {
        size_t seed = 0;
        for (auto &row : mat)
        {
            for (int v : row)
            {
                // 经典的 boost 组合哈希
                seed ^= hash<int>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

struct MatrixEqual
{
    bool operator()(const vector<vector<int>> &a, const vector<vector<int>> &b) const
    {
        return a == b;
    }
};

//这两个struct是AI写的

void check(vector<vector<int>> &matrix, int i, int j)
// 检查(i, j)位置的电池是否充满，若是则返回连锁反应之后被改变的棋盘
{
    if (matrix[i][j] != 5)
        return;
    else
    {
        queue<pair<int, int>> exploding;
        matrix[i][j] = -1;
        exploding.push({i, j});
        while (!exploding.empty())
        {
            auto [i, j] = exploding.front();
            exploding.pop();
            for (int i0 = i - 1; i0 >= 0; i0--)
            {
                int &val = matrix[i0][j];
                if (val >= 0 && val < 5)
                {
                    val++;
                    if (val == 5)
                    {
                        val = -1;
                        exploding.push({i0, j});
                    }
                    break;
                }
            }
            for (int i0 = i + 1; i0 < matrix.size(); i0++)
            {
                int &val = matrix[i0][j];
                if (val >= 0 && val < 5)
                {
                    val++;
                    if (val == 5)
                    {
                        val = -1;
                        exploding.push({i0, j});
                    }
                    break;
                }
            }
            for (int j0 = j - 1; j0 >= 0; j0--)
            {
                int &val = matrix[i][j0];
                if (val >= 0 && val < 5)
                {
                    val++;
                    if (val == 5)
                    {
                        val = -1;
                        exploding.push({i, j0});
                    }
                    break;
                }
            }
            for (int j0 = j + 1; j0 < matrix[0].size(); j0++)
            {
                int &val = matrix[i][j0];
                if (val >= 0 && val < 5)
                {
                    val++;
                    if (val == 5)
                    {
                        val = -1;
                        exploding.push({i, j0});
                    }
                    break;
                }
            }
        }
    }
}

void attemptToPoint(vector<vector<int>> &matrix, int x, int y)
{
    int &battery = matrix[x][y];
    if (battery == -1)
    {
        battery = 1;
    }
    else
    {
        battery++;
        if (battery == 5)
        {
            check(matrix, x, y);
        }
    }
}

bool allClear(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const auto &battery : row)
            if (battery != -1)
                return false;
    }
    return true;
}

bool searchForNStepsDone(const vector<vector<int>> &matrix, int steps, vector<pair<int, int>> &locations, unordered_map<vector<vector<int>>, int, MatrixHash, MatrixEqual> &istore)
{
    if (steps == 0)
    {
        return allClear(matrix);
    }
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            //if (matrix[i][j] == -1) continue;
            // 上面这一句代表不再搜索添补电池的解法
            vector<vector<int>> mcpy=matrix;
            attemptToPoint(mcpy, i, j);
            auto it = istore.find(mcpy);
            if(it!=istore.end())
            {
                if(it->second>=steps-1) continue;
            }
            if (searchForNStepsDone(mcpy, steps - 1, locations, istore))
            {
                locations.push_back({i, j});
                return true;
            }
            else if(steps>1) istore[mcpy]=steps-1;
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
    int r, c;
    cin >> r >> c;
    cout << "then input the matrix row by row: " << endl;
    vector<vector<int>> matrix(r, vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> matrix[i][j];
        }
    }
    vector<pair<int, int>> locations;

    unordered_map<vector<vector<int>>, int, MatrixHash, MatrixEqual> istore;

    for (int i = 1; i <= steps; i++)
    {
        cout << "considering " << i << "-steps-cost solution..." << endl;
        if (searchForNStepsDone(matrix, i, locations, istore))
            break;
    }
    if (locations.empty())
        cout << "cannot find an answer" << endl;
    else
        reverse(locations.begin(), locations.end());

    for (auto Pair : locations)
    {
        cout << '(' << Pair.first << ',' << Pair.second << ')' << ' ';
    }
    cout << endl;
    //cout << "notice: we didn't search for paths in need of extra batteries.";
    return 0;
}