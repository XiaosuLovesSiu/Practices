//使用空指针标记法
#include <stack>
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
    int sumOfLeftLeaves(TreeNode *root)
    {
        int sum = 0;
        stack<TreeNode *> stk;
        stk.push(root);
        while (!stk.empty())
        {
            auto tp = stk.top();
            stk.pop();
            if (tp)
            {
                if (tp->left)
                {
                    stk.push(tp->left);
                    stk.push(nullptr);
                }
                if (tp->right)
                    stk.push(tp->right);
            }
            else
            {
                tp = stk.top();
                stk.pop();
                if (tp->left == nullptr && tp->right == nullptr)
                {
                    sum += tp->val;
                }
                else
                {
                    if (tp->left)
                    {
                        stk.push(tp->left);
                        stk.push(nullptr);
                    }
                    if (tp->right)
                        stk.push(tp->right);
                }
            }
        }
        return sum;
    }
};