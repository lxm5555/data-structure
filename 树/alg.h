#include<iostream>
using namespace std;
#include"binary_tree.h"
template <class ElemType>
bool IsFullTree(const BinaryTree<ElemType> &bt)
// 操作结果: 判断二叉树bt是否是满二叉树
{
	if(bt.Empty())//判断空树
	{
		return true;
	}
	else if(!bt.LeftChild(bt.GetRoot())&&!bt.RightChild(bt.GetRoot()))//判断只有根的树
	{
		return true;
	}
	else if(bt.NodeCount()==pow(2,bt.Height())-1)
	{
		return true;
	}
	else	
	return false;
}

template <class ElemType>
bool IsCompleteTree(const BinaryTree<ElemType> &bt)
// 操作结果: 判断二叉树bt是否是完全二叉树
{
    int a=bt.NodeCount();//层次遍历改编，每入队一个便记录+1，
	LinkQueue<const BinTreeNode<ElemType> *> q;	// 队列
	const BinTreeNode<ElemType> *cur;		// 当前结点	

	if (bt.GetRoot() != NULL) q.InQueue(bt.GetRoot());	
	int y=1;	// 如果根非空，则入队，以便从根结点开始进行层次遍历
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(cur);					// 出队结点为当前访问的结点
		if (cur->leftChild != NULL)			// 左孩子非空
		{
			q.InQueue(cur->leftChild);	
			y++;
		}	// 左孩子入队
		else
		break;
		if (cur->rightChild != NULL)		// 右孩子非空
		{
			q.InQueue(cur->rightChild);	
            y++;
		}	// 右孩子入队
		else
		break;
	}
	if(y==a)
	return true;
	else
	return false;
}

template <class ElemType>
bool IsSimilarHelp(const BinTreeNode<ElemType> *r1, const BinTreeNode<ElemType> *r2)
// 操作结果: 判断以r1和r2为根的两棵二叉树是否相似
{
	bool left = false,right=false;
	if(r1==NULL&&r2==NULL) 
	return true;
    else if(r1==NULL||r2==NULL)
	{
		return false;
	}
	else
	{
		left=IsSimilarHelp(r1->leftChild,r2->leftChild);
		right=IsSimilarHelp(r1->rightChild,r2->rightChild);
		return left&&right;
	}
}

template <class ElemType>
bool IsSimilar(const BinaryTree<ElemType> &bt1, const BinaryTree<ElemType> &bt2)
// 操作结果: 判断两棵二叉树是否相似
{
	return IsSimilarHelp(bt1.GetRoot(), bt2.GetRoot());
}

template <class ElemType>
void SwapBiTreeHelp(BinTreeNode<ElemType> *r)
// 操作结果: 交换以r为根的二叉树的所有结点的左右孩子
{
    if(r!=NULL)
	{
		BinTreeNode<ElemType> *temper=r->leftChild;
		r->leftChild=r->rightChild;
		r->rightChild=temper;
		SwapBiTreeHelp(r->leftChild);
		SwapBiTreeHelp(r->rightChild);
	}
}

template <class ElemType>
void SwapBiTree(BinaryTree<ElemType> &bt)
// 操作结果: 交换二叉树的所有结点的左右孩子
{
	SwapBiTreeHelp((BinTreeNode<ElemType> *)bt.GetRoot());	// 调用辅助函数实现交换二叉树的所有结点的左右孩子
}

template <class ElemType>
void CreateBinaryTreeHelp_PostIn(BinTreeNode<ElemType> *&r, ElemType post[], ElemType in[], 
	int postLeft, int postRight, int inLeft, int inRight)
// 操作结果：已知二叉树的后序序列post[postLeft..postRight]和中序序列in[inLeft..inRight]构造
// 以r为根的二叉树
{
    if(postLeft>postRight||inLeft>inRight)
	{
		r=NULL;
	}
	else
	{
		r=new BinTreeNode<ElemType>(post[postRight]);
		int mid=inLeft;
		while(in[mid]!=post[postRight])
		{
            mid++;
		}
		CreateBinaryTreeHelp_PostIn(r->leftChild,post,in,postLeft,postLeft+mid-inLeft-1,inLeft,mid-1);
		CreateBinaryTreeHelp_PostIn(r->rightChild,post,in,postLeft+mid-inLeft,postRight-1,mid+1,inRight);
	}
}

template <class ElemType>
BinaryTree<ElemType> CreateBinaryTree_PostIn(ElemType post[], ElemType in[], int n)
// 操作结果：已知后序和中序序列构造二叉树
{
	BinTreeNode<ElemType> *r;						// 二叉树的根
	CreateBinaryTreeHelp_PostIn<ElemType>(r, post, in, 0, n - 1, 0, n - 1);
	return BinaryTree<ElemType>(r);					// 返回以r为根的二叉树
}

template <class ElemType>
void PreInToPostHelp(ElemType pre[], ElemType in[], ElemType post[], 
	int preLeft, int inLeft, int postLeft, int n)
// 操作结果：已知二叉树的先序序列post[preLeft..]和中序序列in[inLeft..]，
// 给出后序序列post[postLeft..](不构造二叉树)
{
	if(n<1) return;//n记录每次构造的序列有多少个元素
	post[postLeft+n-1]=pre[preLeft];
	int mid=inLeft,a=0;//a记录mid前有多少元素
	while(in[mid]!=pre[preLeft])
	{
        a++;mid++;
	}
	PreInToPostHelp(pre,in,post,preLeft+1,inLeft,postLeft,a);
	PreInToPostHelp(pre,in,post,preLeft+a+1,mid+1,a+postLeft,n-a-1);
}

template <class ElemType>
void PreInToPost(ElemType pre[], ElemType in[], ElemType post[], int n)
// 操作结果：已知先序和中序序列直接输出后序序列(不构造二叉树)
{
	PreInToPostHelp<ElemType>(pre, in, post, 0, 0, 0, n);
}