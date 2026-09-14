//对逆序链表的进位处理是本题看点。也可开数组，但无必要。

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* d=new ListNode(-1);
        ListNode* p=d;

        while(l1!=nullptr && l2!=nullptr)
        {
            p->next=new ListNode(l1->val+l2->val);
            p=p->next;
            l1=l1->next;
            l2=l2->next;
        }
        if(l1==nullptr)
        {
            p->next=l2;
        }
        else p->next=l1;
        //使用p创建未进位的答案链表

        ListNode* q=d->next;
        while(q->next!=nullptr)
        {
            if(q->val>=10)
            {
                q->val-=10;
                q->next->val+=1;
            }
            q=q->next;
        }
        if(q->val>=10)
        {
            q->val-=10;
            q->next=new ListNode(1);
        }
        //使用q处理进位

        ListNode* h=d->next;
        delete d;
        return h;
    }
};