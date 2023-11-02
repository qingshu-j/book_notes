// straight_insertion_sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void straight_insertion_sort(int* p, int len)
{
	//�����б���ÿ��Ԫ�أ�ȡ������ǰ����������бȽϣ�Ȼ�����
	for (int i = 1; i < len; i++)
	{
		if (p[i-1] > p[i])
		{
			int insertP = p[i];
			int j;
			for (j = i-1; j>=0 && p[j] > insertP; j--)
			{
				p[j + 1] = p[j];
			}
			p[j + 1] = insertP;
		}

		for (int i = 0; i < len; i++)
		{
			cout << p[i];
		}
		cout << endl;
	}
}


//ֱ�Ӳ�������ʱ�临�Ӷȶ�O(n2);�ռ临�Ӷ�1

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
	straight_insertion_sort(mylist, len);
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
	return 0;
}

