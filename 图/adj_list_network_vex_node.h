#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__
#include"lk_list.h"
#include "adj_list_network_edge.h"			// �ڽӱ�����������ģ��

// �ڽӱ�����������ģ��
template <class ElemType, class WeightType>
struct AdjListNetWorkVexNode
{
// ���ݳ�Ա:
	ElemType data;										// ����Ԫ��ֵ
	LinkList<AdjListNetworkEdge<WeightType> > adjLink;	// �ڽӵ�����
};

#endif