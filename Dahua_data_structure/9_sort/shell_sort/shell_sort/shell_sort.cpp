// shell_sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

using namespace std;


void shell_sort(int* p, int len)
{
	/*����ô�����ļ�¼����������?�������뵽�ľ��ǽ�ԭ���д�����¼���ļ�¼���з��顣
	�ָ�����ɸ������У���ʱÿ�������д�����ļ�¼�����ͱȽ����ˣ�Ȼ������Щ�������ڷֱ����ֱ�Ӳ�������

	���������ж���������ʱ��ע��ֻ�ǻ�������ʱ���ٶ�ȫ���¼����һ��ֱ�Ӳ�������
	���Ƿָ�������¼��Ŀ���Ǽ��ٴ������¼�ĸ�������ʹ�����������������չ��
	�������������������͸�������ķ����ﲻ�����ǵ�Ҫ��
	��ˣ�������Ҫ��ȡ��Ծ�ָ�Ĳ���:�����ĳ�����������ļ�¼���һ�������У�
	�������ܱ�֤���������ڷֱ����ֱ�Ӳ��������õ��Ľ���ǻ�����������Ǿֲ�����

	����ѡ��Ҳ��һ��Ҫ�㣬�ؼ���
	��Ҫע����ǣ��������е����һ������ֵ�������1���С�
	�������ڼ�¼����Ծʽ���ƶ���ϣ�����򲢲���һ���ȶ��������㷨��
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


//ϣ������ʱ�临�Ӷȶ�O(n 3/2);�ռ临�Ӷ�1 ��������O(n2)���Ӷȵ�ʱ��

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
	shell_sort(mylist, len);
	return 0;
}

