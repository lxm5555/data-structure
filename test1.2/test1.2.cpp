#include <iostream>				// ±‡“Î‘§¥¶¿Ì√¸¡Ó
using namespace std;			//  π”√√¸√˚ø’º‰std 
#include "alg2.h"

template <class ElemType>
void Show(const ElemType &e)
// ≤Ÿ◊˜Ω·π˚: œ‘ æ ˝æ›‘™Àÿ
{
    cout << e << "  ";
}

int main()
{
	char select = '0';
    SimpleLinkList<int> la,lb,lc;
    int e;

    while (select != '3')
	{
        cout << endl << "1. 单链表递增差集算法测试";
        cout << endl << "2. 单链表逆置测试";
		cout << endl << "3. 退出";
		cout << endl << "请输入(1~3):";
		cin >> select;
		switch (select) 
		{
			case '1':
				la.Clear();
				lb.Clear();
			    cout << endl << " 请依次输入第一个链表中的元素:";
			    cin >> e;
				while (e != 0)
				{
					la.Insert(la.Length() + 1, e);
					cin >> e;
				}

				cout << " 请依次输入第二个链表中的元素:";
			    cin >> e;
				while (e != 0)
				{
					lb.Insert(lb.Length() + 1, e);
					cin >> e;
				}
                Difference(la,lb,lc);
				cout << "递增差集为：";
				lc.Traverse(Show<int>);
				cout << endl;
			    break;
			case '2':
				la.Clear();
			    cout << endl << " 请依次输入链表中的元素:";
				cin >> e;
				while (e != 0)
				{
					la.Insert(la.Length() + 1, e);
					cin >> e;
				}

				la.Reverse();
				cout << "逆置后为:";
				la.Traverse(Show<int>);
				cout << endl;
			    break;
		}
	}

	return 0;               // ∑µªÿ÷µ0, ∑µªÿ≤Ÿ◊˜œµÕ≥
}
