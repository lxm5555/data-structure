#include<iostream>
using namespace std;
#include "node.h"								// Ω·µ„¿‡ƒ£∞Â

// ºÚµ•œﬂ–‘¡¥±Ì¿‡ƒ£∞Â
template <class ElemType>
class SimpleLinkList 
{
protected:
//  ˝æ›≥…‘±:
	Node<ElemType> *head;						// Õ∑Ω·µ„÷∏’Î

// ∏®÷˙∫Ø ˝ƒ£∞Â:
	Node<ElemType> *GetElemPtr(int position) const;			// ∑µªÿ÷∏œÚµ⁄position∏ˆΩ·µ„µƒ÷∏’Î

public:
// ≥ÈœÛ ˝æ›¿‡–Õ∑Ω∑®…˘√˜º∞÷ÿ‘ÿ±‡“ÎœµÕ≥ƒ¨»œ∑Ω∑®…˘√˜:
	SimpleLinkList();							
	virtual ~SimpleLinkList();					
	int Length() const;							// «Ûœﬂ–‘±Ì≥§∂»			 
	bool Empty() const;							// ≈–∂œœﬂ–‘±Ì «∑ÒŒ™ø’
	void Clear();								// Ω´œﬂ–‘±Ì«Âø’
	void Traverse(void (*visit)(const ElemType &)) const;	// ±È¿˙œﬂ–‘±Ì
	bool GetElem(int position, ElemType &e) const;			// «Û÷∏∂®Œª÷√µƒ‘™Àÿ	
	bool SetElem(int position, const ElemType &e);			// …Ë÷√÷∏∂®Œª÷√µƒ‘™Àÿ÷µ
	bool Delete(int position, ElemType &e);					// …æ≥˝‘™Àÿ		
	bool Delete(int position);								// …æ≥˝‘™Àÿ		
	bool Insert(int position, const ElemType &e);			// ≤Â»Î‘™Àÿ
	SimpleLinkList(const SimpleLinkList<ElemType> &source);	// ∏¥÷∆ππ‘Ï∫Ø ˝ƒ£∞Â
	SimpleLinkList<ElemType> &operator =(const SimpleLinkList<ElemType> &source); // ÷ÿ‘ÿ∏≥÷µ‘ÀÀ„∑˚
	void Reverse();								
};


// ºÚµ•œﬂ–‘¡¥±Ì¿‡ƒ£∞Âµƒ µœ÷≤ø∑÷
template<class ElemType>
Node<ElemType> *SimpleLinkList<ElemType>::GetElemPtr(int position) const
// ≤Ÿ◊˜Ω·π˚£∫∑µªÿ÷∏œÚµ⁄position∏ˆΩ·µ„µƒ÷∏’Î
{
	Node<ElemType> *temPtr = head;				// ”√temPtr±È¿˙œﬂ–‘±Ì“‘≤È’“µ⁄position∏ˆΩ·µ„
	int temPos = 0;								// temPtrÀ˘÷∏Ω·µ„µƒŒª÷√ 

	while (temPtr != NULL && temPos < position)
	{	
		temPtr = temPtr->next;
		temPos++;
	}

	if (temPtr != NULL && temPos == position)
	{	// ≤È’“≥…π¶
		return temPtr;	
	}
	else
	{	// ≤È’“ ß∞‹
		return NULL;	
	}
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList()
// ≤Ÿ◊˜Ω·π˚£∫ππ‘Ï“ª∏ˆø’¡¥±Ì
{
	head = new Node<ElemType>;					// ππ‘ÏÕ∑Ω·µ„£¨ø’¡¥±Ì÷ª”–Õ∑Ω·µ„
}

template <class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList()
{
	Clear();									// «Âø’œﬂ–‘±Ì
	delete head;								//  Õ∑≈Õ∑Ω·µ„À˘µ„ø’º‰
}

template <class ElemType>
int SimpleLinkList<ElemType>::Length() const
{
	int count = 0;								// º∆ ˝∆˜ 
	for (Node<ElemType> *temPtr = head->next; temPtr != NULL; temPtr = temPtr->next)
	{	// ”√temPtr“¿¥Œ÷∏œÚ√ø∏ˆ‘™Àÿ
		count++;								// ∂‘œﬂ–‘±Ìµƒ√ø∏ˆ‘™ÀÿΩ¯––º∆ ˝
	}
	return count;								// ∑µªÿ‘™Àÿ∏ˆ ˝
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Empty() const
{
	return head->next == NULL;
}

template <class ElemType>
void SimpleLinkList<ElemType>::Clear()
// ≤Ÿ◊˜Ω·π˚£∫«Âø’œﬂ–‘±Ì
{
	while (!Empty())
	{	// ±Ì–‘±Ì∑«ø’£¨‘Ú…æ≥˝µ⁄1∏ˆ‘™Àÿ
		Delete(1);								// …æ≥˝µ⁄1∏ˆ‘™Àÿ
	}
}

template <class ElemType>
void SimpleLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ≤Ÿ◊˜Ω·π˚£∫“¿¥Œ∂‘œﬂ–‘±Ìµƒ√ø∏ˆ‘™Àÿµ˜”√∫Ø ˝(*visit)
{
	for (Node<ElemType> *temPtr = head->next; temPtr != NULL; temPtr = temPtr->next)
	{	// ”√temPtr“¿¥Œ÷∏œÚ√ø∏ˆ‘™Àÿ
		(*visit)(temPtr->data);					// ∂‘œﬂ–‘±Ìµƒ√ø∏ˆ‘™Àÿµ˜”√∫Ø ˝(*visit)
	}
}

template <class ElemType>
bool SimpleLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
	if (position < 1 || position > Length())
	{	// position∑∂Œß¥Ì
		return false;							// ‘™Àÿ≤ª¥Ê‘⁄
	}
	else
	{	// position∫œ∑®
		Node<ElemType> *temPtr = GetElemPtr(position);			// »°≥ˆ÷∏œÚµ⁄position∏ˆΩ·µ„µƒ÷∏’Î	
		e = temPtr->data;						
		return true;							// ‘™Àÿ¥Ê‘⁄
	}
}

template <class ElemType>
bool SimpleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
	if (position < 1 || position > Length())
	{	// position∑∂Œß¥Ì
		return false;							// ∑∂Œß¥Ì
	}
	else
	{	// position∫œ∑®
		Node<ElemType> *temPtr = GetElemPtr(position);			// »°≥ˆ÷∏œÚµ⁄position∏ˆΩ·µ„µƒ÷∏’Î
		temPtr->data = e;						
		return true;							// …Ë÷√‘™Àÿ≥…π¶
	}
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Delete(int position, ElemType &e)
{
	if (position < 1 || position > Length())
	{	// position∑∂Œß¥Ì
		return false;							// ∑∂Œß¥Ì
	}
	else
	{	// position∫œ∑®
		Node<ElemType> *temPtr = GetElemPtr(position - 1);		// »°≥ˆ÷∏œÚµ⁄position-1∏ˆΩ·µ„µƒ÷∏’Î
		Node<ElemType> *nextPtr = temPtr->next;
		temPtr->next = nextPtr->next;			// …æ≥˝Ω·µ„
		e = nextPtr->data;						// ”√e∑µªÿ±ª…æΩ·µ„‘™Àÿ÷µ	
		delete nextPtr;							//  Õ∑≈±ª…æΩ·µ„
		return true;							// …æ≥˝≥…π¶
	}
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Delete(int position)

{
	if (position < 1 || position > Length())
	{	// position∑∂Œß¥Ì
		return false;							// ∑∂Œß¥Ì
	}
	else
	{	// position∫œ∑®
		Node<ElemType> *temPtr = GetElemPtr(position - 1);		// »°≥ˆ÷∏œÚµ⁄position-1∏ˆΩ·µ„µƒ÷∏’Î
		Node<ElemType> *nextPtr = temPtr->next;
		temPtr->next = nextPtr->next;			// …æ≥˝Ω·µ„
		delete nextPtr;							//  Õ∑≈±ª…æΩ·µ„
		return true;							// …æ≥˝≥…π¶
	}
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Insert(int position, const ElemType &e)
{
	if (position < 1 || position > Length() + 1)
	{	// position∑∂Œß¥Ì
		return false;							// Œª÷√≤ª∫œ∑®
	}
	else
	{	// position∫œ∑®
		Node<ElemType> *temPtr = GetElemPtr(position - 1);				// »°≥ˆ÷∏œÚµ⁄position-1∏ˆΩ·µ„µƒ÷∏’Î
		Node<ElemType> *newPtr = new Node<ElemType>(e, temPtr->next);	// …˙≥…–¬Ω·µ„
		temPtr->next = newPtr;					// Ω´temPtr≤Â»ÎµΩ¡¥±Ì÷–
		return true;							// ≤Â»Î≥…π¶
	}
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &source)

{
	int sourceLength = source.Length();			
	ElemType tempElem;							// ¡Ÿ ±‘™Àÿ
	head = new Node<ElemType>;					

	for (int temPos = 1; temPos <= sourceLength; temPos++)
	{	// ∏¥÷∆ ˝æ›‘™Àÿ
		source.GetElem(temPos, tempElem);		// »°≥ˆµ⁄temPos∏ˆ‘™Àÿ
		Insert(Length() + 1, tempElem);			// Ω´tempElem≤Â»ÎµΩµ±«∞œﬂ–‘±Ì
	}
}

template <class ElemType>
SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator =(const SimpleLinkList<ElemType> &source)
{
	if (&source != this)
	{
		int sourceLength = source.Length();		
		ElemType tempElem;						// ¡Ÿ ±‘™Àÿ
		Clear();								// «Âø’µ±«∞œﬂ–‘±Ì

		for (int temPos = 1; temPos <= sourceLength; temPos++)
		{	// ∏¥÷∆ ˝æ›‘™Àÿ
			source.GetElem(temPos, tempElem);	// »°≥ˆµ⁄temPos∏ˆ‘™Àÿ
			Insert(Length() + 1, tempElem);		// Ω´tempElem≤Â»ÎµΩµ±«∞œﬂ–‘±Ì
		}
	}
	return *this;
}


