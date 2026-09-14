//间隔了一个节点的双指针，操作更灵活，避免了使用临时的temp指针。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==nullptr) return head;
        if(head->next==nullptr) return head;

        ListNode* dummy=new ListNode(-1,head);

        ListNode* front=dummy->next->next;
        ListNode* back=dummy;


        while(true)
        {
            back->next->next=front->next;
            front->next=back->next;
            back->next=front;
            front=front->next;

            if(front->next==nullptr) return dummy->next;
            if(front->next->next==nullptr) return dummy->next;
            front=front->next->next;
            back=back->next->next;
        }
        return dummy->next;
    }
};