//仍然采用原地修改链表值的方法，时间复杂度O(n)，空间复杂度O(1)。
//也有一种巧妙的双指针做法，为官方题解，附于下方。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* recover=headA;
        while(headA)
        {
            headA->val+=1e6;
            headA=headA->next;
        }
        while(headB)
        {
            if(headB->val>1e6)
            {
                break;
            }
            headB=headB->next;
        }
        while(recover)
        {
            recover->val-=1e6;
            recover=recover->next;
        }
        return headB;
    }
};

class officialSolution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *A = headA, *B = headB;
        while (A != B) {
            A = A != nullptr ? A->next : headB;
            B = B != nullptr ? B->next : headA;
        }
        return A;
    }
};
/*
作者：Krahets
链接：https://leetcode.cn/problems/intersection-of-two-linked-lists/solutions/12624/intersection-of-two-linked-lists-shuang-zhi-zhen-l/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/