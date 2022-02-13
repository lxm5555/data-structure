#include <iostream>					// ±‡“Î‘§¥¶¿Ì√¸¡Ó
using namespace std;				
#include "alg3.h"

template <class ElemType>
void Show(const ElemType &e)
// ≤Ÿ◊˜Ω·π˚: œ‘ æ ˝æ›‘™Àÿ
{
    cout << e << "  ";
}

int main()
{
	char select = '0';
	LinkQueue<int> qa;
    int x;
    while (select != '3')
	{
        cout << endl << "1. 回文判断";
        cout << endl << "2. 队列元素倒置";
		cout << endl << "3. 退出";
		cout << endl << "请输入(1~3):";
		cin >> select;
		switch (select)
		{
		case '1':
			char s[100];				
			cout << endl << "请输入字符串：";
			getchar();
			cin.get(s,100);
			if (Palindrome(s))
			{	// ªÿŒƒ
				cout << "\"" << s << "\"" << " 是回文." << endl;
			}
		    else
		    {	// ∑«ªÿŒƒ
			    cout << "\"" << s << "\"" << "不是回文." << endl;
		    }
           	break;
        case '2':
			qa.Clear();
		    cout << endl << "请输入队列元素：";
			cin >> x;
			while (x != 0)
			{
				qa.InQueue(x);
				cin >> x; 
			}
			cout << "逆置前：";
			qa.Traverse(Show);
     		Reverse(qa);
			cout << endl << "逆置后：";
			qa.Traverse(Show);
			cout << endl;
		    break;
		}
	}

	return 0;							
}


