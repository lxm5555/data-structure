#ifndef __BIN_TREE_NODE_H__
#define __BIN_TREE_NODE_H__

// �����������ģ��
template <class ElemType>
struct BinTreeNode
{
// ���ݳ�Ա:
	ElemType data;						// ���ݳɷ�
	BinTreeNode<ElemType>  *leftChild;	// ����ָ��ɷ�
	BinTreeNode<ElemType>  *rightChild;	// �Һ���ָ��ɷ�

//	���캯��ģ��:
	BinTreeNode();		// �޲����Ĺ��캯��ģ�� 
	BinTreeNode(const ElemType &ee,		// ��֪����Ԫ��ֵ,ָ�����Һ��ӵ�ָ�빹��һ�����
		BinTreeNode<ElemType> *lChild = NULL, 
		BinTreeNode<ElemType> *rChild = NULL);
};

// �����������ģ���ʵ�ֲ���
template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = NULL;	// Ҷ������Һ���Ϊ��
}

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType &e, 
	BinTreeNode<ElemType> *lChild, BinTreeNode<ElemType> *rChild)
// �������������һ�����ݳɷ�Ϊval,����ΪlChild,�Һ���ΪrChild�Ľ��
{	
	data = e;					// ����Ԫ��ֵ
	leftChild = lChild;			// ����
	rightChild = rChild;		// �Һ���
}

#endif

