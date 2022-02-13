#include"binary_sort_tree.h"
template <class ElemType, class KeyType>
void InOrderHelp(BinTreeNode<ElemType> *r, const KeyType &key)
// 操作结果: 从大到小输出以r为根的二叉排序树中所有的关键字值不小于key的元素值
{
    if(r!=NULL)
	{
		if(r->data<key)//如果小于那么就直接遍历右子树
		{
			InOrderHelp(r->rightChild,key);
		}
		else//大于也先遍历右子树，保证先把大于的节点找出来并且从大到小，然后输出，再遍历左子树。
		{
			InOrderHelp(r->rightChild,key);
			cout<<r->data<<" ";
			InOrderHelp(r->leftChild,key);
		}
	}
}

template <class ElemType, class KeyType>
void InOrder(const BinarySortTree<ElemType, KeyType> &t, const KeyType &key)
// 操作结果: 从大到小输出二叉排序树中所有的关键字值不小于key的元素值
{
	InOrderHelp((BinTreeNode<ElemType> *)t.GetRoot(), key);
}

template <class ElemType>
bool IsBBTHelp(BinTreeNode<ElemType> *r,int &h)
// 操作结果: 判断以r为根的二叉排序树是否为平衡二叉树, h表示二叉排序树的深度
{
    if(r==NULL) 
	{
		h=0;
        return true;
	}
	int lh=0,rh=0;
	if(IsBBTHelp(r->leftChild,lh)&&IsBBTHelp(r->rightChild,rh))
    {
        int d=abs(lh-rh);
        if(1<d)
        return false;
        h=1+((lh>rh)?lh:rh);
        return true;
    }
    return false;
}

template <class ElemType, class KeyType>
bool IsBBT(const BinarySortTree<ElemType, KeyType> &t)
// 操作结果: 判断二叉排序树是否为平衡二叉树
{
	int h;					
	return IsBBTHelp((BinTreeNode<ElemType> *)t.GetRoot(), h);	
}

template <class ElemType>
void InsertSort(LinkList<ElemType> &la)
// 操作结果: 以单链表为存储结构实现直接插入排序(通过改变指针实现)
{//友元函数保护成员,友元发生未知错误，为了完成作业，所以我将friend删除，把保护成员改成公有
    int l=la.count;
	ElemType a;
	ElemType b;
    for(int i=2; i<l+1; i++)
	{
		int t=i;
		for(int j=i-1; j>=1; j--)
		{
            la.GetElem(i,a);//当前位置
			la.GetElem(j,b);
			if(a<b)
                t--;
		}
		if(t!=i)
		{
			Node<ElemType> *p1=la.GetElemPtr(i);//后
			Node<ElemType> *p2=la.GetElemPtr(t);//前
			Node<ElemType> *p3=la.GetElemPtr(t-1);
			if(p1->next==NULL)
			{
				Node<ElemType> *p4=la.GetElemPtr(i-1);
                p4->next=p1->next;
			    p1->next=p2;
		    p3->next=p1;
			}
			else
			{
				p2->next=p1->next;
	     		p1->next=p2;
				p3->next=p1;
			}
		}
	}
}

