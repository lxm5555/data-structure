#include <iostream>						
using namespace std;					
#include "binary_sort_tree.h"			
#include "lk_list.h"					
#include "lk_stack.h"
#include "alg.h"						

template <class ElemType>
void Show(const ElemType &e)
// 操作结果: 显示数据元素
{
    cout << e << " ";
}

template<class ElemType>
void ShowArray(ElemType elem[], int n)
// 操作结果: 显示数组elem的各数据元素值
{
	for (int i = 0; i < n; i++)
	{	// 显示数组elem
		cout << elem[i] << "  ";
	}
	cout << endl; 
}


int main()								
{
	char select = '0';
	while (select != '4')
	{
		cout << endl << "1. 从大到小输出二叉排序树中所有的关键字值不小于key的元素值";
		cout << endl << "2. 判断二叉排序树是否为平衡二叉树";
		cout << endl << "3. 以单链表为存储结构实现直接插入排序(只移动指针)";
		cout << endl << "4. 退出";
		cout << endl << "选择功能(1~4):";
		cin >> select;
		switch (select)
		{
		case '1':
			{
				const int n = 7;					
				int e[n] = {45, 24, 53, 45, 12, 24, 90};	
				int key = 22;						
				BinarySortTree<int, int> t;			// 二叉排序树
				for (int i = 0; i < n; i++)
					t.Insert(e[i]);
				cout << "二叉排序树为:";
				DisplayBTWithTreeShape(t);			// 显示二叉排序树
				cout << endl << "InOrder(t, 22):";
				InOrder(t, key);					// 从大到小输出二叉排序树中所有的关键字值不小于key的元素值
				cout << endl;						
				break;
			}
		case '2':
			{
				const int n = 7;					
				int e[n] = {45, 24, 53, 45, 12, 24, 90};	
				BinarySortTree<int, int> t;			// 二叉排序树
				for (int i = 0; i < n; i++)
					t.Insert(e[i]);
				cout << "二叉排序树:";
				DisplayBTWithTreeShape(t);			// 显示二叉排序树
				if (IsBBT(t)) cout << endl << "是平衡二叉树" << endl;
				else cout << endl << "不是平衡二叉树" << endl;
				break;
			}
		case '3':
			{
				const int n = 7;							
				int  e[n] = {45, 23, 53, 91, 89, 90, 56};	
				LinkList<int> la;							// 线性链表

				for (int i = 0; i< n; i++)
					la.Insert(la.Length() + 1, e[i]);		// 建立线性链表
				cout<<"排序前:";
				la.Traverse(Show);							// 显示la
				cout<<endl;
				InsertSort(la);								// 排序
				cout<<"排序后:";
				la.Traverse(Show);							// 显示la
				cout<<endl;
				break;
			}
		}
	}
	return 0;							
}

