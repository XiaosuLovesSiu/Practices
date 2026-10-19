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

class Solution
{
public:
    void invert(TreeNode *cur)
    {
        if (!cur)
            return;
        auto temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;
        invert(cur->left);
        invert(cur->right);
    }
    TreeNode *invertTree(TreeNode *root)
    {
        invert(root);
        return root;
    }
};