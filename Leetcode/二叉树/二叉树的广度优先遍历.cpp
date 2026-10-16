//二叉树的层序遍历。题目为Leetcode 102.

#include <queue>
#include <vector>
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

class Solution1
{
public:
    vector<vector<int>> levelOrder(TreeNode *root) //迭代法，使用队列。此处值得注意的点是，使用size控制for循环来实现逐层遍历。
    {
        vector<vector<int>> res;
        if (!root)
            return res;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            vector<int> vec;
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                vec.push_back(cur->val);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            res.push_back(vec);
        }
        return res;
    }
};

class Solution2
{
public:
    void generate(TreeNode *cur, vector<vector<int>> &res, int depth) //采用了迭代。
    {
        if (!cur)
            return;
        if (res.size() == depth)
            res.push_back({});
        res[depth].push_back(cur->val);
        generate(cur->left, res, depth + 1);
        generate(cur->right, res, depth + 1);
    }
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        generate(root, res, 0);
        return res;
    }
};