#include<iostream>
using namespace std;
#include"simple_lk_list.h"

template <class ElemType>
void Difference(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, 
SimpleLinkList<ElemType> &lc)
// 初始条件: la和lb中数据元素递增有序
// 操作结果: lc返回la与lb表示集合的差集，并使lc中数据元素仍递增有序
{
    ElemType aElem,bElem;
    lc.Clear();
    for(int aPos=1;aPos<=la.Length();aPos++)
    {
        la.GetElem(aPos,aElem);
        bool isExist = false;
        for(int bPos=1;bPos<=lb.Length();bPos++)
        {
            lb.GetElem(bPos,bElem);
            if(aElem==bElem)
            {
                isExist = true;
                break;
            }
        }
        if(!isExist)
        {
            lc.Insert(lc.Length()+1,aElem);
        }
    }
    
}

template <class ElemType>
void SimpleLinkList<ElemType>::Reverse()
// 操作结果: 利用原结点空间逆置单链表中元素的的顺序
{
    Node<ElemType>* temp;
    Node<ElemType>* cur;
    cur=head->next->next;
    head->next->next=NULL;
    while(cur)//cur为最后一个元素的指针域时，退出循环
    {
        temp=cur->next;
        cur->next=head->next;
        head->next=cur;
        cur=temp;
    }
}
