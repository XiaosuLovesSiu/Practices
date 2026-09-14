//使用哈希表方法的正解。
#include <vector>
#include <unordered_set>
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
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> dict;
        for(int number : nums)
        {
            dict.insert(number);
        }
        ListNode* thr=head;
        bool onstage=false;
        int res=0;
        while(thr->next)
        {
            if(onstage==true)
            {
                if(dict.find(thr->val)==dict.end())
                {
                    res++;
                    onstage=false;
                }
            }
            else
            {
                if(dict.find(thr->val)!=dict.end())
                {
                    onstage=true;
                }
            }
            thr=thr->next;
        }
        if(onstage==true) res++;
        else
        {
            if(dict.find(thr->val)!=dict.end()) res++;
        }
        return res;
    }
};