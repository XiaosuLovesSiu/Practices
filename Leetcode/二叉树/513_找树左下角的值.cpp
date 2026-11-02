//使用空指针标记法。
#include <queue>
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
    int findBottomLeftValue(TreeNode *root)
    {
        int lft = root->val;
        queue<TreeNode *> q;
        q.push(nullptr);
        q.push(root);
        while (true)
        {
            auto fr = q.front();
            q.pop();
            if (!fr)
            {
                if (q.empty())
                    break;
                q.push(nullptr);
                fr = q.front();
                lft = fr->val;
            }
            if (fr->left)
                q.push(fr->left);
            if (fr->right)
                q.push(fr->right);
        }
        return lft;
    }
};