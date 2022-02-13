#include <iostream>
using namespace std;
#include "sq_list.h"
#include"alg1.h"
template <class ElemType>
void Show(const ElemType &e)
{
    cout << e << "  ";
}
int main()
{
	char select = '0';
    SqList<int> la,lb,lc;
    int e;
    
	while (select != '3')
	{
        cout << endl << "1. 顺序表差集算法测试";
        cout << endl << "2. 奇偶调整测试";
		cout << endl << "3. 退出";
		cout << endl << "请输入(1~3):";
		cin >> select;
		switch (select) 
		{
			case '1':
				la.Clear();
				lb.Clear();
			    cout << endl << " 请输入第一个线性表中的元素：";
			    cin >> e;
				while (e != 0)
				{
					la.Insert(la.Length() + 1, e);
					cin >> e;
				}

				cout << " 请输入第二个线性表中的元素:";
			    cin >> e;
				while (e != 0)
				{
					lb.Insert(lb.Length() + 1, e);
					cin >> e;
				}
                
				Difference(la,lb,lc);
				cout << "差集为:";
                lc.Traverse(Show<int>);
				cout << endl;
				break;
			case '2':
				la.Clear();
			    cout << endl << " 请输入线性表中的元素：";
				cin >> e;
				while (e != 0)
				{
					la.Insert(la.Length() + 1, e);
					cin >> e;
				}
				Adjust(la);
				cout << "奇偶调整后为:";
				la.Traverse(Show<int>);
				cout << endl;
				break;
			
		}
	}

   	return 0;               		
}


