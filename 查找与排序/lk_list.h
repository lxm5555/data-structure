#ifndef __LK_LIST_H__
#define __LK_LIST_H__
#include <iostream>						
using namespace std;
#include "node.h"									// �����ģ��

// ����������ģ��
template <class ElemType>
class LinkList 
{
//protected:
public:
// ���ݳ�Ա:
	Node<ElemType> *head;							// ͷ���ָ��
	mutable int curPosition;						// ��ǰλ�õ����
	mutable Node<ElemType> *curPtr;					// ָ��ǰλ�õ�ָ��
	int count;										// Ԫ�ظ���

// ��������ģ��:
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkList();										// �޲����Ĺ��캯��ģ��
	virtual ~LinkList();							// ��������ģ��
	int Length() const;								// �����Ա���			 
	bool Empty() const;								// �ж����Ա��Ƿ�Ϊ��
	void Clear();									// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;			// �������Ա�
	bool GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	bool Delete(int position);						// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);	// ����Ԫ��
	LinkList(const LinkList<ElemType> &source);		// ���ƹ��캯��ģ��
	LinkList<ElemType> &operator =(const LinkList<ElemType> &source); // ���ظ�ֵ�����

	/*template <class ElemType>
	friend*/ void InsertSort(LinkList<ElemType> &la);
};


// ������ģ���ʵ�ֲ���
template<class ElemType>
Node<ElemType> *LinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (curPosition > position)
	{	// ��ǰλ����������λ��֮��,ֻ�ܴӱ�ͷ��ʼ����
		curPosition = 0;
		curPtr = head;
	}

	for (; curPosition < position; curPosition++)
		curPtr = curPtr->next;						// ����λ��position

	return curPtr;
}

template <class ElemType>
LinkList<ElemType>::LinkList()
// �������������һ��������
{
	head = new Node<ElemType>;						// ����ͷ���
	curPtr = head;	curPosition = 0;				// ��ʼ����ǰλ��
	count = 0;										// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
// ����������������Ա�
{
	Clear();										// ������Ա�
	delete head;									// �ͷ�ͷ�����ָ�ռ�
}

template <class ElemType>
int LinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool LinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == NULL;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
// ���������������Ա�
{

	while (!Empty())
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1);									// ɾ����1��Ԫ��
	}
}

template <class ElemType>
void LinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const 
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *temPtr = head->next; temPtr != NULL; temPtr = temPtr->next)
	{	// ��temPtr����ָ��ÿ��Ԫ��
		(*visit)(temPtr->data);						// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
bool LinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true,
//	���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;								// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *temPtr = GetElemPtr(position);				// ȡ��ָ���position������ָ��	
		e = temPtr->data;							// ��e���ص�position��Ԫ�ص�ֵ
		return true;								// Ԫ�ش���
	}
}

template <class ElemType>
bool LinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;								// ��Χ��
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *temPtr = GetElemPtr(position);				// ȡ��ָ���position������ָ��
		temPtr->data = e;							// ���õ�position��Ԫ�ص�ֵ
		return true;								// ����Ԫ�سɹ�
	}
}

template <class ElemType>
bool LinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;								// ��Χ��
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *temPtr = GetElemPtr(position - 1);			// ȡ��ָ���position-1������ָ��
		Node<ElemType> *nextPtr = temPtr->next;		// nextPtrΪtemPtr�ĺ��
		temPtr->next = nextPtr->next;				// ɾ�����
		e = nextPtr->data;							// ��e���ر�ɾ���Ԫ��ֵ	
		if (position == Length())
		{	// ɾ��β���,��ǰ����Ϊͷ���
			curPosition = 0;						// ���õ�ǰλ�õ����
			curPtr = head;							// ����ָ��ǰλ�õ�ָ��
		}
		else
		{	// ɾ����β���,��ǰ����Ϊ��position�����
			curPosition = position;					// ���õ�ǰλ�õ����
			curPtr = temPtr->next;					// ����ָ��ǰλ�õ�ָ��
		}
		count--;									// ɾ���ɹ���Ԫ�ظ�����1 
		delete nextPtr;								// �ͷű�ɾ���
		return true;								// ɾ���ɹ�
	}
}

template <class ElemType>
bool LinkList<ElemType>::Delete(int position)
// ���������ɾ�����Ա�ĵ�position��Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;								// ��Χ��
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *temPtr = GetElemPtr(position - 1);			// ȡ��ָ���position-1������ָ��
		Node<ElemType> *nextPtr = temPtr->next;		// nextPtrΪtemPtr�ĺ��
		temPtr->next = nextPtr->next;				// ɾ�����
		if (position == Length())
		{	// ɾ��β���,��ǰ����Ϊͷ���
			curPosition = 0;						// ���õ�ǰλ�õ����
			curPtr = head;							// ����ָ��ǰλ�õ�ָ��
		}
		else
		{	// ɾ����β���,��ǰ����Ϊ��position�����
			curPosition = position;					// ���õ�ǰλ�õ����
			curPtr = temPtr->next;					// ����ָ��ǰλ�õ�ָ��
		}
		count--;									// ɾ���ɹ���Ԫ�ظ�����1 
		delete nextPtr;								// �ͷű�ɾ���
		return true;								// ɾ���ɹ�
	}
}


template <class ElemType>
bool LinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��Ԫ��ǰ����Ԫ��e
//	position��ȡֵ��ΧΪ1��position��Length()+1
//	position�Ϸ�ʱ����true, ���򷵻�false
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false;								// ��Χ��
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *temPtr = GetElemPtr(position - 1);				// ȡ��ָ���position-1������ָ��
		Node<ElemType> *newPtr = new Node<ElemType>(e, temPtr->next);	// �����½��
		temPtr->next = newPtr;						// ��temPtr���뵽������
		curPosition = position;						// ���õ�ǰλ�õ����
		curPtr = newPtr;							// ����ָ��ǰλ�õ�ָ��
		count++;									// ����ɹ���Ԫ�ظ�����1 
		return true;								// ɾ���ɹ�
	}
}

template <class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &source)
// ��������������Ա�source���������Ա������ƹ��캯��ģ��
{
	int sourceLength = source.Length();				// source�ĳ���
	ElemType temElem;								// ��ʱԪ��

	// ��ʼ��һ�������Ա�
	head = new Node<ElemType>;						// ����ͷ���
	curPtr = head;	curPosition = 0;				// ��ʼ����ǰλ��
	count = 0;										// ��ʼ��Ԫ�ظ���

	for (int temPos = 1; temPos <= sourceLength; temPos++)
	{	// ��������Ԫ��
		source.GetElem(temPos, temElem);			// ȡ����temPos��Ԫ��
		Insert(Length() + 1, temElem);				// ��temElem���뵽��ǰ���Ա�
	}
}

template <class ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator =(const LinkList<ElemType> &source)
// ��������������Ա�source��ֵ����ǰ���Ա������ظ�ֵ�����
{
	if (&source != this)
	{
		int sourceLength = source.Length();			// source�ĳ���
		ElemType temElem;							// ��ʱԪ��
		Clear();									// ��յ�ǰ���Ա�

		for (int temPos = 1; temPos <= sourceLength; temPos++)
		{	// ��������Ԫ��
			source.GetElem(temPos, temElem);		// ȡ����temPos��Ԫ��
			Insert(Length() + 1, temElem);			// ��temElem���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif