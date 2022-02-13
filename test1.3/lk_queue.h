#pragma once
#include<iostream>
using namespace std;
#include"node.h"														// Ω·µ„¿‡ƒ£∞Â

// ¡¥∂”¡–¿‡ƒ£∞Â

template<class ElemType>
class LinkQueue 
{
protected:
//  ˝æ›≥…‘±:
	Node<ElemType> *front, *rear;										// ∂”Õ∑∂”Œ≤÷∏’Î
	int count;															// ‘™Àÿ∏ˆ ˝

public:
// ≥ÈœÛ ˝æ›¿‡–Õ∑Ω∑®…˘√˜º∞÷ÿ‘ÿ±‡“ÎœµÕ≥ƒ¨»œ∑Ω∑®…˘√˜:
	LinkQueue();														
	virtual ~LinkQueue();												
	int Length() const;													// «Û∂”¡–≥§∂»
	bool Empty() const;													// ≈–∂œ∂”¡– «∑ÒŒ™ø’
	void Clear();														// Ω´∂”¡–«Âø’
	void Traverse(void (*visit)(const ElemType &)) const ;				// ±È¿˙∂”¡–
	bool OutQueue(ElemType &e);											// ≥ˆ∂”≤Ÿ◊˜
	bool OutQueue();													// ≥ˆ∂”≤Ÿ◊˜
	bool GetHead(ElemType &e) const;									// »°∂”Õ∑≤Ÿ◊˜
	bool InQueue(const ElemType &e);									// »Î∂”≤Ÿ◊˜
	LinkQueue(const LinkQueue<ElemType> &source);						// ∏¥÷∆ππ‘Ï∫Ø ˝ƒ£∞Â
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &source);	// ÷ÿ‘ÿ∏≥÷µ‘ÀÀ„∑˚
};

// ¡¥∂”¡–¿‡ƒ£∞Âµƒ µœ÷≤ø∑÷

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// ≤Ÿ◊˜Ω·π˚£∫ππ‘Ï“ª∏ˆø’∂”¡–
{
	rear = front = new Node<ElemType>;									// …˙≥…Õ∑Ω·µ„
	count = 0;															// ≥ı ºªØ‘™Àÿ∏ˆ ˝
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// ≤Ÿ◊˜Ω·π˚£∫œ˙ªŸ∂”¡–
{
	Clear();															// «Âø’∂”¡–
	delete front;														
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// ≤Ÿ◊˜Ω·π˚£∫∑µªÿ∂”¡–≥§∂»			 
{
	return count;														// count±Ì æ∂”¡–‘™Àÿ∏ˆ ˝
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const

{
	return count == 0;													// count == 0±Ì æ∂”¡–Œ™ø’
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// ≤Ÿ◊˜Ω·π˚£∫«Âø’∂”¡–
{
	while (!Empty())
	{	// ∂”¡–∑«ø’£¨‘Ú≥ˆ¡–
		OutQueue();														// ≥ˆ¡–
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*visit)(const ElemType &)) const 
// ≤Ÿ◊˜Ω·π˚£∫“¿¥Œ∂‘∂”¡–µƒ√ø∏ˆ‘™Àÿµ˜”√∫Ø ˝(*visit)
{
	for (Node<ElemType> *temPtr = front->next; temPtr != NULL; temPtr = temPtr->next)
	{	// ∂‘∂”¡–µƒ√ø∏ˆ‘™Àÿµ˜”√∫Ø ˝(*visit)
		(*visit)(temPtr->data);
	}
}


template<class ElemType>
bool LinkQueue<ElemType>::OutQueue(ElemType &e)
{
	if (!Empty()) 
	{	// ∂”¡–∑«ø’
		Node<ElemType> *temPtr = front->next;							// ÷∏œÚ∂”¡–Õ∑Àÿ
		e = temPtr->data;												// ”√e∑µªÿ∂”Õ∑‘™Àÿ
		front->next = temPtr->next;									// front->next÷∏œÚœ¬“ª‘™Àÿ
		if (rear == temPtr)
		{	// ±Ì æ≥ˆ∂”«∞∂”¡–÷–÷ª”–“ª∏ˆ‘™Àÿ£¨≥ˆ∂”∫ÛŒ™ø’∂”¡–
			rear = front;
		}
		delete temPtr;													//  Õ∑≈≥ˆ∂”µƒΩ·µ„
		count--;														// ≥ˆ∂”≥…π¶∫Û‘™Àÿ∏ˆ ˝◊‘ºı1
		return true;													// ≥…π¶
	}
	else
	{	// ∂”¡–Œ™ø’
		return false;													//  ß∞‹
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::OutQueue()
{
	if (!Empty()) 
	{	// ∂”¡–∑«ø’
		Node<ElemType> *temPtr = front->next;							// ÷∏œÚ∂”¡–Õ∑Àÿ
		front->next = temPtr->next;									// front->next÷∏œÚœ¬“ª‘™Àÿ
		if (rear == temPtr)
		{	// ±Ì æ≥ˆ∂”«∞∂”¡–÷–÷ª”–“ª∏ˆ‘™Àÿ£¨≥ˆ∂”∫ÛŒ™ø’∂”¡–
			rear = front;
		}
		delete temPtr;													//  Õ∑≈≥ˆ∂”µƒΩ·µ„
		count--;														// ≥ˆ∂”≥…π¶∫Û‘™Àÿ∏ˆ ˝◊‘ºı1
		return true;													// ≥…π¶
	}
	else
	{	// ∂”¡–Œ™ø’
		return false;													//  ß∞‹
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType &e) const
{
	if (!Empty()) 
	{	// ∂”¡–∑«ø’
		Node<ElemType> *temPtr = front->next;							// ÷∏œÚ∂”¡–Õ∑Àÿ
		e = temPtr->data;												// ”√e∑µªÿ∂”Õ∑‘™Àÿ
		return true;													// ≥…π¶
	}
	else
	{	// ∂”¡–Œ™ø’
		return false;													//  ß∞‹
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType &e)
{
	Node<ElemType> *temPtr = new Node<ElemType>(e);					// …˙≥…–¬Ω·µ„
	if (temPtr == NULL)
	{	// ∂ØÃ¨ƒ⁄¥Ê∫ƒæ°
		return false;													//  ß∞‹
	}
	else
	{	// ≤Ÿ◊˜≥…π¶
		rear->next = temPtr;											// –¬Ω·µ„◊∑º”‘⁄∂”Œ≤
		rear = temPtr;													// rear÷∏œÚ–¬∂”Œ≤
		count++;														// »Î∂”≥…π¶∫Û‘™Àÿ∏ˆ ˝º”1 
		return true;													// ≥…π¶
	}
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &source)
{
	rear = front = new Node<ElemType>;	// …˙≥…Õ∑Ω·µ„
	count = 0;															// ≥ı ºªØ‘™Àÿ∏ˆ ˝
	for (Node<ElemType> *temPtr = source.front->next; temPtr != NULL; temPtr = temPtr->next)
	{	// ∂‘source∂”¡–µƒ√ø∏ˆ‘™Àÿ∂‘µ±«∞∂”¡–◊˜»Î∂”¡–≤Ÿ◊˜
		InQueue(temPtr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &source)
// ≤Ÿ◊˜Ω·π˚£∫Ω´∂”¡–source∏≥÷µ∏¯µ±«∞∂”¡–°™°™÷ÿ‘ÿ∏≥÷µ‘ÀÀ„∑˚
{
	if (&source != this)
	{
		Clear();														// «Âø’µ±«∞∂”¡– 
		for (Node<ElemType> *temPtr = source.front->next; temPtr != NULL; temPtr = temPtr->next)
		{	// ∂‘source∂”¡–µƒ√ø∏ˆ‘™Àÿ∂‘µ±«∞∂”¡–◊˜»Î∂”¡–≤Ÿ◊˜
			InQueue(temPtr->data);
		}
	}
	return *this;
}


