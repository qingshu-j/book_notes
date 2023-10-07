// key_code_snippet_cases.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

/*
线程的同步-关键代码段
原理：
•如果没有线程访问该资源，EnterCriticalSection便更新成员变量，以指明调用线程已被赋予访问权并立即返回，使该线程能够继续运行（访问该资源）。
•如果成员变量指明，调用线程已经被赋予对资源的访问权，那么EnterCriticalSection便更新这些变量，以指明调用线程多少次被赋予访问权并立即返回，使该线程能够继续运行。
这种情况很少出现，并且只有当线程在一行中两次调用EnterCriticalSection而不影响对LeaveCriticalSection的调用时，才会出现这种情况。
•如果成员变量指明，一个线程（除了调用线程之外）已被赋予对资源的访问权，那么EnerCriticalSection将调用线程置于等待状态。这种情况是极好的，因为等待的线程不会浪费任何CPU时间。
系统能够记住该线程想要访问该资源并且自动更新CRITICAL_SECTION的成员变量，一旦目前访问该资源的线程调用LeaveCriticalSection函数，该线程就处于可调度状态。

TryEnterCriticalSection函数决不允许调用线程进入等待状态。相反，它的返回值能够指明调用线程是否能够获得对资源的访问权。
因此，如果TryEnterCriticalSection发现该资源已经被另一个线程访问，它就返回FALSE。在其他所有情况下，它均返回TRUE。
运用这个函数，线程能够迅速查看它是否可以访问某个共享资源，如果不能访问，那么它可以继续执行某些其他操作，而不必进行等待。


非常有用的提示和技巧：
1.每个共享资源使用一个CRITICAL_SECTION变量
2.不要长时间运行关键代码段
*/

#define THREAD_NUMS 2
CRITICAL_SECTION g_cs;
int g_nums = 0;

DWORD WINAPI ThreadFunc(LPVOID lpThreadParameter)
{
	EnterCriticalSection(&g_cs);
	for (int i = 0; i<1000000; i++)
	{	
		g_nums += 1;
	}
	LeaveCriticalSection(&g_cs);
	return 0L;
}


int main()
{
	InitializeCriticalSection(&g_cs);
	HANDLE handle[THREAD_NUMS];
	DWORD starttime = GetTickCount();
	for (int i = 0;i<THREAD_NUMS;i++)
	{
		handle[i] = CreateThread(NULL, 0, ThreadFunc,NULL,0,NULL);
	}
	DWORD dw_obj = WaitForMultipleObjects(THREAD_NUMS, handle, TRUE, INFINITE);
	DeleteCriticalSection(&g_cs);
	cout << "time:" << GetTickCount() - starttime <<"ms."<< endl;
	switch (dw_obj)
	{
	case WAIT_OBJECT_0:
	{
		for (int i = 0; i < THREAD_NUMS; i++)
		{
			CloseHandle(handle[i]);
		}
		cout <<"g_nums:" <<g_nums << endl;
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


    return 0;
}

