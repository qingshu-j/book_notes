// straight_insertion_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void straight_insertion_sort(int* p, int len)
{
	//遍历列表，对每个元素，取出来与前面的有序序列比较，然后插入
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


//直接插入排序：时间复杂度度O(n2);空间复杂度1

int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{ 9,1,5,8,3,7,4,6,2 };
	int len = sizeof(mylist) / sizeof(mylist[0]);
	cout << "原列表：";
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

