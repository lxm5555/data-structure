#include <iostream>
using namespace std;
#include"sq_list.h"
template<class ElemType>
void Difference(const SqList<ElemType>&la,const SqList<ElemType>&lb,SqList<ElemType>&lc)
{
    ElemType aElem,bElem;
    lc.Clear();
    for(int aPos=1;aPos<=la.Length();aPos++)
    {
        la.GetElem(aPos,aElem);
        bool isExist=false;
        for(int bPos=1;bPos<=lb.Length();bPos++)
        {
            lb.GetElem(bPos,bElem);
            if(aElem==bElem)
            {
                isExist=true;
                break;
            }
        }
        if(!isExist)
        {
            lc.Insert(lc.Length()+1,aElem);
        }
    }
}
void Adjust(SqList<int>&la)
{
    int leftPos=1,rightPos=la.Length();
    int aElem,bElem;
    while(leftPos<rightPos)
    {
        la.GetElem(leftPos,aElem);
        la.GetElem(rightPos,bElem);
        if(aElem%2==1)
        {
            leftPos++;
        }
        else if(bElem%2==0)
        {
            rightPos--;
        }
        else
        {
            la.SetElem(leftPos++,bElem);
            la.SetElem(rightPos--,aElem);
        }
    }
}