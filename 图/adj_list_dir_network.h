#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"								// 线性链表
#include "adj_list_network_edge.h"					// 邻接表有向网边数据类模板
#include "adj_list_network_vex_node.h"				// 邻接表有向网顶点结点
#include "lk_queue.h"								// 链队列
#include "lk_stack.h"

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 10000							// 缺省大小
#endif

// 有向网的邻接表类模板
template <class ElemType, class WeightType>
class AdjListDirNetwork
{
protected:
// 数据成员:
	int vexNum, edgeNum;							// 顶点个数和边数
	AdjListNetWorkVexNode<ElemType, WeightType> *vexTable;		// 顶点表
	mutable bool *tag;								// 顶点标志				

// 辅助函数模板:
	int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > &lkList, int v) const;	// 定位顶点v在邻接链表中的位置
	void DFS(int v, void (*visit)(const ElemType &e)) const;	// 从顶点v出发进行深度优先搜索网
	void BFS(int v, void (*visit)(const ElemType &)) const;		// 从第顶点v出发进行广度优先搜索网

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListDirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE);
		// 构造顶点数据为es[]，顶点个数为vertexNum，边数为0的有向网
	virtual ~AdjListDirNetwork();					// 析构函数模板
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// 对网进行深度优先遍历
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// 对网进行广度优先遍历
	bool GetElem(int v, ElemType &e) const;			// 用e返回顶点v的元素值	
	bool SetElem(int v, const ElemType &e);			// 设置顶点v的元素值为e
	int GetVexNum() const;							// 返回顶点个数			 
	int GetEdgeNum() const;							// 返回边数个数			 
	int FirstAdjVex(int v) const;					// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;			// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2, WeightType w);	// 插入顶点为v1和v2,权为w的边			 
	void DeleteEdge(int v1, int v2);				// 删除顶点为v1和v2的边			 
	WeightType GetWeight(int v1, int v2) const;		// 返回顶点为v1和v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);	// 设置顶点为v1和v2的边的权值
	bool GetTag(int v) const;						// 返回顶点v的标志		 
	void SetTag(int v, bool val) const;				// 设置顶点v的标志为val		 
	AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &source);	// 复制构造函数模板
	AdjListDirNetwork<ElemType, WeightType> &operator =
		(const AdjListDirNetwork<ElemType, WeightType> &source);				// 重载赋值运算符

	void NonRecurDFS(int v, void (*visit)(const ElemType &e)) const;
	void NonRecurDFSTraverse(void (*visit)(const ElemType &e)) const;
	bool ExistPathLenHelp(int i, int j, int k);
	void ExistPathLen(int i, int j, int k);
};

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net);				// 显示邻接矩阵有向网

// 有向网的邻接表类模板的实现部分
template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
// 初始条件：存在网
// 操作结果：从顶点v出发进行深度优先搜索网
{	
	SetTag(v, true);								// 设置访问标志
	ElemType e;										// 临时变量
	GetElem(v, e);									// 取顶点v的数据元素
	(*visit)(e);									// 访问顶点v的数据元素
	for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
	{	// 对v的尚未访问过的邻接顶点w递归调用DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
// 初始条件：存在网
// 操作结果：对网进行深度优先遍历
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// 对每个顶点设置访问标志
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// 对尚未访问的顶点按DFS进行深度优先搜索
		if (!GetTag(v))	DFS(v, visit);
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
// 初始条件：存在网
// 操作结果：从第顶点v出发进行广度优先搜索网
{	
	SetTag(v, true);								// 设置访问标志
	ElemType e;										// 临时变量
	GetElem(v, e);									// 取顶点v的数据元素
	(*visit)(e);									// 访问顶点v的数据元素
	LinkQueue<int> q;								// 定义队列
	q.InQueue(v);									// v入队
	while (!q.Empty())
	{	// 队列q非空, 进行循环
		int u, w;									// 临时顶点
		q.OutQueue(u);								// 出队
		for (w = FirstAdjVex(u); w >= 0; w = NextAdjVex(u, w))
		{	// 对u尚未访问过的邻接顶点w进行访问
			if (!GetTag(w))
			{	// 对w进行访问
				SetTag(w, true);					// 设置访问标志
				GetElem(w, e);						// 顶点w的数据元素
				(*visit)(e);						// 取访问顶点w的数据元素
				q.InQueue(w);						// w入队
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
// 初始条件：存在网
// 操作结果：对网进行广度优先遍历
{
	int v;											// 工作变量
	for (v = 0; v < GetVexNum(); v++)
	{	// 对每个顶点设置访问标志
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// 对尚未访问的顶点按BFS进行深度优先搜索
		if (!GetTag(v)) BFS(v , visit); 
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(ElemType es[], int vertexNum)
// 操作结果：构造顶点数据为es[]，顶点个数为vertexNum，边数为0的有向网
{
	if (vertexNum < 0)
	{	// 出现异常
		cout << "顶点个数不能为负!" << endl;		// 提示信息
		exit(1);									// 退出程序
	}

	vexNum = vertexNum;								// 顶点数为vertexNum
	edgeNum = 0;									// 边数为0

	tag = new bool[vexNum];							// 生成标志数组
	int temPos;										// 临时变量 
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// 初始化标志数组
		tag[temPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// 初始化顶点数据
		vexTable[temPos].data = es[temPos];
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::~AdjListDirNetwork()
// 操作结果：释放邻接表有向网所占用空间
{
	delete []tag;									// 释放标志
	delete []vexTable;								// 释放邻接表
}

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// 操作结果：用e返回顶点v的元素值, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;								// 元素不存在
	}
	else
	{	// v合法
		e = vexTable[v].data;						// 将顶点v的元素值赋给e
		return true;								// 元素存在
	}
}	

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点v的元素值为e，v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;								// 位置错
	}
	else
	{	// v合法
		vexTable[v].data = e;						// 顶点元素
		return true;								// 成功
	}
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum)
	{	// 出现异常
		cout << "v不合法!" << endl;					// 提示信息
		exit(2);									// 退出程序
	}

	if (vexTable[v].adjLink.Empty())
	{	// 空邻接链表，无邻接点
		return -1; 
	}
	else
	{	// 空邻接链表，存在邻接点
		AdjListNetworkEdge<WeightType> temEdgeNode;	// 临时变量
		vexTable[v].adjLink.GetElem(1, temEdgeNode);// 取出顶点v的第一个邻接点	
		return temEdgeNode.adjVex;					// 返回顶点v的第一个邻接点
	}
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > &lkList, int v) const
// 操作结果：定位顶点v在邻接链表中的位置
{
	AdjListNetworkEdge<WeightType> temEdgeNode;		// 临时变量
	int curPos;										// 工作变量

	for (curPos = 1; curPos <= lkList.Length(); curPos++)
	{	// 循环定定
		lkList.GetElem(curPos, temEdgeNode);		// 取得边信息
		if (temEdgeNode.adjVex == v) break;			// 定位成功
	}
	
	return curPos;									// curPos = lkList.Length() + 1 表示定位失败
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// 出现异常
		cout << "v1不合法!" << endl;				// 提示信息
		exit(3);									// 退出程序
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// 出现异常
		cout << "v2不合法!" << endl;				// 提示信息
		exit(4);									// 退出程序
	}
	if (v1 == v2)
	{	// 出现异常
		cout << "v1不能等于v2!" << endl;			// 提示信息
		exit(5);									// 退出程序
	}
	
	int temPos = IndexHelp(vexTable[v1].adjLink, v2);			// 取出v2在邻接链表中的位置
	if (temPos < vexTable[v1].adjLink.Length())
	{	// 存在下一个邻接点
		AdjListNetworkEdge<WeightType> temEdgeNode;	// 临时变量
		vexTable[v1].adjLink.GetElem(temPos + 1, temEdgeNode);	// 取出后继
		return temEdgeNode.adjVex;					// 返回下一个邻接点
	}
	else
	{	// 不存在下一个邻接点
		return -1;
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// 出现异常
		cout << "v1不合法!" << endl;				// 提示信息
		exit(6);									// 退出程序
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// 出现异常
		cout << "v2不合法!" << endl;				// 提示信息
		exit(7);									// 退出程序
	}
	if (v1 == v2)
	{	// 出现异常
		cout << "v1不能等于v2!" << endl;			// 提示信息
		exit(8);									// 退出程序
	}
	if (w == 0)
	{	// 出现异常
		cout << "w不能为0!" << endl;				// 提示信息
		exit(9);									// 退出程序
	}

	AdjListNetworkEdge<WeightType> temEdgeNode;		// 临时变量
	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// 取出边
		temEdgeNode.weight = w;								// 设设置权值
		vexTable[v1].adjLink.SetElem(temPos, temEdgeNode);	// 设置边
	}
	else
	{	// 不存在边<v1, v2>
		temEdgeNode.adjVex = v2; temEdgeNode.weight = w;	// 定义边
		vexTable[v1].adjLink.Insert(temPos, temEdgeNode);	// 插入边<v1, v2>
		edgeNum++;									// 边数自增1
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// 出现异常
		cout << "v1不合法!" << endl;				// 提示信息
		exit(10);									// 退出程序
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// 出现异常
		cout << "v2不合法!" << endl;				// 提示信息
		exit(11);									// 退出程序
	}
	if (v1 == v2)
	{	// 出现异常
		cout << "v1不能等于v2!" << endl;			// 提示信息
		exit(12);									// 退出程序
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// 存在边<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;			// 临时变量
		vexTable[v1].adjLink.Delete(temPos, temEdgeNode);	// 删除边<v1, v2>
 		edgeNum--;									// 边数自减1
	}
}

template <class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
	{	// 出现异常
		cout << "v1不合法!" << endl;				// 提示信息
		exit(13);									// 退出程序
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// 出现异常
		cout << "v2不合法!" << endl;				// 提示信息
		exit(14);									// 退出程序
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// 存在边<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;			// 临时变量
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// 取出边
		return temEdgeNode.weight;					// 返回权值
	}
	else
	{	// 不存在边<v1, v2>
		return 0;									// 权值为0表示边不存在
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
	{	// 出现异常
		cout << "v1不合法!" << endl;				// 提示信息
		exit(15);									// 退出程序
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// 出现异常
		cout << "v2不合法!" << endl;				// 提示信息
		exit(16);									// 退出程序
	}
	if (v1 == v2)
	{	// 出现异常
		cout << "v1不能等于v2!" << endl;			// 提示信息
		exit(17);									// 退出程序
	}
	if (w == 0)
	{	// 出现异常
		cout << "w不能为0!" << endl;				// 提示信息
		exit(18);									// 退出程序
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// 存在边<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;	// 临时变量
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// 取出边
		temEdgeNode.weight = w;						// 修改权值
		vexTable[v1].adjLink.SetElem(temPos, temEdgeNode);	// 设置边
	}
}

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
	{	// 出现异常
		cout << "v不合法!" << endl;					// 提示信息
		exit(19);									// 退出程序
	}

	return tag[v];									// 返回顶点v的标志
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
	{	// 出现异常
		cout << "v不合法!" << endl;					// 提示信息
		exit(20);									// 退出程序
	}

	tag[v] = val;									// 设置顶点v的标志为val
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &source)
// 操作结果：由有向网的邻接矩阵source构造新有向网的邻接矩阵source——复制构造函数模板
{
	int temPos;										// 临时变量
	vexNum = source.vexNum;							// 复制顶点数
	edgeNum = source.edgeNum;						// 复制边数

	tag = new bool[vexNum];							// 生成标志数组
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// 复制标志数组
		tag[temPos] = source.tag[temPos];
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];	// 生成邻接表
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// 复制邻接链表
		vexTable[temPos].data = source.vexTable[temPos].data;			// 复制顶点数据
		vexTable[temPos].adjLink = source.vexTable[temPos].adjLink;		// 复制邻接链表	
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType> &AdjListDirNetwork<ElemType, WeightType>::operator =(const AdjListDirNetwork<ElemType, WeightType> &source)
// 操作结果：将有向网的邻接矩阵source赋值给当前有向网的邻接矩阵——重载赋值运算符
{
	if (&source != this)
	{
		int temPos;									// 临时变量

		delete []tag;								// 释放标志
		delete []vexTable;							// 释放邻接表

		vexNum = source.vexNum;						// 复制顶点数
		edgeNum = source.edgeNum;					// 复制边数

		tag = new bool[vexNum];						// 生成标志数组
		for (temPos = 0; temPos < vexNum; temPos++)
		{	// 复制标志数组
			tag[temPos] = source.tag[temPos];
		}

		vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];	// 生成邻接表
		for (temPos = 0; temPos < vexNum; temPos++)
		{	// 复制邻接链表
			vexTable[temPos].data = source.vexTable[temPos].data;			// 复制顶点数据
			vexTable[temPos].adjLink = source.vexTable[temPos].adjLink;		// 复制邻接链表	
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net)
// 操作结果: 显示邻接矩阵有向网
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 显示第v个邻接链表
		cout << endl << v << "  ";					// 显示顶点号
		ElemType e;									// 数据元素
		net.GetElem(v, e);							// 取出元素值
		cout << e << "  ";							// 显示顶点元素

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// 显示第v个邻接链表的一个结点（表示一个邻接点）
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")";		// 显示邻接点信息
		}
		cout << endl;								// 换行
	}
}

#endif
