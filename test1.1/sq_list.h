#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 1000		// ȱʡԪ�ظ���
#endif

// ˳�����ģ��
template <class ElemType>
class SqList 
{
protected:
// ���ݳ�Ա:
	ElemType *elems;					// Ԫ�ش洢�ռ�
	int maxSize;						// ˳������Ԫ�ظ���
	int count;							// Ԫ�ظ���

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqList(int size = DEFAULT_SIZE);							// ���캯��ģ��
	virtual ~SqList();					// ��������ģ��
	int Length() const;					// �����Ա�����			 
	bool Empty() const;					// �ж����Ա��Ƿ�Ϊ��
	void Clear();						// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;		// �������Ա�
	bool GetElem(int position, ElemType &e) const;				// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);				// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);						// ɾ��Ԫ��		
	bool Delete(int position);			// ɾ��Ԫ��		
	bool Insert(int position,const ElemType &e);				// ����Ԫ��
	SqList(const SqList<ElemType> &source);						// ���ƹ��캯��ģ��
	SqList<ElemType> &operator =(const SqList<ElemType> &source); // ���ظ�ֵ�����
};


// ˳�����ģ���ʵ�ֲ���

template <class ElemType>
SqList<ElemType>::SqList(int size)
{
	maxSize = size;						// ���Ԫ�ظ���
	elems = new ElemType[maxSize];		// ����洢�ռ�
	count = 0;							// �����Ա�Ԫ�ظ���Ϊ0
}

template <class ElemType>
SqList<ElemType>::~SqList()
// ����������������Ա�
{
	delete []elems;						// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;						// ����Ԫ�ظ���
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return count == 0;					// count == 0��ʾ���Ա�Ϊ��
}

template <class ElemType>
void SqList<ElemType>::Clear()
// ���������������Ա�
{
	count = 0;							// �����Ա�Ԫ�ظ���Ϊ0
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա���ÿ��Ԫ�ص��ú���(*visit)
{
	for (int temPos = 1; temPos <= Length(); temPos++)
	{	// �����Ա���ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(elems[temPos - 1]);
	}
}

template <class ElemType>
bool SqList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա����ڵ�position��Ԫ��ʱ����e������ֵ������true, ���򷵻�false
{
	if(position < 1 || position > Length())
	{	// position��Χ��
		return false;					// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		e = elems[position - 1];
		return true;					// Ԫ�ش���
	}
}

template <class ElemType>
bool SqList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա��ĵ�position��Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;					// ��Χ��
	}
	else
	{	// position�Ϸ�
		elems[position - 1] = e;
		return true;					// �ɹ�
	}
}

template <class ElemType>
bool SqList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա��ĵ�position��Ԫ��, ��ǰ��e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;					// ��Χ��
	}
	else
	{	// position�Ϸ�
		GetElem(position, e);			// ��e���ر�ɾ��Ԫ�ص�ֵ
		ElemType temElem;				// ��ʱԪ��
		for (int temPos = position + 1; temPos <= Length(); temPos++)
		{	// ��ɾ��Ԫ��֮���Ԫ����������
			GetElem(temPos, temElem); SetElem(temPos - 1, temElem); 
		}
		count--;						// ɾ����Ԫ�ظ������Լ�1
		return true;					// ɾ���ɹ�
	}
}

template <class ElemType>
bool SqList<ElemType>::Delete(int position)
// ���������ɾ�����Ա��ĵ�position��Ԫ��,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;					// ��Χ��
	}
	else
	{	// position�Ϸ�
		ElemType temElem;				// ��ʱԪ��
		for (int temPos = position + 1; temPos <= Length(); temPos++)
		{	// ��ɾ��Ԫ��֮���Ԫ����������
			GetElem(temPos, temElem); SetElem(temPos - 1, temElem); 
		}
		count--;						// ɾ����Ԫ�ظ������Լ�1
		return true;					// ɾ���ɹ�
	}
}

template <class ElemType>
bool SqList<ElemType>::Insert(int position, const ElemType &e)
{
	if (count == maxSize)
	{	// ���Ա���������false
		return false;	
	}
	else if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false;					// ��Χ��
	}
	else
	{	// �ɹ�
		ElemType temElem;				// ��ʱԪ��
		for (int temPos = Length(); temPos >= position; temPos--)
		{	// ����λ��֮���Ԫ������
			GetElem(temPos, temElem); SetElem(temPos + 1, temElem); 
		}
		count++;						// �����Ԫ�ظ���������1
		SetElem(position, e);			
		return true;					// ����ɹ�
	}
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &source)
// ��������������Ա�source���������Ա��������ƹ��캯��ģ��
{
	maxSize = source.maxSize;			// ���Ԫ�ظ���
	count = source.count;				// ���Ա�Ԫ�ظ���
	elems = new ElemType[maxSize];		// ����洢�ռ�
	for (int temPos = 1; temPos <= source.Length(); temPos++)
	{	// ��������Ԫ��
		elems[temPos - 1] = source.elems[temPos - 1];	// ����Ԫ��ֵ
	}
}

template <class ElemType>
SqList<ElemType> &SqList<ElemType>::operator =(const SqList<ElemType> &source)
// ��������������Ա�source��ֵ����ǰ���Ա��������ظ�ֵ�����
{
	if (&source != this)
	{
		maxSize = source.maxSize;		// ���Ԫ�ظ���
		count = source.count;			// ���Ա�Ԫ�ظ���
		delete []elems;					// �ͷŴ洢�ռ�
		elems = new ElemType[maxSize];	// ����洢�ռ�
		for (int temPos = 1; temPos <= source.Length(); temPos++)
		{	// ��������Ԫ��
			elems[temPos - 1] = source.elems[temPos - 1];	// ����Ԫ��ֵ
		}
	}
	return *this;
}

#endif