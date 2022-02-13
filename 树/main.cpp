#include <iostream>						
using namespace std;					
#include "binary_tree.h"				
#include "alg.h"	

template <class ElemType>
void DisplaySeq(ElemType seq[], int n)
{
	for(int i = 0; i < n-1; i++)
	{
		cout << seq[i] << ", ";
	}
	cout << seq[n-1];
}

int main()								
{
	char select = '0';
	while (select != '7')
	{
		cout << endl << "1. 判断一棵二叉树是否为满二叉树";
		cout << endl << "2. 判断一棵二叉树是否为完全二叉树";
		cout << endl << "3. 判断两棵二叉树是否相似";
		cout << endl << "4. 交换二叉树的所有节点的左右孩子";
		cout << endl << "5. 由后序序列与中序序列构造二叉树";
		cout << endl << "6. 已知先序和中序序列直接输出后序序列(不构造二叉树)";
		cout << endl << "7. 退出";
		cout << endl << "选择功能(1~7):";
		cin >> select;
		switch (select)
		{
		case '1':
			{
				int pre1[] = {1, 2, 4, 5, 3};		// 先序序列	
				int	in1[] = {4, 2, 5, 1, 3};		// 中序序列 
				int n1 = 5;							// 结点个数
				BinaryTree<int> bt1;				// 二叉树
				bt1 = CreateBinaryTree(pre1, in1, n1);	//建立二叉树
				DisplayBTWithTreeShape(bt1);		// 显示二叉树
				if (IsFullTree(bt1)) cout << endl << "是满二又树" << endl;
				else cout << endl << "不是满二又树" << endl;

				int pre2[] = {1, 2, 4, 5, 3, 6, 7};	// 先序序列	
				int	in2[] = {4, 2, 5, 1, 6, 3, 7};	// 中序序列 
				int n2 = 7;							// 结点个数
				BinaryTree<int> bt2;				// 二叉树
				bt2 = CreateBinaryTree(pre2, in2, n2);	//建立二叉树
				DisplayBTWithTreeShape(bt2);		// 显示二叉树
				if (IsFullTree(bt2)) cout << endl << "是满二又树" << endl;
				else cout << endl << "不是满二又树" << endl;
				break;
			}
		case '2':
			{
				int pre1[] = {1, 2, 4, 3, 5};		// 先序序列	
				int	in1[] = {2, 4, 1, 5, 3};		// 中序序列 
				int n1 = 5;							// 结点个数
				BinaryTree<int> bt1;				// 二叉树
				bt1 = CreateBinaryTree(pre1, in1, n1);	//建立二叉树
				DisplayBTWithTreeShape(bt1);		// 显示二叉树
				if (IsCompleteTree(bt1)) cout << endl << "是完全二又树" << endl;
				else cout << endl << "不是完全二又树" << endl;

				int pre2[] = {1, 2, 4, 5, 3, 6};	// 先序序列	
				int	in2[] = {4, 2, 5, 1, 6, 3};	// 中序序列 
				int n2 = 6;							// 结点个数
				BinaryTree<int> bt2;				// 二叉树
				bt2 = CreateBinaryTree(pre2, in2, n2);	//建立二叉树
				DisplayBTWithTreeShape(bt2);		// 显示二叉树
				if (IsCompleteTree(bt2)) cout << endl << "是完全二又树" << endl;
				else cout << endl << "不是完全二又树" << endl;
				break;
			}
		case '3':
			{
				int pre1[] = {1, 2, 4, 5, 3};		// 先序序列	
				int	in1[] = {4, 2, 5, 1, 3};		// 中序序列 
				int n1 = 5;							// 结点个数
				BinaryTree<int> bt1;				// 二叉树
				bt1 = CreateBinaryTree(pre1, in1, n1);	//建立二叉树
				DisplayBTWithTreeShape(bt1);		// 显示二叉树

				int pre2[] = {2, 3, 5, 4, 1};		// 先序序列	
				int	in2[] = {5, 3, 4, 2, 1};		// 中序序列 
				int n2 = 5;							// 结点个数
				BinaryTree<int> bt2;				// 二叉树
				bt2 = CreateBinaryTree(pre2, in2, n2);	//建立二叉树
				DisplayBTWithTreeShape(bt2);		// 显示二叉树

				int pre3[] = {1, 2, 4, 5, 3};		// 先序序列	
				int	in3[] = {4, 2, 1, 3, 5};		// 中序序列 
				int n3 = 5;							// 结点个数
				BinaryTree<int> bt3;				// 二叉树
				bt3 = CreateBinaryTree(pre3, in3, n3);	//建立二叉树
				DisplayBTWithTreeShape(bt3);		// 显示二叉树

				if (IsSimilar(bt1, bt2)) cout << endl << "bt1和bt2相似" << endl;
				else cout << endl << "bt1和bt2不相似" << endl;

				if (IsSimilar(bt1, bt3)) cout << endl << "bt1和bt3相似" << endl;
				else cout << endl << "bt1和bt3不相似" << endl;
				break;
			}
		case '4':
			{
				int pre[] = {1, 2, 4, 3, 5};		// 先序序列	
				int	in[] = {2, 4, 1, 5, 3};			// 中序序列 
				int n = 5;							// 结点个数
				BinaryTree<int> bt;					// 二叉树
				cout << "原二叉树";
				bt = CreateBinaryTree(pre, in, n);	//建立二叉树
				DisplayBTWithTreeShape(bt);			// 显示二叉树
				SwapBiTree(bt);						// 交换二叉树的所有结点的左右孩子
				cout << "交换左右孩子后的新二叉树";
				DisplayBTWithTreeShape(bt);			// 显示二叉树
				break;
			}
		case '5':
			{
				int post[]={4,5,2,7,8,3,1};		// 后序序列
				int in[]={4,2,5,1,7,3,8};		// 中序序列
				int n = 7;						// 结点个数
				BinaryTree<int> postInbt;
				postInbt = CreateBinaryTree_PostIn(post, in, n);// 构造二叉树
				cout << "后序序列：";DisplaySeq(post, n);cout << endl;								
				cout << "中序序列：";DisplaySeq(in, n);cout << endl;
				cout << "构造的二叉树:" << endl;
				DisplayBTWithTreeShape<int>(postInbt);
				cout << endl;
				break;
			}
		case '6':
			{
				int pre[] = {1, 2, 4, 5, 3, 6, 7};	// 先序序列	
				int	in[] = {4, 2, 5, 1, 6, 3, 7};	// 中序序列
				int post[7];
				int n = 7;							// 结点个数
				PreInToPost(pre, in, post, n);
				cout << "先序序列：";DisplaySeq(pre, n);cout << endl;								
				cout << "中序序列：";DisplaySeq(in, n);cout << endl;
				cout << "后序序列：";DisplaySeq(post, n);cout << endl;
				break;
			}
		}
	}
	return 0;							
}
