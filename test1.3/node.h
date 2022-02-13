#pragma once
#include<iostream>
using namespace std;


// Ω·µ„¿‡ƒ£∞Â
template <class ElemType>
struct Node 
{
//  ˝æ›≥…‘±:
	ElemType data;				//  ˝æ›≥…∑÷
	Node<ElemType> *next;		// ÷∏’Î≥…∑÷

// ππ‘Ï∫Ø ˝ƒ£∞Â:
	Node();						
	Node(const ElemType &e, Node<ElemType> *link = NULL);	// “—÷™ ˝æ›‘™Àÿ÷µ∫Õ÷∏’ÎΩ®¡¢Ω·µ„
};

// Ω·µ„¿‡ƒ£∞Âµƒ µœ÷≤ø∑÷
template<class ElemType>
Node<ElemType>::Node()

{
	next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(const ElemType &e, Node<ElemType> *link)

{
	data = e;
	next = link;
}


