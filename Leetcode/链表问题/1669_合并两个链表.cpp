//基本的模拟方法。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        int ind=0;
        ListNode* searcher=list1;
        while(ind<a-1)
        {
            searcher=searcher->next;
            ind++;
        }
        ListNode* deleter=searcher->next;
        searcher->next=list2;
        ind++;
        for(;ind<=b;ind++)
        {
            ListNode* temp=deleter->next;
            delete deleter;
            deleter=temp;
        }
        while(list2->next) list2=list2->next;
        list2->next=deleter;
        return list1;
    }
};