// simple_selection_sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void simple_selection_sort(int* p, int len)
{
	//��ÿ��Ԫ�����������Ԫ�����Ƚϣ������С�ģ�ÿһ�ֽ������ٽ���
	for (int i = 0; i < len - 1 ; i++)
	{
		int min = i;
		for (int j = i+1; j < len; j++)
		{
			if (p[min] > p[j])
			{
				min = j;
			}
		}
		if (min!=i)
		{
			int temp = p[i];
			p[i] = p[min];
			p[min] = temp;
		}
	}
}

//��ѡ������ʱ�临�Ӷȶ�O(n2);�ռ临�Ӷ�1


int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{ 9,1,5,8,3,7,4,6,2 };
	int len = sizeof(mylist) / sizeof(mylist[0]);
	cout << "ԭ�б�";
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
	simple_selection_sort(mylist, len);
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
    return 0;
}

