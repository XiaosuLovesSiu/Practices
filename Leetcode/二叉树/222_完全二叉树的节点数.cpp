#include <vector>
#include <cmath>
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
    int check(TreeNode *cur)
    {
        if (!cur)
            return 0;
        TreeNode *ptr = cur;
        TreeNode *ptr2 = cur;
        int l = 0, r = 0;
        while (ptr)
        {
            ptr = ptr->left;
            l++;
        }
        while (ptr2)
        {
            ptr2 = ptr2->right;
            r++;
        }
        if (l == r)
            return (int)pow(2, l) - 1;
        else
            return 1 + check(cur->left) + check(cur->right);
    }
    int countNodes(TreeNode *root)
    {
        if (!root)
            return 0;
        return check(root);
    }
};