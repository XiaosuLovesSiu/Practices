//创建一个虚拟头结点，便于操作。使用两个指针迭代完成本题。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
    //题目要求：合并两个升序链表为一个新的升序链表
    {
        if (list1 == nullptr)
            return list2;
        else if (list2 == nullptr)
            return list1;
        //处理空链表情况

        ListNode* pre1=new ListNode(-101,list1);
        ListNode* prep1=pre1;

        ListNode* p1=list1;
        ListNode* p2=list2;
        while(p1 && p2)
        {
            if(p1->val<p2->val)
            {
                p1=p1->next;
                prep1=prep1->next;
            }
            else
            {
                prep1->next=p2;
                ListNode* temp=p2->next;
                p2->next=p1;
                prep1=p2;
                p2=temp;
            }
        }
        if(p1==nullptr) prep1->next=p2;
        ListNode* list=pre1->next;
        delete pre1;
        return list;
    }
}
;