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
    bool cpr(TreeNode *A, TreeNode *B)
    {
        if (!A)
        {
            if (!B)
                return true;
            else
                return false;
        }
        else if (!B)
            return false;
        else if (A->val != B->val)
            return false;
        else
            return cpr(A->left, B->left) && cpr(A->right, B->right);
    }
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;
        invert(root->right);
        return cpr(root->left, root->right);
    }
};