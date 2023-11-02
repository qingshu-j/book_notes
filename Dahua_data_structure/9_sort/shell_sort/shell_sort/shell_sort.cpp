// shell_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;


void shell_sort(int* p, int len)
{
	/*如何让待排序的记录个数较少呢?很容易想到的就是将原本有大量记录数的记录进行分组。
	分割成若干个子序列，此时每个子序列待排序的记录个数就比较少了，然后在这些子序列内分别进行直接插入排序，

	当整个序列都基本有序时，注意只是基本有序时，再对全体记录进行一次直接插入排序。
	我们分割待排序记录的目的是减少待排序记录的个数，并使整个序列向基本有序发展。
	而如上面这样分完组后就各自排序的方法达不到我们的要求。
	因此，我们需要采取跳跃分割的策略:将相距某个“增量”的记录组成一个子序列，
	这样才能保证在子序列内分别进行直接插入排序后得到的结果是基本有序而不是局部有序。

	增量选择也是一个要点，关键。
	需要注意的是，增量序列的最后一个增量值必须等于1才行。
	另外由于记录是跳跃式的移动，希尔排序并不是一种稳定的排序算法。
		*/
	int increment = len;
	do 
	{
		increment = increment / 3 + 1;
		for (int i = increment;i<len;i++)
		{
			if (p[i- increment]>p[i])
			{
				int insertP = p[i];
				int j;
				for (j = i - increment; j >= 0 && p[j] > insertP; j-= increment)
				{
					p[j + increment] = p[j];
				}
				p[j + increment] = insertP;
			}
		}
		for (int i = 0; i < len; i++)
		{
			cout << p[i];
		}
		cout << endl;
	} while (increment>1);

}


//希尔排序：时间复杂度度O(n 3/2);空间复杂度1 ；结束了O(n2)复杂度的时代

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
	shell_sort(mylist, len);
	return 0;
}

