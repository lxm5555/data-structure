#ifndef __NODE_H__
#define __NODE_H__

// �����ģ��
template <class ElemType>
struct Node 
{
// ���ݳ�Ա:
	ElemType data;				// ���ݳɷ�
	Node<ElemType> *next;		// ָ��ɷ�

// ���캯��ģ��:
	Node();						// �޲����Ĺ��캯��ģ��
	Node(const ElemType &e, Node<ElemType> *link = NULL);	// ��֪����Ԫ��ֵ��ָ�뽨�����
};

// �����ģ���ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ��ɷ�Ϊ�յĽ��
{
	next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(const ElemType &e, Node<ElemType> *link)
// �������������һ�����ݳɷ�Ϊe��ָ��ɷ�Ϊlink�Ľ��
{
	data = e;
	next = link;
}

#endif
