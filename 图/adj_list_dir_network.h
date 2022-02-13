#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"								// ��������
#include "adj_list_network_edge.h"					// �ڽӱ���������������ģ��
#include "adj_list_network_vex_node.h"				// �ڽӱ�������������
#include "lk_queue.h"								// ������
#include "lk_stack.h"

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 10000							// ȱʡ��С
#endif

// ���������ڽӱ���ģ��
template <class ElemType, class WeightType>
class AdjListDirNetwork
{
protected:
// ���ݳ�Ա:
	int vexNum, edgeNum;							// ��������ͱ���
	AdjListNetWorkVexNode<ElemType, WeightType> *vexTable;		// �����
	mutable bool *tag;								// �����־				

// ��������ģ��:
	int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > &lkList, int v) const;	// ��λ����v���ڽ������е�λ��
	void DFS(int v, void (*visit)(const ElemType &e)) const;	// �Ӷ���v���������������������
	void BFS(int v, void (*visit)(const ElemType &)) const;		// �ӵڶ���v�������й������������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjListDirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE);
		// ���춥������Ϊes[]���������ΪvertexNum������Ϊ0��������
	virtual ~AdjListDirNetwork();					// ��������ģ��
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// ��������������ȱ���
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// �������й�����ȱ���
	bool GetElem(int v, ElemType &e) const;			// ��e���ض���v��Ԫ��ֵ	
	bool SetElem(int v, const ElemType &e);			// ���ö���v��Ԫ��ֵΪe
	int GetVexNum() const;							// ���ض������			 
	int GetEdgeNum() const;							// ���ر�������			 
	int FirstAdjVex(int v) const;					// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;			// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2, WeightType w);	// ���붥��Ϊv1��v2,ȨΪw�ı�			 
	void DeleteEdge(int v1, int v2);				// ɾ������Ϊv1��v2�ı�			 
	WeightType GetWeight(int v1, int v2) const;		// ���ض���Ϊv1��v2�ıߵ�Ȩֵ
	void SetWeight(int v1, int v2, WeightType w);	// ���ö���Ϊv1��v2�ıߵ�Ȩֵ
	bool GetTag(int v) const;						// ���ض���v�ı�־		 
	void SetTag(int v, bool val) const;				// ���ö���v�ı�־Ϊval		 
	AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &source);	// ���ƹ��캯��ģ��
	AdjListDirNetwork<ElemType, WeightType> &operator =
		(const AdjListDirNetwork<ElemType, WeightType> &source);				// ���ظ�ֵ�����

	void NonRecurDFS(int v, void (*visit)(const ElemType &e)) const;
	void NonRecurDFSTraverse(void (*visit)(const ElemType &e)) const;
	bool ExistPathLenHelp(int i, int j, int k);
	void ExistPathLen(int i, int j, int k);
};

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net);				// ��ʾ�ڽӾ���������

// ���������ڽӱ���ģ���ʵ�ֲ���
template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
// ��ʼ������������
// ����������Ӷ���v���������������������
{	
	SetTag(v, true);								// ���÷��ʱ�־
	ElemType e;										// ��ʱ����
	GetElem(v, e);									// ȡ����v������Ԫ��
	(*visit)(e);									// ���ʶ���v������Ԫ��
	for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
// ��ʼ������������
// �����������������������ȱ���
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// ��ÿ���������÷��ʱ�־
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴DFS���������������
		if (!GetTag(v))	DFS(v, visit);
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
// ��ʼ������������
// ����������ӵڶ���v�������й������������
{	
	SetTag(v, true);								// ���÷��ʱ�־
	ElemType e;										// ��ʱ����
	GetElem(v, e);									// ȡ����v������Ԫ��
	(*visit)(e);									// ���ʶ���v������Ԫ��
	LinkQueue<int> q;								// �������
	q.InQueue(v);									// v���
	while (!q.Empty())
	{	// ����q�ǿ�, ����ѭ��
		int u, w;									// ��ʱ����
		q.OutQueue(u);								// ����
		for (w = FirstAdjVex(u); w >= 0; w = NextAdjVex(u, w))
		{	// ��u��δ���ʹ����ڽӶ���w���з���
			if (!GetTag(w))
			{	// ��w���з���
				SetTag(w, true);					// ���÷��ʱ�־
				GetElem(w, e);						// ����w������Ԫ��
				(*visit)(e);						// ȡ���ʶ���w������Ԫ��
				q.InQueue(w);						// w���
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
// ��ʼ������������
// ����������������й�����ȱ���
{
	int v;											// ��������
	for (v = 0; v < GetVexNum(); v++)
	{	// ��ÿ���������÷��ʱ�־
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴BFS���������������
		if (!GetTag(v)) BFS(v , visit); 
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(ElemType es[], int vertexNum)
// ������������춥������Ϊes[]���������ΪvertexNum������Ϊ0��������
{
	if (vertexNum < 0)
	{	// �����쳣
		cout << "�����������Ϊ��!" << endl;		// ��ʾ��Ϣ
		exit(1);									// �˳�����
	}

	vexNum = vertexNum;								// ������ΪvertexNum
	edgeNum = 0;									// ����Ϊ0

	tag = new bool[vexNum];							// ���ɱ�־����
	int temPos;										// ��ʱ���� 
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// ��ʼ����־����
		tag[temPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// �����ڽӱ�
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// ��ʼ����������
		vexTable[temPos].data = es[temPos];
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::~AdjListDirNetwork()
// ����������ͷ��ڽӱ���������ռ�ÿռ�
{
	delete []tag;									// �ͷű�־
	delete []vexTable;								// �ͷ��ڽӱ�
}

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// �����������e���ض���v��Ԫ��ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;								// Ԫ�ز�����
	}
	else
	{	// v�Ϸ�
		e = vexTable[v].data;						// ������v��Ԫ��ֵ����e
		return true;								// Ԫ�ش���
	}
}	

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// ������������ö���v��Ԫ��ֵΪe��v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;								// λ�ô�
	}
	else
	{	// v�Ϸ�
		vexTable[v].data = e;						// ����Ԫ��
		return true;								// �ɹ�
	}
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�			 
{
	if (v < 0 || v >= vexNum)
	{	// �����쳣
		cout << "v���Ϸ�!" << endl;					// ��ʾ��Ϣ
		exit(2);									// �˳�����
	}

	if (vexTable[v].adjLink.Empty())
	{	// ���ڽ��������ڽӵ�
		return -1; 
	}
	else
	{	// ���ڽ����������ڽӵ�
		AdjListNetworkEdge<WeightType> temEdgeNode;	// ��ʱ����
		vexTable[v].adjLink.GetElem(1, temEdgeNode);// ȡ������v�ĵ�һ���ڽӵ�	
		return temEdgeNode.adjVex;					// ���ض���v�ĵ�һ���ڽӵ�
	}
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > &lkList, int v) const
// �����������λ����v���ڽ������е�λ��
{
	AdjListNetworkEdge<WeightType> temEdgeNode;		// ��ʱ����
	int curPos;										// ��������

	for (curPos = 1; curPos <= lkList.Length(); curPos++)
	{	// ѭ������
		lkList.GetElem(curPos, temEdgeNode);		// ȡ�ñ���Ϣ
		if (temEdgeNode.adjVex == v) break;			// ��λ�ɹ�
	}
	
	return curPos;									// curPos = lkList.Length() + 1 ��ʾ��λʧ��
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// �����쳣
		cout << "v1���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(3);									// �˳�����
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// �����쳣
		cout << "v2���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(4);									// �˳�����
	}
	if (v1 == v2)
	{	// �����쳣
		cout << "v1���ܵ���v2!" << endl;			// ��ʾ��Ϣ
		exit(5);									// �˳�����
	}
	
	int temPos = IndexHelp(vexTable[v1].adjLink, v2);			// ȡ��v2���ڽ������е�λ��
	if (temPos < vexTable[v1].adjLink.Length())
	{	// ������һ���ڽӵ�
		AdjListNetworkEdge<WeightType> temEdgeNode;	// ��ʱ����
		vexTable[v1].adjLink.GetElem(temPos + 1, temEdgeNode);	// ȡ�����
		return temEdgeNode.adjVex;					// ������һ���ڽӵ�
	}
	else
	{	// ��������һ���ڽӵ�
		return -1;
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// �����쳣
		cout << "v1���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(6);									// �˳�����
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// �����쳣
		cout << "v2���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(7);									// �˳�����
	}
	if (v1 == v2)
	{	// �����쳣
		cout << "v1���ܵ���v2!" << endl;			// ��ʾ��Ϣ
		exit(8);									// �˳�����
	}
	if (w == 0)
	{	// �����쳣
		cout << "w����Ϊ0!" << endl;				// ��ʾ��Ϣ
		exit(9);									// �˳�����
	}

	AdjListNetworkEdge<WeightType> temEdgeNode;		// ��ʱ����
	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// ȡ����
		temEdgeNode.weight = w;								// ������Ȩֵ
		vexTable[v1].adjLink.SetElem(temPos, temEdgeNode);	// ���ñ�
	}
	else
	{	// �����ڱ�<v1, v2>
		temEdgeNode.adjVex = v2; temEdgeNode.weight = w;	// �����
		vexTable[v1].adjLink.Insert(temPos, temEdgeNode);	// �����<v1, v2>
		edgeNum++;									// ��������1
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
	{	// �����쳣
		cout << "v1���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(10);									// �˳�����
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// �����쳣
		cout << "v2���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(11);									// �˳�����
	}
	if (v1 == v2)
	{	// �����쳣
		cout << "v1���ܵ���v2!" << endl;			// ��ʾ��Ϣ
		exit(12);									// �˳�����
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// ���ڱ�<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;			// ��ʱ����
		vexTable[v1].adjLink.Delete(temPos, temEdgeNode);	// ɾ����<v1, v2>
 		edgeNum--;									// �����Լ�1
	}
}

template <class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum)
	{	// �����쳣
		cout << "v1���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(13);									// �˳�����
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// �����쳣
		cout << "v2���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(14);									// �˳�����
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// ���ڱ�<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;			// ��ʱ����
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// ȡ����
		return temEdgeNode.weight;					// ����Ȩֵ
	}
	else
	{	// �����ڱ�<v1, v2>
		return 0;									// ȨֵΪ0��ʾ�߲�����
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum)
	{	// �����쳣
		cout << "v1���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(15);									// �˳�����
	}
	if (v2 < 0 || v2 >= vexNum)
	{	// �����쳣
		cout << "v2���Ϸ�!" << endl;				// ��ʾ��Ϣ
		exit(16);									// �˳�����
	}
	if (v1 == v2)
	{	// �����쳣
		cout << "v1���ܵ���v2!" << endl;			// ��ʾ��Ϣ
		exit(17);									// �˳�����
	}
	if (w == 0)
	{	// �����쳣
		cout << "w����Ϊ0!" << endl;				// ��ʾ��Ϣ
		exit(18);									// �˳�����
	}

	int temPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (temPos <= vexTable[v1].adjLink.Length())
	{	// ���ڱ�<v1, v2>
		AdjListNetworkEdge<WeightType> temEdgeNode;	// ��ʱ����
		vexTable[v1].adjLink.GetElem(temPos, temEdgeNode);	// ȡ����
		temEdgeNode.weight = w;						// �޸�Ȩֵ
		vexTable[v1].adjLink.SetElem(temPos, temEdgeNode);	// ���ñ�
	}
}

template <class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum)
	{	// �����쳣
		cout << "v���Ϸ�!" << endl;					// ��ʾ��Ϣ
		exit(19);									// �˳�����
	}

	return tag[v];									// ���ض���v�ı�־
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum)
	{	// �����쳣
		cout << "v���Ϸ�!" << endl;					// ��ʾ��Ϣ
		exit(20);									// �˳�����
	}

	tag[v] = val;									// ���ö���v�ı�־Ϊval
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &source)
// ��������������������ڽӾ���source���������������ڽӾ���source�������ƹ��캯��ģ��
{
	int temPos;										// ��ʱ����
	vexNum = source.vexNum;							// ���ƶ�����
	edgeNum = source.edgeNum;						// ���Ʊ���

	tag = new bool[vexNum];							// ���ɱ�־����
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// ���Ʊ�־����
		tag[temPos] = source.tag[temPos];
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];	// �����ڽӱ�
	for (temPos = 0; temPos < vexNum; temPos++)
	{	// �����ڽ�����
		vexTable[temPos].data = source.vexTable[temPos].data;			// ���ƶ�������
		vexTable[temPos].adjLink = source.vexTable[temPos].adjLink;		// �����ڽ�����	
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType> &AdjListDirNetwork<ElemType, WeightType>::operator =(const AdjListDirNetwork<ElemType, WeightType> &source)
// ��������������������ڽӾ���source��ֵ����ǰ���������ڽӾ��󡪡����ظ�ֵ�����
{
	if (&source != this)
	{
		int temPos;									// ��ʱ����

		delete []tag;								// �ͷű�־
		delete []vexTable;							// �ͷ��ڽӱ�

		vexNum = source.vexNum;						// ���ƶ�����
		edgeNum = source.edgeNum;					// ���Ʊ���

		tag = new bool[vexNum];						// ���ɱ�־����
		for (temPos = 0; temPos < vexNum; temPos++)
		{	// ���Ʊ�־����
			tag[temPos] = source.tag[temPos];
		}

		vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];	// �����ڽӱ�
		for (temPos = 0; temPos < vexNum; temPos++)
		{	// �����ڽ�����
			vexTable[temPos].data = source.vexTable[temPos].data;			// ���ƶ�������
			vexTable[temPos].adjLink = source.vexTable[temPos].adjLink;		// �����ڽ�����	
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net)
// �������: ��ʾ�ڽӾ���������
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";					// ��ʾ�����
		ElemType e;									// ����Ԫ��
		net.GetElem(v, e);							// ȡ��Ԫ��ֵ
		cout << e << "  ";							// ��ʾ����Ԫ��

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")";		// ��ʾ�ڽӵ���Ϣ
		}
		cout << endl;								// ����
	}
}

#endif
