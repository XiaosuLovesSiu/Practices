#include <iostream>
#include <stack>
#include <string>
#include <set>
using namespace std;

struct Node
{
    char value;
    Node* left;
    Node* right;

    Node(const char val) : value(val), left(nullptr), right(nullptr) {}
};

void notice()
{
    cout << "Input fully parenthesized infix expression." << endl;
    cout << "Operators: 1(\\land) 2(\\lor) 3(\\lnot) 4(\\rightarrow) 5(\\leftrightarrow)" << endl;
    cout << "Example: ((p1q)4(3r)) for (p\\land q)\\rightarrow\\lnot r" << endl;
    cout << "Variables must be single letters. No spaces." << endl;
}

Node *infixToTree(const string &infix)
{
    stack<Node *> s;

    for (char token : infix)
    {
        if (token != ')')
        {
            s.push(new Node(token));
        }
        else
        {
            Node *right = s.top();
            s.pop();
            Node *op = s.top();
            s.pop();
            if (!(op->value == '1' || op->value == '2' || op->value == '3' || op->value == '4' || op->value == '5'))
            {
                throw string("Invalid operator: ") + op->value;
            }
            if (op->value == '1' || op->value == '2' || op->value == '4' || op->value == '5')
            {
                Node *left = s.top();
                s.pop();
                op->left = left;
            }
            op->right = right;
            if (s.empty() || s.top()->value != '(')
            {
                throw string("Invalid expression: missing left parenthesis for operator ") + op->value;
            }
            s.pop(); // Pop the left parenthesis
            s.push(op);
        }
    }
    Node *root = s.top();
    s.pop();
    if (!s.empty())
    {
        throw string("Invalid expression: extra tokens in stack");
    }
    return root;
}

bool judge(set<Node*> lft, set<Node*> rht)
{
    set<char> rSet;
    for (auto it = rht.begin(); it != rht.end(); ++it)
    {
        rSet.insert((*it)->value);
    }
    for (auto it = lft.begin(); it != lft.end(); ++it)
    {
        if (rSet.find((*it)->value) != rSet.end())
        {
            return true; // Found a common node in both sets
        }
    }
    return false; // No common nodes found
}

bool WangHaoAlgorithm(set<Node*> lft, set<Node*> rht)
{
    for (auto it = lft.begin(); it != lft.end(); ++it)
    {
        auto node = *it;
        if (node->value == '1')
        {
            lft.erase(it);
            lft.insert(node->left);
            lft.insert(node->right);
            return WangHaoAlgorithm(lft, rht);
        }
        else if (node->value == '2')
        {
            lft.erase(it);
            Node* leftChild = node->left;
            Node* rightChild = node->right;
            lft.insert(leftChild);
            bool ans1=WangHaoAlgorithm(lft, rht);
            lft.erase(leftChild);
            lft.insert(rightChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
        else if (node->value == '3')
        {
            lft.erase(it);
            rht.insert(node->right);
            return WangHaoAlgorithm(lft, rht);
        }
        else if (node->value == '4')
        {
            lft.erase(it);
            Node* leftChild = node->left;
            Node* rightChild = node->right;
            lft.insert(rightChild);
            bool ans1=WangHaoAlgorithm(lft, rht);
            lft.erase(rightChild);
            rht.insert(leftChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
        else if (node->value == '5')
        {
            lft.erase(it);
            Node* leftChild = node->left;
            Node* rightChild = node->right;
            lft.insert(leftChild);
            lft.insert(rightChild);
            bool ans1=WangHaoAlgorithm(lft, rht);
            lft.erase(leftChild);
            lft.erase(rightChild);
            rht.insert(leftChild);
            rht.insert(rightChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
    }
    for(auto it = rht.begin(); it != rht.end(); ++it)
    {
        auto node = *it;
        if (node->value == '1')
        {
            rht.erase(it);
            Node *leftChild = node->left;
            Node *rightChild = node->right;
            rht.insert(leftChild);
            bool ans1 = WangHaoAlgorithm(lft, rht);
            rht.erase(leftChild);
            rht.insert(rightChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
        else if (node->value == '2')
        {
            rht.erase(it);
            Node *leftChild = node->left;
            Node *rightChild = node->right;
            rht.insert(leftChild);
            rht.insert(rightChild);
            return WangHaoAlgorithm(lft, rht);
        }
        else if (node->value == '3')
        {
            rht.erase(it);
            lft.insert(node->right);
            return WangHaoAlgorithm(lft, rht);
        }
        else if (node->value == '4')
        {
            rht.erase(it);
            Node *leftChild = node->left;
            Node *rightChild = node->right;
            lft.insert(leftChild);
            bool ans1 = WangHaoAlgorithm(lft, rht);
            lft.erase(leftChild);
            rht.insert(rightChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
        else if (node->value == '5')
        {
            rht.erase(it);
            Node *leftChild = node->left;
            Node *rightChild = node->right;
            lft.insert(leftChild);
            rht.insert(rightChild);
            bool ans1 = WangHaoAlgorithm(lft, rht);
            lft.erase(leftChild);
            rht.erase(rightChild);
            rht.insert(leftChild);
            lft.insert(rightChild);
            return WangHaoAlgorithm(lft, rht) && ans1;
        }
    }
    return judge(lft, rht);
}

void deleteTree(Node *root)
{
    if (!root) return;              // 空树，直接返回
    deleteTree(root->left);  // 先删除左子树
    deleteTree(root->right); // 再删除右子树
    delete root;             // 最后删除根节点
    return;
}

int main()
{
    notice();
    string infix;
    cin >> infix;
    
    set<Node*> lft;
    set<Node*> rht;

    try
    {
        Node* root = infixToTree(infix);

        if (root->value == '4')
        {
            auto l = root->left;
            lft.insert(l);
            auto r = root->right;
            rht.insert(r);
        }
        else
        {
            rht.insert(root);
        } // 转换为王浩相继式，初始化左右map
        bool result = WangHaoAlgorithm(lft, rht);

        deleteTree(root); // 删除树，释放内存

        cout << (result ? "The formula is TRUE." : "The formula is not true at some assignment.") << endl;
    }
    catch (const string &e)
    {
        cout << "Error: " << e << endl;
        return 1;
    }
    return 0;
}