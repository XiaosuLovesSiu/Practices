//移除链表中等于给定值的节点。使用双指针的经典方法。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int target) {
        while(head!=nullptr && head->val==target)
        {
            ListNode* htemp=head;
            head=head->next;
            delete htemp;
        }
        if(head==nullptr) return nullptr;
        else
        {
            ListNode* indexB=head;
            ListNode* indexP=head->next;
            while(indexP!=nullptr)
            {
                if(indexP->val==target)
                {
                    indexB->next=indexP->next;
                    delete indexP;
                    indexP=indexB->next;
                }
                else
                {
                    indexB=indexP;
                    indexP=indexB->next;
                }
            }
        }
        return head;
    }
};