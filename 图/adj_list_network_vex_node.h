#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__
#include"lk_list.h"
#include "adj_list_network_edge.h"			// 邻接表网边数据类模板

// 邻接表网顶点结点类模板
template <class ElemType, class WeightType>
struct AdjListNetWorkVexNode
{
// 数据成员:
	ElemType data;										// 数据元素值
	LinkList<AdjListNetworkEdge<WeightType> > adjLink;	// 邻接点链表
};

#endif