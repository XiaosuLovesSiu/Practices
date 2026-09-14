//使用了三个指针的方法，可读性更强，更直观。也可减少一个指针的使用。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* now=head;
        ListNode* past=nullptr;
        if(head==nullptr) return nullptr;
        ListNode* future=now->next;
        while(future)
        {
            now->next=past;
            past=now;
            now=future;
            future=future->next;
        }
        now->next=past;
        return now;
    }
};