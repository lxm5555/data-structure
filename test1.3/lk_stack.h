#pragma once
#include<iostream>
using namespace std;
#include "node.h"														// Ω·µ„¿‡ƒ£∞Â

// ¡¥’ª¿‡ƒ£∞Â
template<class ElemType>
class LinkStack //链式栈
{
protected:
//  ˝æ›≥…‘±:
	Node<ElemType> *top;												// ’ª∂•÷∏’Î
	int count;															// ‘™Àÿ∏ˆ ˝

public:
// ≥ÈœÛ ˝æ›¿‡–Õ∑Ω∑®…˘√˜º∞÷ÿ‘ÿ±‡“ÎœµÕ≥ƒ¨»œ∑Ω∑®…˘√˜:
	LinkStack();														
	virtual ~LinkStack();												
	int Length() const;													// «Û’ª≥§∂»			 
	bool Empty() const;													// ≈–∂œ’ª «∑ÒŒ™ø’
	void Clear();														// Ω´’ª«Âø’
	void Traverse(void (*visit)(const ElemType &)) const ;				// ±È¿˙’ª
	bool Push(const ElemType &e);										// »Î’ª
	bool Top(ElemType &e) const;										
	bool Pop(ElemType &e);												// ≥ˆ’ª
	bool Pop();															// ≥ˆ’ª
	LinkStack(const LinkStack<ElemType> &source);						// ∏¥÷∆ππ‘Ï∫Ø ˝ƒ£∞Â
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &source);	// ÷ÿ‘ÿ∏≥÷µ‘ÀÀ„∑˚
};


// ¡¥’ª¿‡ƒ£∞Âµƒ µœ÷≤ø∑÷

template<class ElemType>
LinkStack<ElemType>::LinkStack()
// ≤Ÿ◊˜Ω·π˚£∫ππ‘Ï“ª∏ˆø’’ª±Ì
{
	top = NULL;															// ππ‘Ï’ª∂•÷∏’Î
	count = 0;															// ≥ı ºªØ‘™Àÿ∏ˆ ˝
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
{
	Clear();															// «Âø’’ª
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
{
	return count;														// count±Ì æ’ª‘™Àÿ∏ˆ ˝
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
{
	return count == 0;													
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// ≤Ÿ◊˜Ω·π˚£∫«Âø’’ª
{
	while (!Empty())
	{	// ±Ì’ª∑«ø’£¨‘Ú≥ˆ’ª
		Pop();															// ≥ˆ’ª
	}
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ≤Ÿ◊˜Ω·π˚£∫¥”’ªµ◊µΩ’ª∂•“¿¥Œ∂‘’ªµƒ√ø∏ˆ‘™Àÿµ˜”√∫Ø ˝(*visit)
{
	Node<ElemType> *temPtr;												// ¡Ÿ ±÷∏’Î±‰¡ø
	LinkStack<ElemType> temS;											// ¡Ÿ ±’ª,temS÷–‘™ÀÿÀ≥–Ú”Îµ±«∞’ª‘™ÀÿÀ≥–Úœ‡∑¥
	for (temPtr = top; temPtr != NULL; temPtr = temPtr->next)
	{	// ”√temPtr“¿¥Œ÷∏œÚµ±«∞’ªµƒ√ø∏ˆ‘™Àÿ
		temS.Push(temPtr->data);										
	}
	
	for (temPtr = temS.top; temPtr != NULL; temPtr = temPtr->next)
	{	
		(*visit)(temPtr->data);											
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Push(const ElemType &e)
{
	Node<ElemType> *newTop = new Node<ElemType>(e, top);
	if (newTop == NULL) 
	{	// ∂ØÃ¨ƒ⁄¥Ê∫ƒæ°
		return false;													//  ß∞‹
	}
	else
	{	// ≤Ÿ◊˜≥…π¶
		top = newTop;
		count++;														// »Î’ª≥…π¶∫Û‘™Àÿ∏ˆ ˝º”1 
		return true;													// ≥…π¶
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Top(ElemType &e) const
{
	if(Empty())
	{	// ’ªø’
		return false;													//  ß∞‹
	}
	else
	{	// ’ª∑«ø’,≤Ÿ◊˜≥…π¶
		e = top->data;													
		return true;													// ≥…π¶
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Pop(ElemType &e)
{
	if (Empty())
	{	
		return false;													//  ß∞‹
	}
	else
	{	// ≤Ÿ◊˜≥…π¶
		Node<ElemType> *oldTop = top;									// æ…’ª∂•
		e = oldTop->data;											
		top = oldTop->next;												// top÷∏œÚ–¬’ª∂•
		delete oldTop;													// …æ≥˝æ…’ª∂•
		count--;														// ≥ˆ’ª≥…π¶∫Û‘™Àÿ∏ˆ ˝◊‘ºı1
		return true;													// π¶ƒ‹
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Pop()
{
	if (Empty())
	{	// ’ªø’
		return false;													//  ß∞‹
	}
	else
	{	// ≤Ÿ◊˜≥…π¶
		Node<ElemType> *oldTop = top;									// æ…’ª∂•
		top = oldTop->next;												// top÷∏œÚ–¬’ª∂•
		delete oldTop;													// …æ≥˝æ…’ª∂•
		count--;														// ≥ˆ’ª≥…π¶∫Û‘™Àÿ∏ˆ ˝◊‘ºı1
		return true;													// π¶ƒ‹
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &source) 
{
	if (source.Empty())
	{	// sourceŒ™ø’
		top = NULL;														// ππ‘Ï’ª∂•÷∏’Î
		count = 0;														// ≥ı ºªØ‘™Àÿ∏ˆ ˝
	}
	else 
	{	// source∑«ø’,∏¥÷∆’ª
		top = new Node<ElemType>(source.top->data);						// …˙≥…µ±«∞’ªœÓ
		count = source.count;											// ’ª‘™Àÿ∏ˆ ˝
		Node<ElemType> *buttomPtr = top;								// µ±«∞’ªµ◊÷∏’Î
		for (Node<ElemType> *temPtr = source.top->next; temPtr != NULL; temPtr = temPtr->next)
		{	// ”√temPtr“¿¥Œ÷∏œÚ∆‰”‡‘™Àÿ
			buttomPtr->next = new Node<ElemType>(temPtr->data);			// œÚ’ªµ◊◊∑º”‘™Àÿ	
			buttomPtr = buttomPtr->next;								// buttomPtr÷∏œÚ–¬’ªµ◊
		}
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &source)

{
	if (&source != this)
	{
		if (source.Empty())
		{	// sourceŒ™ø’
			top = NULL;													// ππ‘Ï’ª∂•÷∏’Î
			count = 0;													// ≥ı ºªØ‘™Àÿ∏ˆ ˝
		}
		else 
		{	// source∑«ø’,∏¥÷∆’ª
			Clear();													// «Âø’µ±«∞’ª
			top = new Node<ElemType>(source.top->data);					// …˙≥…µ±«∞’ªœÓ
			count = source.count;										// ’ª‘™Àÿ∏ˆ ˝
			Node<ElemType> *buttomPtr = top;							// µ±«∞’ªµ◊÷∏’Î
			for (Node<ElemType> *temPtr = source.top->next; temPtr != NULL; temPtr = temPtr->next)
			{	// ”√temPtr“¿¥Œ÷∏œÚ∆‰”‡‘™Àÿ
				buttomPtr->next = new Node<ElemType>(temPtr->data);		// œÚ’ªµ◊◊∑º”‘™Àÿ	
				buttomPtr = buttomPtr->next;							// buttomPtr÷∏œÚ–¬’ªµ◊
			}
		}
	}
	return *this;
}


