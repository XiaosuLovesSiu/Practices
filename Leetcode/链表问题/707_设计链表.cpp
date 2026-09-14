//设计并实现我的链表！

struct clist
{
    int val;
    clist* next;
};
class MyLinkedList {
private:
    clist* p_dum;
public:
    MyLinkedList() {
        this->p_dum= new clist{0,nullptr};
    }
    
    int get(int index) {
        clist* p_ind=p_dum;
        if(index<0) return -1;
        for(int i=0;i<=index;i++)
        {
            if(p_ind->next==nullptr) return -1;
            p_ind=p_ind->next;
        }
        return p_ind->val;
    }
    
    void addAtHead(int val) {
        clist* temp0=p_dum;
        p_dum->next=new clist{val,temp0->next};
    }
    
    void addAtTail(int val) {
        clist* p_find=p_dum;
        while(p_find->next!=nullptr)
        {
            p_find=p_find->next;
        }
        p_find->next=new clist{val,nullptr};;
    }
    
    void addAtIndex(int index, int val) {
        if(index==0)
        {
            addAtHead(val);
        }
        bool success=(index>0)?true:false;
        clist* p_ind2=p_dum;
        for(int i=0;i<=index-1;i++)
        {
            if(p_ind2==nullptr)
            {
                success=false;
                break;
            }
            p_ind2=p_ind2->next;
        }
        if(success)
        {
            clist* tp=p_ind2->next;
            p_ind2->next=new clist{val,tp};
        }
    }
    
    void deleteAtIndex(int index) {
        bool success3=(index>=0)?true:false;
        clist* p_ind3=p_dum;
        for(int i=0;i<=index-1;i++)
        {
            if(p_ind3->next==nullptr)
            {
                success3=false;
                break;
            }
            if(p_ind3->next->next==nullptr)
            {
                success3=false;
                break;
            }
            p_ind3=p_ind3->next;
        }
        if(success3)
        {
            clist* temp=p_ind3->next;
            p_ind3->next=temp->next;
            delete temp;
        }
    }
};