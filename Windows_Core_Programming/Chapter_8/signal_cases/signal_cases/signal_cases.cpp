// signal_cases.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

/*
信标的使用规则如下：
• 如果当前资源的数量大于0，则发出信标信号。
• 如果当前资源数量是0，则不发出信标信号。
• 系统决不允许当前资源的数量为负值。
• 当前资源数量决不能大于最大资源数量。
当使用信标时，不要将信标对象的使用数量与它的当前资源数量混为一谈
*/

#define THREAD_NUMS 10
#define SIGNAL_MAX_NUMS 5
HANDLE g_signalhandle = NULL;
int g_nums = 0;

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter)
{
	DWORD dw_obj = WaitForSingleObject(g_signalhandle, INFINITE);
	switch (dw_obj)
	{
	case WAIT_OBJECT_0:
	{
		for (int i = 0; i < 1000000; i++)
		{
			g_nums += 1;
		}
		ReleaseSemaphore(g_signalhandle,1,NULL);//增加信号量的计数
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
	g_signalhandle = CreateSemaphore(NULL, 1, SIGNAL_MAX_NUMS, NULL);
	if (!g_signalhandle)
	{
		cout << "CreateSemaphore failed:" << endl;
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
	CloseHandle(g_signalhandle);

	return 0;
}

