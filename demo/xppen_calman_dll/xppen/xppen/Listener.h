#pragma once
#include<Windows.h>
typedef void (CALLBACK *DEVICESNOTIFY_CALLBACK)(char* devPath, short status, void *userData);//Hid监听 status 0断开 1连接
 
typedef struct tagLISTENER_GROUP {
	DEVICESNOTIFY_CALLBACK					DeviceNotify_listener;//HID监听
 
} LISTENER_GROUP;

class Listener
{
public:
	Listener(void);
	~Listener(void);
	BOOL						Init();
	BOOL  				        RegisterEvents(LISTENER_GROUP *Listener_group, void* pThis);												//注册监听事件
	BOOL						UnregisterEvents();													//注销监听
	void						Exit();
private:
	BOOL						CreateHideListenWindow();																			//创建监视窗口
	static LRESULT CALLBACK	    PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);						//临时中转的窗口过程
	BOOL						RealWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);										//实际的窗口过程
	static DWORD WINAPI			RegisterDeviceThread(LPVOID lpParameter);															//注册设备线程 中转	
	BOOL						RegisterDevice();																					//实际注册窗口

	VOID						EnmuTabeltDevice();
	LISTENER_GROUP				*m_pListenerGroup;																					//
	HWND						m_hWnd;
	//窗口句柄
	void*                       m_pThis;
};

