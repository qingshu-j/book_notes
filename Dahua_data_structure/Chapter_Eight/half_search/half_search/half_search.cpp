// half_search.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void half_search(int* p, int min, int max,int value)
{
	if (min<max)
	{
		int low = min, high = max, half;
		half = (low + high) / 2;
		if (p[half] > value)
		{
			half_search(p, min, half - 1, value);
		}
		else if (p[half] == value)
		{
			cout << half << endl;
		}
		else
		{
			half_search(p, half + 1, max, value);
		}
	}
	else if (min==max && p[min] == value)
	{
		cout << min << endl;
	}
	else
	{
		cout << -1 << endl;
	}
}

void half_search1(int* p, int min, int max, int value)
{
	int low = min, high = max, half;
	while (low<=high)
	{
		half = (low + high) / 2;
		if (p[half] > value)
		{
			high = half - 1;
		}
		else if (p[half] == value)
		{
			cout << half << endl;
			return;
		}
		else
		{
			low = half + 1;
		}
	}
	cout << -1 << endl;
}

//�۰���ң�ʱ�临�Ӷȶ�O(logn),ǰ�������������б�
//�����ֱ�ӱ������ң�ʱ�临�Ӷȶ�O(n)

int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{ 1,2,3,4,5,6,7,8,9};
	int len = sizeof(mylist) / sizeof(mylist[0]);
	int value = 5;
	half_search1(mylist, 0,8, value);
	return 0;
}
