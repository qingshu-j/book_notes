// event_cases.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

/*
事件能够通知一个操作已经完成。有两种不同类型的事件对象。
一种是人工重置的事件，另一种是自动重置的事件。
当人工重置的事件得到通知时，等待该事件的所有线程均变为可调度线程。
当一个自动重置的事件得到通知时，等待该事件的线程中只有一个线程变为可调度线程。
当调用SetEvent时，可以将事件改为已通知状态
当调用ResetEvent函数时，可以将该事件改为未通知状态
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


