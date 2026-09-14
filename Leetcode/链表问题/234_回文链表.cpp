#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//方法一。采取模块化方法，用反转链表函数处理回文检验中单链表无法反向遍历的问题。

class Solution1 {
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
        for(int i=1;i<nodeNum;i++)
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

    bool isPalindrome(ListNode* head) {
        if(head->next==nullptr) return true;
        ListNode* beforeMid=middleNode(head);
        ListNode* Mid=beforeMid->next;
        beforeMid->next=nullptr;
        Mid=reverseList(Mid);
        ListNode* thr=head;
        ListNode* memMid=Mid;
        while(thr)
        {
            if(thr->val!=Mid->val) return false;
            else
            {
                thr=thr->next;
                Mid=Mid->next;
            }
        }
        memMid=reverseList(memMid);
        beforeMid->next=memMid;
        return true;
    }
};

//方法二。直接用数组存储链表元素，利用双指针法判断回文。

class Solution2 {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vlist;
        while(head!=nullptr)
        {
            vlist.push_back(head->val);
            head=head->next;
        }
        for(int i=0,j=vlist.size()-1;i<j;i++,j--)
        {
            if(vlist.at(i)!=vlist.at(j)) return false;
        }
        return true;
    }
};