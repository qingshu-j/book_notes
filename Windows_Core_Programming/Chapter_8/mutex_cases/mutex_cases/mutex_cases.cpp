// mutex_cases.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


using namespace std;

/*
ID���ڱ�ʶϵͳ�е��ĸ��̵߳�ǰӵ�л�����󣬵ݹ����������ָ�����߳�ӵ�л������Ĵ�����
�������mutex���ں˶����ܹ�ȷ���߳�ӵ�жԵ�����Դ�Ļ������Ȩ��
ͨ������һ���ȴ������������ݸ��𱣻���Դ�Ļ������ľ�����߳̾��ܹ���öԹ���
��Դ�ķ���Ȩ�����ڲ����ȴ�����Ҫ����̵߳�ID�����˽����Ƿ���0��������󷢳�֪ͨ��
�ţ�������߳�ID��0����ô���߳�ID������Ϊ�����̵߳�ID���ݹ������������Ϊ1��ͬʱ��
�����̱߳��ֿɵ���״̬��
����ȴ���������ID����0����������������֪ͨ�źţ�����ô�����̱߳����ȴ�״̬��
ϵͳ����ס�������������ڻ�������ID��������Ϊ0ʱ�����߳�ID����Ϊ�ȴ��̵߳�ID��
���ݹ����������Ϊ1����������ȴ��߳��ٴγ�Ϊ�ɵ����̡߳����������һ�����Ի�����
�˶�����еļ����޸Ķ�����ԭ�Ӳ�����ʽ���еġ�
*/

#define THREAD_NUMS 2
HANDLE g_mutexhandle = NULL;
int g_nums = 0;

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter)
{
	DWORD dw_obj = WaitForSingleObject(g_mutexhandle, INFINITE);
	switch (dw_obj)
	{
	case WAIT_OBJECT_0:
	{
		for (int i = 0; i < 1000000; i++)
		{
			g_nums += 1;
		}
		ReleaseMutex(g_mutexhandle);
	}
	break;
	case WAIT_FAILED:
	{
		cout << "err:" << GetLastError() << endl;
	}
	break;
	case WAIT_TIMEOUT:
		break;
	}
	return 0L;
}


int main()
{
	g_mutexhandle = CreateMutex(NULL, FALSE, NULL);
	if (!g_mutexhandle)
	{
		cout << "CreateMutex failed:" << endl;
		return 0;
	}
	HANDLE handle[THREAD_NUMS];
	DWORD starttime = GetTickCount();
	for (int i = 0; i < THREAD_NUMS; i++)
	{
		handle[i] = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	}
	DWORD dw_obj = WaitForMultipleObjects(THREAD_NUMS, handle, TRUE, INFINITE);
	cout << "time:" << GetTickCount() - starttime << "ms." << endl;
	switch (dw_obj)
	{
	case WAIT_OBJECT_0:
	{
		for (int i = 0; i < THREAD_NUMS; i++)
		{
			CloseHandle(handle[i]);
		}
		cout << "g_nums:" << g_nums << endl;
	}
	break;
	case WAIT_FAILED:
	{
		cout << "err:" << GetLastError() << endl;
	}
	break;
	case WAIT_TIMEOUT:
		break;
	}
	CloseHandle(g_mutexhandle);

	return 0;
}


