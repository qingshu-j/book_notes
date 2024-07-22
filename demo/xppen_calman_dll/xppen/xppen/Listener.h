#pragma once
#include<Windows.h>
typedef void (CALLBACK *DEVICESNOTIFY_CALLBACK)(char* devPath, short status, void *userData);//Hid���� status 0�Ͽ� 1����
 
typedef struct tagLISTENER_GROUP {
	DEVICESNOTIFY_CALLBACK					DeviceNotify_listener;//HID����
 
} LISTENER_GROUP;

class Listener
{
public:
	Listener(void);
	~Listener(void);
	BOOL						Init();
	BOOL  				        RegisterEvents(LISTENER_GROUP *Listener_group, void* pThis);												//ע������¼�
	BOOL						UnregisterEvents();													//ע������
	void						Exit();
private:
	BOOL						CreateHideListenWindow();																			//�������Ӵ���
	static LRESULT CALLBACK	    PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);						//��ʱ��ת�Ĵ��ڹ���
	BOOL						RealWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);										//ʵ�ʵĴ��ڹ���
	static DWORD WINAPI			RegisterDeviceThread(LPVOID lpParameter);															//ע���豸�߳� ��ת	
	BOOL						RegisterDevice();																					//ʵ��ע�ᴰ��

	VOID						EnmuTabeltDevice();
	LISTENER_GROUP				*m_pListenerGroup;																					//
	HWND						m_hWnd;
	//���ھ��
	void*                       m_pThis;
};

