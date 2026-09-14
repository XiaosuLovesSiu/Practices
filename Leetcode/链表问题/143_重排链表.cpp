//综合运用了找中点、反转链表、合并链表的方法完成了本题，体现了模块化思想。也可用数组+双指针处理。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* searcher=head;
        ListNode* flagger=head;
        int nodeNum=0;

        while(searcher!=nullptr)
        {
            nodeNum++;
            searcher=searcher->next;
        }
        nodeNum/=2;
        for(int i=0;i<nodeNum;i++)
        {
            flagger=flagger->next;
        }
        return flagger;
    }
    
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

    void mergeLists(ListNode* l1, ListNode* l2) {
        ListNode* fu1;
        ListNode* fu2;
        while(l1!=nullptr && l2!=nullptr)
        {
            fu1=l1->next;
            fu2=l2->next;
            l1->next=l2;
            l1=fu1;
            l2->next=l1;
            l2=fu2;
        }
    }

    void reorderList(ListNode* head) {
        if(head!=nullptr && head->next!=nullptr)
        {
            ListNode* mNode=middleNode(head);
            ListNode* startNode=mNode->next;
            mNode->next=nullptr;
            ListNode* l=reverseList(startNode);
            mergeLists(head,l);
        }
    }
};