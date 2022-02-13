#include "adj_list_dir_network.h"
template <class ElemType, class WeightType>
void StatDegree(const AdjListDirNetwork<ElemType, WeightType> &g, int *Degree)
// 操作结果：统计网g各顶点的度
{
	for (int i = 0; i < g.GetVexNum(); i++)
    {
    Degree[i] = 0;
    }
    for(int i=0;i<g.GetVexNum();i++)
	{
		int t=0;
		for(int j=g.FirstAdjVex(i);j>=0;j=g.NextAdjVex(i,j))
		{
            t++;//计算出度
			Degree[j]=Degree[j]+1;//计算入度，j为i指向的节点，计算j即为入度
		}
		Degree[i]+=t;
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::NonRecurDFS(int v, void (*visit)(const ElemType &e)) const
// 操作结果：从顶点v出发进行非递归深度优先搜索网
{
	SetTag(v,true);
	ElemType e;
	GetElem(v,e);
	(*visit)(e);
	LinkStack<int> ls;
	ls.Push(v);
	while(!ls.Empty())
	{
		int u,w;
		ls.Pop(u);//回溯最近的节点，然后遍历其它未访问的节点。
		for(w=FirstAdjVex(u);w>=0;w=FirstAdjVex(w))//与广度优先遍历不同，一直访问第一个节点。
		{
			if(!GetTag(w))
			{
				SetTag(w,true);
				GetElem(w,e);
				(*visit)(e);
				ls.Push(w);
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::NonRecurDFSTraverse(void (*visit)(const ElemType &e)) const
// 操作结果：对网进行深度优先遍历
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	
		if (!GetTag(v))	NonRecurDFS(v, visit);
	}
}

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::ExistPathLenHelp(int i, int j, int k)
// 操作结果:判断给定的两个顶点间是否存在长度为k的简单路径，若存在返回true，不存在返回false
{//迭代,简单路径没有环，需要tag,对于另一条路径符合的情况回溯
    if(GetWeight(i,j)==k&&k!=0)//结束
	return true;
	if(k<0)//路径小于0直接结束
	return false;
	SetTag(i,true);//已访问
	for(int a=FirstAdjVex(i);a>=0;a=NextAdjVex(i,a))//NextAdjVex代表如果第一个邻接点不行就换下一个邻接点
	{
		if(!GetTag(a))
		{
			if(ExistPathLenHelp(a,j,k-GetWeight(i,a)))//存在返回true，不存在就换一个邻接点，并把点重新设置为false
			return true;
			else
			SetTag(a,false);
		}
	}
	return false;
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::ExistPathLen(int i, int j, int k)
// 操作结果:判断给定的两个顶点间是否存在长度为k的简单路径
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	
		SetTag(v, false);
	}

	if(ExistPathLenHelp(i, j, k))
	{
		cout<<i<<"号结点与"<<j<<"号结点间【存在】长度为"<<k<<"的简单路径:"<<endl;
	}
	else
	{
		cout<<i<<"号结点与"<<j<<"号结点间【不存在】长度为"<<k<<"的简单路径:"<<endl;
	}
	cout<<endl;
}