//Floyd判圈算法，快慢指针法。快指针每次走两步，慢指针每次走一步，如果有环，则快慢指针必定相遇。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fi=head;
        ListNode* si=head;
        while(fi!=nullptr && fi->next!=nullptr)
        {
            fi=fi->next->next;
            si=si->next;
            if(fi==si) return true;
        }
        return false;
    }
};