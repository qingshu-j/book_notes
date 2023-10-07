// mutex_cases.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


using namespace std;

/*
ID用于标识系统中的哪个线程当前拥有互斥对象，递归计数器用于指明该线程拥有互斥对象的次数。
互斥对象（mutex）内核对象能够确保线程拥有对单个资源的互斥访问权。
通过调用一个等待函数，并传递负责保护资源的互斥对象的句柄，线程就能够获得对共享
资源的访问权。在内部，等待函数要检查线程的ID，以了解它是否是0（互斥对象发出通知信
号）。如果线程ID是0，那么该线程ID被设置为调用线程的ID，递归计数器被设置为1，同时，
调用线程保持可调度状态。
如果等待函数发现ID不是0（不发出互斥对象的通知信号），那么调用线程便进入等待状态。
系统将记住这个情况，并且在互斥对象的ID重新设置为0时，将线程ID设置为等待线程的ID，
将递归计数器设置为1，并且允许等待线程再次成为可调度线程。与所有情况一样，对互斥内
核对象进行的检查和修改都是以原子操作方式进行的。
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


