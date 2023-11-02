// simple_selection_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void simple_selection_sort(int* p, int len)
{
	//用每个元素与后面所有元素作比较，标记最小的，每一轮结束后再交换
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

//简单选择排序：时间复杂度度O(n2);空间复杂度1


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
	simple_selection_sort(mylist, len);
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
    return 0;
}

