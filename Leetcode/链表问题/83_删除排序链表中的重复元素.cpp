//相对直观且行之有效的双指针方法。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        ListNode* fp=head->next;
        ListNode* sp=head;
        while(fp)
        {
            if(sp->val==fp->val)
            {
                ListNode* temp=fp->next;
                sp->next=temp;
                delete fp;
                fp=temp;
            }
            else 
            {
                sp=sp->next;
                fp=fp->next;
            }
        }
        return head;
    }
};