#include"binary_sort_tree.h"
template <class ElemType, class KeyType>
void InOrderHelp(BinTreeNode<ElemType> *r, const KeyType &key)
// �������: �Ӵ�С�����rΪ���Ķ��������������еĹؼ���ֵ��С��key��Ԫ��ֵ
{
    if(r!=NULL)
	{
		if(r->data<key)//���С����ô��ֱ�ӱ���������
		{
			InOrderHelp(r->rightChild,key);
		}
		else//����Ҳ�ȱ�������������֤�ȰѴ��ڵĽڵ��ҳ������ҴӴ�С��Ȼ��������ٱ�����������
		{
			InOrderHelp(r->rightChild,key);
			cout<<r->data<<" ";
			InOrderHelp(r->leftChild,key);
		}
	}
}

template <class ElemType, class KeyType>
void InOrder(const BinarySortTree<ElemType, KeyType> &t, const KeyType &key)
// �������: �Ӵ�С������������������еĹؼ���ֵ��С��key��Ԫ��ֵ
{
	InOrderHelp((BinTreeNode<ElemType> *)t.GetRoot(), key);
}

template <class ElemType>
bool IsBBTHelp(BinTreeNode<ElemType> *r,int &h)
// �������: �ж���rΪ���Ķ����������Ƿ�Ϊƽ�������, h��ʾ���������������
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
// �������: �ж϶����������Ƿ�Ϊƽ�������
{
	int h;					
	return IsBBTHelp((BinTreeNode<ElemType> *)t.GetRoot(), h);	
}

template <class ElemType>
void InsertSort(LinkList<ElemType> &la)
// �������: �Ե�����Ϊ�洢�ṹʵ��ֱ�Ӳ�������(ͨ���ı�ָ��ʵ��)
{//��Ԫ����������Ա,��Ԫ����δ֪����Ϊ�������ҵ�������ҽ�friendɾ�����ѱ�����Ա�ĳɹ���
    int l=la.count;
	ElemType a;
	ElemType b;
    for(int i=2; i<l+1; i++)
	{
		int t=i;
		for(int j=i-1; j>=1; j--)
		{
            la.GetElem(i,a);//��ǰλ��
			la.GetElem(j,b);
			if(a<b)
                t--;
		}
		if(t!=i)
		{
			Node<ElemType> *p1=la.GetElemPtr(i);//��
			Node<ElemType> *p2=la.GetElemPtr(t);//ǰ
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

