#include <iostream>						
using namespace std;
#define MY_INFINITY 10000
#include "adj_list_dir_network.h"		
#include "alg.h"


template <class ElemType>
void Show(const ElemType &e)
// 操作结果: 显示数据元素
{
    cout << e << "  ";
}
	int main()
{

	char vexs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
	int m[9][9] = {
		{0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 4, 0, 0},
		{0, 0, 0, 3, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 5, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int n = 9;

	AdjListDirNetwork<char, int> net(vexs, n);

	int u;							
	for (u = 0; u < n; u++)
	{	// 生成邻接矩阵的行
		for (int v = 0; v < n; v++)
		{	// 生成邻接矩阵元素的值
			if (m[u][v] != 0) net.InsertEdge(u, v, m[u][v]);
		}
	}

	char select = '0';
	while (select != '4')
	{
		cout << endl << "1. 统计有向网各顶点的度";
		cout << endl << "2. 非递归深度优先遍历";
		cout << endl << "3. 判断给定的两个顶点间是否存在长度为k的简单路径";
		cout << endl << "4. 退出";
		cout << endl << "选择功能(1~4):";
		cin >> select;
		switch (select)
		{
		case '1':
			{
				int *Degree = new int[net.GetVexNum()];	
				StatDegree(net,Degree);
				cout<<"各顶点的度为:"<<endl;
				for(int i = 0; i < n; i++)
				{
					cout << vexs[i] << ":"<<Degree[i]<<endl;
				}
				break;
			}
		case '2':
			{
				cout << "深度优先遍历:";
				net.DFSTraverse(Show);			// 深度优先遍历
				cout << endl;

				cout << "非递归深度优先遍历:";
				net.NonRecurDFSTraverse(Show);	// 非递归深度优先遍历
				cout << endl;
				break;
			}
		case '3':
			{
				net.ExistPathLen(0, 7, 15);
				break;
			}

		}
	}

	return 0;							
}