// BubbleSort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void BubbleSort1(int* p,int len)
{
	//��ÿ��Ԫ�����������Ԫ�����Ƚϣ������򽻻���ÿһ�ֺ󶼱�֤�Ƚϵ��Ǹ�Ԫ������С��
	for (int i =0;i<len-1;i++)
	{
		for (int j =i+1;j<len;j++)
		{
			if (p[i]>p[j])
			{
				int temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
		for (int i = 0; i < len; i++)
		{
			cout << p[i];
		}
		cout << endl;
	}
}

void BubbleSort2(int* p, int len)
{
	//�����������������׷���ÿ�ֹ��������Ǹ�Ԫ��������
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len-1-i; j++)
		{
			if (p[j] > p[j+1])
			{
				int temp = p[j+1];
				p[j+1] = p[j];
				p[j] = temp;
			}
		}
		for (int i = 0; i < len; i++)
		{
			cout << p[i];
		}
		cout << endl;
	}
}


void BubbleSort3(int* p, int len)
{
	//��������������ð�ݷ���ÿ�ֹ�����ǰ����Ǹ�Ԫ������С��
	int flag = true;
	for (int i = 0; i < len - 1 && flag; i++)
	{
		flag = false;
		for (int j = len - 2; j >= 0; j--)
		{
			if (p[j] > p[j + 1])
			{
				int temp = p[j + 1];
				p[j + 1] = p[j];
				p[j] = temp;
				flag = true;
			}
		}
		for (int i = 0; i < len; i++)
		{
			cout << p[i];
		}
		cout << endl;
	}
}

int main()
{
	int mylist[] = /*{2,1,3,4,5,6,7,8,9}*/{9,1,5,8,3,7,4,6,2};
	int len = sizeof(mylist)/ sizeof(mylist[0]);
	cout << "ԭ�б�";
	for each (auto i in mylist)
	{
		cout << i;
	}
	cout << endl;
	BubbleSort3(mylist, len);
    return 0;
}

