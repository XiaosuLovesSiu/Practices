//重新构建答案链表的思路

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        int memo=0;
        ListNode* thread=head->next;
        ListNode* dummy=new ListNode(-1);
        ListNode* thr=dummy;
        while(thread!=nullptr)
        {
            if(thread->val==0)
            {
                thr->next=new ListNode(memo);
                memo=0;
                thr=thr->next;
            }
            else
            {
                memo+=thread->val;
            }
            thread=thread->next;
        }
        thr=dummy->next;
        delete dummy;
        return thr;
    }
};