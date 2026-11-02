#include <vector>
#include <stack>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    string transferToString(int x)
    {
        string res;
        if (x == 0)
            return "0";
        if (x < 0)
        {
            res.push_back('-');
            x *= -1;
        }
        stack<int> stk;
        while (x != 0)
        {
            stk.push(x % 10);
            x /= 10;
        }
        while (stk.empty() == false)
        {
            res.push_back(static_cast<char>(stk.top() + '0'));
            stk.pop();
        }
        return res;
    }

    void func(TreeNode *cur, vector<string> &vec, string str)
    {
        if (cur->left == nullptr && cur->right == nullptr)
        {
            vec.push_back(str + transferToString(cur->val));
        }
        else
        {
            str += transferToString(cur->val);
            str += "->";
            if (cur->left)
                func(cur->left, vec, str);
            if (cur->right)
                func(cur->right, vec, str);
        }
    }
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> vec;
        if (!root)
            return vec;
        string str;
        func(root, vec, str);
        return vec;
    }
};