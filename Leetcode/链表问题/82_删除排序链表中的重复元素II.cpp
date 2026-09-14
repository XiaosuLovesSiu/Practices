//哈希表思路，直接重新构建答案链表。空间复杂度更高。
#include <map>
using namespace std;

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
        map<int,int> mop;
        ListNode* point=head;
        ListNode* dummy=new ListNode(-101);
        ListNode* str=dummy;
        while(point)
        {
            mop[point->val]++;
            point=point->next;
        }
        for(auto [key,value] : mop)
        {
            if(value==1)
            {
                str->next=new ListNode(key);
                str=str->next;
            }
        }
        str=dummy->next;
        delete dummy;
        return str;
    }
};