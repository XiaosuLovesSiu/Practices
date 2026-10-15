//包含144、94、145三道题，每题各有递归和迭代两种解法

#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){} 
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){} 
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
};

class Solution1_1
{
public:
    void preT(TreeNode *root, vector<int> &vec)
    {
        if (!root)
            return;
        vec.push_back(root->val);
        preT(root->left, vec);
        preT(root->right, vec);
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> vec;
        preT(root, vec);
        return vec;
    }
};

class Solution2_1
{
public:
    void inorderT(TreeNode *root, vector<int> &vec)
    {
        if (!root)
            return;
        inorderT(root->left, vec);
        vec.push_back(root->val);
        inorderT(root->right, vec);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> vec;
        inorderT(root, vec);
        return vec;
    }
};

class Solution3_1
{
public:
    void post(TreeNode *root, vector<int> &vec)
    {
        if (!root)
            return;
        post(root->left, vec);
        post(root->right, vec);
        vec.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> vec;
        post(root, vec);
        return vec;
    }
};

class Solution1_2
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> s;
        vector<int> res;
        if (!root)
            return res;
        s.push(root);
        while (!s.empty())
        {
            TreeNode *now = s.top();
            s.pop();
            res.push_back(now->val);
            if (now->right)
                s.push(now->right);
            if (now->left)
                s.push(now->left);
        }
        return res;
    }
};

class Solution2_2
{
public:
    vector<int> inorderTraversal_set(TreeNode *root) 
    // 这里开了个set来记录已经访问过的节点，避免重复访问，事实上可以用mouse指针完成这一工作
    {
        stack<TreeNode *> s;
        vector<int> res;
        if (!root)
            return res;
        TreeNode *mouse = root;

        while (mouse)
        {
            s.push(mouse);
            mouse = mouse->left;
        }
        set<TreeNode *> processed;
        while (!s.empty())
        {
            mouse = s.top();
            if (!mouse->left || processed.find(mouse->left) != processed.end())
            {
                processed.insert(mouse);
                res.push_back(mouse->val);
                s.pop();
                if (mouse->right)
                    s.push(mouse->right);
            }
            else
                s.push(mouse->left);
        }
        return res;
    }

    vector<int> inorderTraversal_ptr(TreeNode *root)  
    //这里是用指针的优化版本
    {
        stack<TreeNode *> s;
        vector<int> res;
        if (!root)
            return res;
        TreeNode *mouse = root;

        while (mouse || !s.empty())
        {
            if (mouse)
            {
                s.push(mouse);
                mouse = mouse->left;
            }
            else
            {
                mouse = s.top();
                s.pop();
                res.push_back(mouse->val);
                mouse = mouse->right;
            }
        }
        return res;
    }
};

class Solution3_2
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> s;
        vector<int> res;
        if (!root)
            return res;
        s.push(root);
        while (!s.empty())
        {
            TreeNode *now = s.top();
            s.pop();
            res.push_back(now->val);
            if (now->left)
                s.push(now->left);
            if (now->right)
                s.push(now->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

//此外，二叉树的遍历还可以用空节点标记法或者boolean标记法来实现
//下面以中序遍历的空节点标记法为例，其它遍历顺序类似

class Solution2_3
{
public:
    vector<int> inorderTraversal_nullptr(TreeNode *root) 
    //思想的精髓是用nullptr来标记当前节点的左右子树是否已经访问过，若访问过则可以将当前节点的值加入结果集，否则就应该先招募下家
    {
        stack<TreeNode *> s;
        vector<int> res;
        if (!root)
            return res;
        TreeNode *mouse = root;
        s.push(root);
        while (!s.empty())
        {
            mouse = s.top();
            if (mouse)
            {
                s.pop();
                if (mouse->right)
                    s.push(mouse->right);
                s.push(mouse);
                s.push(nullptr);
                if (mouse->left)
                    s.push(mouse->left);
            }//由于是中序（左中右）遍历，入栈顺序为右中左。其它顺序的遍历类似，只需要调整入栈顺序即可
            else
            {
                s.pop();
                res.push_back(s.top()->val);
                s.pop();
            }
        }
        return res;
    }
};

//下面以后序遍历的boolean标记法为例，其它遍历顺序类似

class Solution3_4
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    //用一个布尔值来标记当前节点的左右子树是否已经访问过，若访问过则可以将当前节点的值加入结果集，否则就应该先招募下家
    {
        stack<pair<TreeNode *, bool>> s;
        vector<int> res;
        if (!root)
            return res;
        TreeNode *mouse = root;
        s.push({root, false});
        while (!s.empty())
        {
            auto thePair = s.top();
            mouse = thePair.first;
            if (!thePair.second)
            {
                s.pop();
                s.push({mouse, true});
                if (mouse->right)
                    s.push({mouse->right, false});
                if (mouse->left)
                    s.push({mouse->left, false});
            }//由于是后序（左右中）遍历，入栈顺序为中右左。其它顺序的遍历类似，只需要调整入栈顺序即可
            else
            {
                res.push_back(mouse->val);
                s.pop();
            }
        }
        return res;
    }
};