// quick_sort.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int pivot = p[low];//�Ż���ȡ��һ��Ԫ�ز�̫�ȶ�����ȡÿ���б���������м���
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
	//ȡһ����ֵ������һ�飬���б��ΪС�ںʹ�����ֵ�������б��ݹ�����������ֱ�������б�����
	sort(p,0,len-1);
}


//���������������������������ݹ�logn�Σ�ʱ����ú�ƽ�����Ӷȶ�O(nlogn);��Ƕ��������������������Ӷȶ�O(n2)

int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{ 5,1,9,3,7,4,8,6,2 };
	int len = sizeof(mylist) / sizeof(mylist[0]);
	cout << "ԭ�б�";
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
