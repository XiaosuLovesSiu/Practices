#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(const char val) : value(val), left(nullptr), right(nullptr) {}
};

Node* infixToTree(const string& infix) {
    stack<Node*> s;

    for (char token : infix) 
    {
        if (token != ')') 
        {
            s.push(new Node(token));
        }
        else 
        {
            Node* right = s.top();
            s.pop();
            Node* op = s.top();
            s.pop();
            if(!(op->value == '1' || op->value == '2' || op->value == '3' || op->value == '4' || op->value == '5')) 
            {
                throw string("Invalid operator: ") + op->value;
            }
            if(op->value == '1' || op->value == '2' || op->value == '4' || op->value == '5') 
            {
                Node* left = s.top();
                s.pop();
                op->left = left;
            }
            op->right = right;
            if(s.empty() || s.top()->value != '(') 
            {
                throw string("Invalid expression: missing left parenthesis for operator ") + op->value;
            } 
            s.pop(); // Pop the left parenthesis
            s.push(op);
        }
    }
    Node* root = s.top();
    s.pop();
    if(!s.empty()) 
    {
        throw string("Invalid expression: extra tokens in stack");
    }
    return root;
}
void preorder(Node* root, string& result)
{
    if (!root) return;          // 空树，直接返回
    result += root->value;  // 先访问根节点
    preorder(root->left, result);       // 再遍历左子树
    preorder(root->right, result);      // 最后遍历右子树
    return;
}

void postorder(Node* root, string& result)
{
    if (!root) return;          // 空树，直接返回
    postorder(root->left, result);       // 先遍历左子树
    postorder(root->right, result);      // 再遍历右子树
    result += root->value;  // 最后访问根节点
    return;
}

void deleteTree(Node* root)
{
    if (!root) return;          // 空树，直接返回
    deleteTree(root->left);       // 先删除左子树
    deleteTree(root->right);      // 再删除右子树
    delete root;  // 最后删除根节点
    return;
}

void notice() {
    cout << "Input fully parenthesized infix expression." << endl;
    cout << "Operators: 1(\\land) 2(\\lor) 3(\\lnot) 4(\\rightarrow) 5(\\leftrightarrow)" << endl;
    cout << "Example: ((p1q)4(3r)) for (p\\land q)\\rightarrow\\lnot r" << endl;
    cout << "Variables must be single letters. No spaces." << endl;
}

int main()
{
    int choice;
    cout << "input 1 for polish notation, 2 for reverse polish notation" << endl;
    cin >> choice;
    if(choice != 1 && choice != 2) 
    {
        cerr << "Invalid choice. Please input 1 or 2." << endl;
        return 1;
    }
    string str;
    notice();
    cin >> str;
    try
    {
        auto root = infixToTree(str);
        string result;
        if(choice == 1)
        {
            preorder(root, result);
        }
        else 
        {
            postorder(root, result);
        }
        cout << result << endl;
        deleteTree(root);
    }
    catch (const string& e)
    {
        cerr << e << endl;
    }

    return 0;
}