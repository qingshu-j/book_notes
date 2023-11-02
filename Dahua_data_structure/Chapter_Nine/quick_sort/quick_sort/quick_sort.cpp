// quick_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

void swap(int* p, int low, int high)
{
	int temp = p[low];
	p[low] = p[high];
	p[high] = temp;
}

int partition(int* p, int low, int high)
{
	//for (int i =0;i<9;i++)
	//{
	//	cout << p[i];
	//}
	//cout << endl;
	int pivot = p[low];//优化，取第一个元素不太稳定，可取每次列表的三数的中间数
	while (low < high)
	{
		while (low < high && p[high] > pivot)
		{
			high--;
		}
		swap(p, low, high);
		while (low < high && p[low] < pivot)
		{
			low++;
		}
		swap(p, low, high);
	} 
	return low;
}


void sort(int* p, int low,int high)
{
	int pivot;
	if (low < high)
	{
		pivot = partition(p, low, high);
		sort(p, low, pivot - 1);
		sort(p, pivot + 1, high);
	}
}

void quick_sort(int* p, int len)
{
	//取一个轴值，遍历一遍，将列表分为小于和大于轴值的两个列表，递归上述操作，直到所有列表都有序
	sort(p,0,len-1);
}


//快速排序：最好情况是满二叉树，递归logn次，时间最好和平均复杂度度O(nlogn);最坏是二叉树变成链表情况，复杂度度O(n2)

int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{ 5,1,9,3,7,4,8,6,2 };
	int len = sizeof(mylist) / sizeof(mylist[0]);
	cout << "原列表：";
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
	quick_sort(mylist, len);
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
	return 0;
}
