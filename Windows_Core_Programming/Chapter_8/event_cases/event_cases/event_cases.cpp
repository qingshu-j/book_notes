// event_cases.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace std;

/*
�¼��ܹ�֪ͨһ�������Ѿ���ɡ������ֲ�ͬ���͵��¼�����
һ�����˹����õ��¼�����һ�����Զ����õ��¼���
���˹����õ��¼��õ�֪ͨʱ���ȴ����¼��������߳̾���Ϊ�ɵ����̡߳�
��һ���Զ����õ��¼��õ�֪ͨʱ���ȴ����¼����߳���ֻ��һ���̱߳�Ϊ�ɵ����̡߳�
������SetEventʱ�����Խ��¼���Ϊ��֪ͨ״̬
������ResetEvent����ʱ�����Խ����¼���Ϊδ֪ͨ״̬
*/

#define THREAD_NUMS 2
HANDLE g_eventhandle = NULL;
int g_nums = 0;

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter)
{
	DWORD dw_obj = WaitForSingleObject(g_eventhandle, INFINITE);
	switch (dw_obj)
	{
	case WAIT_OBJECT_0:
	{
		for (int i = 0; i < 1000000; i++)
		{
			g_nums += 1;
		}
		SetEvent(g_eventhandle);
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
	g_eventhandle = CreateEvent(NULL,FALSE, TRUE,NULL);
	if (!g_eventhandle)
	{
		cout << "CreateEvent failed:" << endl;
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
	CloseHandle(g_eventhandle);

	return 0;
}


