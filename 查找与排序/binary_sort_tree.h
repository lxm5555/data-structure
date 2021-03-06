#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"										// 链队列
#include "bin_tree_node.h"									// 二叉树结点类模板

// 二叉排序树类模板
template <class ElemType, class KeyType>
class BinarySortTree
{
protected:
// 数据成员:
	BinTreeNode<ElemType> *root;

// 辅助函数模板:
	BinTreeNode<ElemType> *CopyTreeHelp(const BinTreeNode<ElemType> *r) const ;					// 复制二叉排序树
	void DestroyHelp(BinTreeNode<ElemType> * &r);			// 销毁以r为根二叉排序树
	void PreOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	// 先序遍历
	void InOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	// 中序遍历
	void PostOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	// 后序遍历
    int HeightHelp(const BinTreeNode<ElemType> *r) const;	// 返回二叉排序树的高
	int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// 返回二叉排序树的结点个数
	BinTreeNode<ElemType> *ParentHelp(const BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *cur) const;			// 返回cur的双亲
	BinTreeNode<ElemType> *SearchHelp(const KeyType &key, BinTreeNode<ElemType> *&f) const;		// 查找元素的值为key的数据元素
//	BinTreeNode<ElemType> *SearchHelp(const ElemType &key, BinTreeNode<ElemType> *&f) const;	// 查找元素的值为key的数据元素
	void DeleteHelp(BinTreeNode<ElemType> *&p);				// 删除p指向的结点

public:
// 二叉排序树方法声明及重载编译系统默认方法声明:
	BinarySortTree();										// 无参数的构造函数模板
	virtual ~BinarySortTree();								// 析构函数模板
	const BinTreeNode<ElemType> *GetRoot() const;			// 返回二叉排序树的根
	bool Empty() const;										// 判断二叉排序树是否为空
	bool GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const;	// 用e返回结点数据元素值
	bool SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);		// 将结点cur的值置为e
	void InOrder(void (*visit)(const ElemType &)) const;	// 二叉排序树的中序遍历	
	void PreOrder(void (*visit)(const ElemType &)) const;	// 二叉排序树的先序遍历
	void PostOrder(void (*visit)(const ElemType &)) const;	// 二叉排序树的后序遍历
	void LevelOrder(void (*visit)(const ElemType &)) const;	// 二叉排序树的层次遍历
	int NodeCount() const;									// 返回二叉排序树的结点个数
	BinTreeNode<ElemType> *Search(const KeyType &key) const;// 查找值为key的数据元素
	bool Insert(const ElemType &e);							// 插入数据元素e
	bool Delete(const KeyType &key);						// 删除关键字为key的数据元素
	const BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的左孩子
	const BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的右孩子
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的双亲
	int	Height() const;										// 返回二叉排序树的高
	BinarySortTree(const ElemType &e);						// 建立以e为根的二叉排序树
	BinarySortTree(const BinarySortTree<ElemType, KeyType> &source);	// 复制构造函数模板
	BinarySortTree(BinTreeNode<ElemType> *r);				// 建立以r为根的二叉排序树
	BinarySortTree<ElemType, KeyType> &operator=
		(const BinarySortTree<ElemType, KeyType>& source);	// 重载赋值运算符
};

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt);
	//	树状形式显示二叉排序树 

// 二叉排序树类的实现部分
template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree()
// 操作结果：构造一个空二叉排序树
{
	root = NULL;
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::~BinarySortTree()
// 操作结果：销毁二叉排序树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType, class KeyType>
const BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::GetRoot() const
// 操作结果：返回二叉排序树的根
{
	return root;
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Empty() const
// 操作结果：判断二叉排序树是否为空
{
	return root == NULL;
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const
// 操作结果：用e返回结点cur数据元素值，如果不存在结点cur，返回false，否则返回true
{
	if (cur == NULL)	
	{	// 不存在结点cur
		return false;										// 返回false
	}
	else
	{	// 存在结点cur
		e = cur->data;										// 用e返回数据元素值
		return true;										// 返回true
	}
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
// 操作结果：如果不存在结点cur，则返回false，否则返回true，并将结点cur的值设置为e
{
	if (cur == NULL)	
	{	// 不存在结点cur
		return false;										// 返回false
	}
	else
	{	// 存在结点cur
		cur->data = e;										// 将结点cur的值设置为e
		return true;										// 返回true
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PreOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		(*visit)(r->data);									// 访问根结点
		PreOrderHelp(r->leftChild, visit);					// 遍历左子树
		PreOrderHelp(r->rightChild, visit);					// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PreOrder(void (*visit)(const ElemType &)) const
// 操作结果：先序遍历二叉排序树
{
	PreOrderHelp(root, visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, visit);					// 遍历左子树
		(*visit)(r->data);									// 访问根结点
		InOrderHelp(r->rightChild, visit);					// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrder(void (*visit)(const ElemType &)) const
// 操作结果：中序遍历二叉排序树
{
	InOrderHelp(root, visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, visit);					// 遍历左子树
		PostOrderHelp(r->rightChild, visit);				// 遍历右子树
		(*visit)(r->data);									// 访问根结点
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrder(void (*visit)(const ElemType &)) const
// 操作结果：后序遍历二叉排序树
{
	PostOrderHelp(root, visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::LevelOrder(void (*visit)(const ElemType &)) const
// 操作结果：层次遍历二叉排序树
{
	LinkQueue<BinTreeNode<ElemType> *> q;					// 队列
	BinTreeNode<ElemType> *t = root;						// 从根结点开始进行层次遍历
	
	if (t != NULL) q.InQueue(t);							// 如果根非空,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(t);     
		(*visit)(t->data);
		if (t->leftChild != NULL)							// 左孩子非空
			q.InQueue(t->leftChild);						// 左孩子入队
		if (t->rightChild != NULL)							// 右孩子非空
			q.InQueue(t->rightChild);						// 右孩子入队
	}
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::HeightHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉排序树的高
{
	if(r == NULL)
	{	// 空二叉排序树高为0
		return 0;
	}
	else
	{	// 非空二叉排序树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);					// 左子树的高
		rHeight = HeightHelp(r->rightChild);				// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉排序树高为左右子树的高的最大值再加1
	}
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::Height() const
// 操作结果：返回二叉排序树的高
{
	return HeightHelp(root);
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const ElemType &e)
// 操作结果：建立以e为根的二叉排序树
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉排序树的结点个数
{
	if (r ==NULL) return 0;									// 空二叉排序树结点个数为0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// 非空二叉排序树结点个为左右子树的结点个数之和再加1
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCount() const
// 操作结果：返回二叉排序树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType, class KeyType>
const BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::LeftChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的左孩子
{
	return cur->leftChild;
}

template <class ElemType, class KeyType>
const BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::RightChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的右孩子
{
	return cur->rightChild;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> * BinarySortTree<ElemType, KeyType>::ParentHelp(const BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
// 操作结果：返回以r为根的二叉排序树，结点cur的双亲
{
	if (r == NULL) return NULL;								// 空二叉排序树
	else if (r->leftChild == cur || r->rightChild == cur) return r; // r为cur的双亲
	else
	{	// 在子树上求双亲
		const BinTreeNode<ElemType> *temPtr;
		
		temPtr = ParentHelp(r->leftChild, cur);				// 在左子树上求cur的双亲	
		if (temPtr != NULL) return temPtr;					// 双亲在左子树上

		temPtr = ParentHelp(r->rightChild, cur);			// 在右子树上求cur的双亲	
		if (temPtr != NULL) return temPtr;					// 双亲在右子树上
		else return NULL;									// 表示cur无双亲
	}
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Parent(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的双亲
{
	return ParentHelp(root, cur);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::SearchHelp(const KeyType &key, 
	BinTreeNode<ElemType> *&f) const
// 操作结果: 返回指向元素的值为key的数据元素的指针，用f返回其双亲
{
	BinTreeNode< ElemType> *p = root;						// 指向根结点
	f = NULL;												// 指向p的双亲
	
	while (p != NULL && p->data != key)
	{	// 查找元素的值为key的结点
		if (key < p->data)
		{	// key更小，在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else
		{	// key更大，在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	
	return p;
}
/*
template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::SearchHelp(const ElemType &key, 
	BinTreeNode<ElemType> *&f) const
// 操作结果: 返回指向元素的值为key的数据元素的指针，用f返回其双亲
{
	BinTreeNode< ElemType> *p = root;						// 指向根结点
	f = NULL;												// 指向p的双亲
	
	while (p != NULL && p->data != key)
	{	// 查找元素的值为key的结点
		if (key < p->data)
		{	// key更小，在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else
		{	// key更大，在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	
	return p;
}
*/
template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Search(const KeyType &key) const 
// 操作结果: 返回指向值为为key的数据元素的指针
{
	BinTreeNode<ElemType> *f;								// 指向被查找结点的双亲
	return SearchHelp(key, f);
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Insert(const ElemType &e)
// 操作结果: 插入数据元素e
{
	BinTreeNode<ElemType> *f;								// 指向被查找结点的双亲

	if (SearchHelp(e, f) == NULL)
	{	// 查找失败，插入成功
		BinTreeNode<ElemType> *p;							// 插入的新结点
		p = new BinTreeNode<ElemType>(e);
		if (Empty())
		{	// 空二叉树，新结点为根结点
			root = p;
		}
		else if (e < f->data)
		{	// e更小，插入结点为f的左孩子
			f->leftChild = p;
		}
		else
		{	// e更大，插入结点为f的右孩子
			f->rightChild = p;
		}

		return true;		
	}
	else
	{	// 查找成功，插入失败
		return false;
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DeleteHelp(BinTreeNode<ElemType> *&p)
// 操作结果: 删除p指向的结点
{
	BinTreeNode<ElemType> *temPtr, *temF;  
	if (p->leftChild == NULL && p->rightChild == NULL)
	{	// p为叶结点
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)
	{	// p只有左子树为空
		temPtr = p;
		p = p->rightChild;
		delete temPtr;
	}
	else if (p->rightChild == NULL)
	{	// p只有右子树非空
		temPtr = p;
		p = p->leftChild;
		delete temPtr;
	}
	else
	{	// p左右子非空
		temF = p;
		temPtr = p->leftChild;
		while (temPtr->rightChild != NULL)
		{	// 查找p在中序序列中直接前驱temPtr及其双亲temF，直到temPtr右子树为空
			temF = temPtr;
			temPtr = temPtr->rightChild;
		}
		p->data = temPtr->data;								// 将temPtr指向结点的数据元素值赋值给p指向结点的数据元素

		// 删除temPtr指向的结点
		if (temF->rightChild == temPtr)
		{	// 删除temF的右孩子
			DeleteHelp(temF->rightChild);
		}
		else
		{	// 删除temF的左孩子
			DeleteHelp(temF->leftChild);
		}
	}
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Delete(const KeyType &key)
// 操作结果: 删除关键字为key的数据元素
{
	BinTreeNode<ElemType> *p, *f;
	p = SearchHelp(key, f);
	if ( p == NULL)
	{	// 查找失败，删除失败
		return false;
	}
	else
	{	// 查找成功，插入失败
		if (f == NULL)
		{	// 被删除结点为根结点
			DeleteHelp(root);
		}
		else if (key < f->data)
		{	// key更小，删除f的左孩子
			DeleteHelp(f->leftChild);
		}
		else
		{	// key更大，删除f的右孩子
			DeleteHelp(f->rightChild);
		}
		return true;		
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DestroyHelp(BinTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉排序树
{
	if(r != NULL)
	{	// r非空,实施销毁
		DestroyHelp(r->leftChild);							// 销毁左子树
		DestroyHelp(r->rightChild);							// 销毁右子树
		delete r;											// 销毁根结点
		r = NULL;
	}
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::CopyTreeHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：将以r为根的二叉排序树复制成新的二叉排序树，返回新二叉排序树的根
{
	if (r == NULL)
	{	// 复制空二叉排序树
		return NULL;										// 空二叉排序树根为空	
	}
	else
	{	// 复制非空二叉排序树
		BinTreeNode<ElemType> *lChild = CopyTreeHelp(r->leftChild);		// 复制左子树
		BinTreeNode<ElemType> *rChild = CopyTreeHelp(r->rightChild);	// 复制右子树
		BinTreeNode<ElemType> *rt = new BinTreeNode<ElemType>(r->data, lChild, rChild);		// 复制根结点
		return rt;
	}
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const BinarySortTree<ElemType, KeyType> &source)
// 操作结果：由已知二叉排序树构造新二叉排序树——复制构造函数模板
{
	root = CopyTreeHelp(source.root);						// 复制二叉排序树
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉排序树
{	
	root = r;	// 复制二叉排序树
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType> &BinarySortTree<ElemType, KeyType>::operator=(const BinarySortTree<ElemType, KeyType> &source)
// 操作结果：由已知二叉排序树source复制到当前二叉排序树——重载赋值运算符
{
	if (&source != this)
	{
		DestroyHelp(root);									// 释放原二叉排序树所占用空间
		root = CopyTreeHelp(source.root);					// 复制二叉排序树
	}
	return *this;
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->rightChild, level + 1);//显示右子树
		cout << endl;										// 显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";									// 确保在第level列显示结点
		cout << r->data;									// 显示结点
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->leftChild, level + 1);	//显示左子树
	}
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt)
//	操作结果：树状形式显示二叉排序树 
{
	DisplayBTWithTreeShapeHelp<ElemType, KeyType>(bt.GetRoot(), 1);				// 树状显示以bt.GetRoot()为根的二叉排序树
	cout << endl;
}

#endif
