//不同于141题的Floyd判圈算法，这里通过修改链表节点值标识其是否被访问过，若再次访问到则说明有环。
//此方法不改变链表结构，但执行时会破坏链表节点值。需要避免并行访问该链表。
//最后再次遍历链表，将被修改的节点值恢复为原值。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        const int num=1e6+3*1e5;
        ListNode* rec=head;
        while(head)
        {
            if(head->val>1e6) break;
            else head->val+=num;
            head=head->next;
        }
        while(rec)
        {
            if(rec->val<=1e5) break;
            else rec->val-=num;
            rec=rec->next;
        }
        return head;
    }
};