//分输入栈、输出栈，用函数pour来把栈的最后面元素倒腾到最前面

#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> stk1;
    stack<int> stk2;
    void pour()
    {
        while(stk1.empty()==false)
        {
            stk2.push(stk1.top());
            stk1.pop();
        }
    }
public:

    MyQueue() {

    }
    
    void push(int x) {
        this->stk1.push(x);
    }
    
    int pop() {
        if(stk2.empty()) this->pour();
        int val=stk2.top();
        this->stk2.pop();
        return val;
    }
    
    int peek() {
        if(stk2.empty()) this->pour();
        return this->stk2.top();
    }
    
    bool empty() {
        return this->stk1.empty() && this->stk2.empty();
    }
};