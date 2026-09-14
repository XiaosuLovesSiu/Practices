//采用了控制“望舒”和“飞廉”两个指针的间隔为n的方法，实现了对倒数第N个元素的定位。
//也可使用反转链表函数。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==nullptr||head->next==nullptr) return nullptr;
        ListNode* wangshu=head;
        ListNode* feilian=head;

        for(int i=0;i<n;i++)
        {
            wangshu=wangshu->next;
        }
        if(wangshu==nullptr)
        {
            head=head->next;
            delete feilian;
            return head;
        }
        while(wangshu->next)
        {
            wangshu=wangshu->next;
            feilian=feilian->next;
        }
        ListNode* deleter=feilian->next;
        feilian->next=deleter->next;
        delete deleter;
        return head;
    }
};