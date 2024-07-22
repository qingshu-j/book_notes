#include "stdafx.h"
#include "Listener.h"
#include"Dbt.h"
#include <INITGUID.H>
#include<string>
#include <algorithm>
#include<Setupapi.h>
extern "C"
{
#include "hid/hidsdi.h"
#include "hid/hid.h"
}
using namespace std;
#pragma comment(lib,"Setupapi.lib")
DEFINE_GUID(GUID_DEVINTERFACE_HID, 0x4D1E55B2, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30);	   //定义HID接口

#ifndef _tstring
#include <tchar.h>
#ifdef UNICODE
#define _tstring std::wstring
#else
#define _tstring std::string
#endif
#endif

#ifdef DEBUG_INFO
char chout[512];
#endif


Listener::Listener()
{
	m_pThis = NULL;
}


Listener::~Listener()
{
}
BOOL	Listener::Init()
{
	return CreateHideListenWindow();
}
void    Listener::Exit()
{
	if (m_hWnd)
	{
		::PostMessage(m_hWnd, WM_DESTROY, NULL, NULL);	//销毁窗口
		m_hWnd = NULL;
	}
}
BOOL     Listener::CreateHideListenWindow()
{
	WNDCLASSEX wndclass;
	HANDLE  hThread;
	DWORD   dwTID;
	TCHAR szAppName[] = TEXT("XENCELABS_HID_HIDE_LISTEN_WINDOW");
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = PluginWinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = (HINSTANCE)GetModuleHandle(NULL);//hInstance;//
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = NULL;
	RegisterClassEx(&wndclass);

	hThread = CreateThread(NULL, 0, RegisterDeviceThread, this, 0, &dwTID);
	//WaitForSingleObject(hThread, INFINITE);//防止线程关闭	
	return TRUE;
}
//-----------------------------------------------------------------------------
//注册设备进程
//-----------------------------------------------------------------------------
DWORD WINAPI Listener::RegisterDeviceThread(LPVOID lpParameter)
{
	Listener * pHidManage = (Listener*)(lpParameter);
	pHidManage->RegisterDevice();
	return TRUE;
}
BOOL	Listener::RegisterDevice()
{
	MSG msg;
	int i = 0;
	//HWND  hWnd;
	TCHAR szAppName[] = TEXT("XENCELABS_HID_HIDE_LISTEN_WINDOW");
	DEV_BROADCAST_DEVICEINTERFACE  filter = { 0 };
	TCHAR guid_data4[8] = { 0x88,0xCB,0x0,0x11,0x11,0x0,0x0,0x30 };
	m_hWnd = CreateWindow(szAppName, TEXT("CUIDHidListen"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);
	if (NULL == m_hWnd) {

		return FALSE;
	}
	UpdateWindow(m_hWnd);
	//设置this指针
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this); //将this指针传递给窗口
	 //注册USB设备插拔通知
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	filter.dbcc_classguid = GUID_DEVINTERFACE_HID;
	if (!RegisterDeviceNotification(m_hWnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//------------------------------------------------------------------------------------
//窗口过程函数
//-------------------------------------------------------------------------------------
LRESULT CALLBACK Listener::PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Listener * pListener = NULL;
	pListener = (Listener *)GetWindowLong(hWnd, GWL_USERDATA);
	if (pListener)
		return pListener->RealWinProc(hWnd, msg, wParam, lParam);

#ifdef DEBUG_INFO_ERR
	printf(chout, sizeof(chout), "ERR:Cannot get hid listner obj, hwnd=%d\r\n", hWnd);
	OutputDebugStringA(chout);
#endif
	return DefWindowProc(hWnd, msg, wParam, lParam);

}
BOOL Listener::RealWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
	PDEV_BROADCAST_HDR pHdr;
	switch (msg)
	{

	case WM_DEVICECHANGE:
		pHdr = (PDEV_BROADCAST_HDR)lParam; //设备接入
		if (DBT_DEVICEARRIVAL == wParam)
		{
			if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
			{
				pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
				GUID guid = pDevInf->dbcc_classguid;
				if (GUID_DEVINTERFACE_HID == guid)//HID 设备
				{
					_tstring devPath = pDevInf->dbcc_name;
					transform(devPath.begin(), devPath.end(), devPath.begin(), ::toupper);
					size_t _28BD = devPath.find(_T("VID_28BD"));
					size_t _mi02 = devPath.find(_T("MI_02"));
					size_t _520A = devPath.find(_T("PID_095C"));
					size_t _520B = devPath.find(_T("PID_095D"));
					if (_28BD != string::npos  && _mi02 != string::npos)
					{
						if(_520A != string::npos || _520B != string::npos)
							m_pListenerGroup->DeviceNotify_listener((char*)devPath.c_str(), 1, m_pThis);
					}

				}
			}
		}
		else if (DBT_DEVICEREMOVECOMPLETE == wParam)
		{ //设备移除
			if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
			{
				pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
				GUID guid = pDevInf->dbcc_classguid;
				if (GUID_DEVINTERFACE_HID == guid)//HID设备
				{
					_tstring devPath = pDevInf->dbcc_name;
					transform(devPath.begin(), devPath.end(), devPath.begin(), ::toupper);
					size_t _28BD = devPath.find(_T("VID_28BD"));
					size_t _mi02 = devPath.find(_T("MI_02"));
					size_t _520A = devPath.find(_T("PID_095C"));
					size_t _520B = devPath.find(_T("PID_095D"));
					if ((_28BD != string::npos && _mi02 != string::npos))
					{
						if (_520A != string::npos || _520B != string::npos)
							m_pListenerGroup->DeviceNotify_listener((char*)devPath.c_str(), 0, m_pThis);
					}
				}
			}
		}
		return TRUE;
	}
	return TRUE;
}

BOOL  Listener::RegisterEvents(LISTENER_GROUP *pListener_group, void* pThis)
{
	m_pListenerGroup = pListener_group;
	m_pThis = pThis;
	printf("pThis:%p", pThis);
	EnmuTabeltDevice();
	return TRUE;
}
BOOL Listener::UnregisterEvents()
{
	m_pListenerGroup = NULL;
	return TRUE;
}
VOID	 Listener::EnmuTabeltDevice()
{
	bool bConncet = false;
	GUID    hidGuid;

	HidD_GetHidGuid(&hidGuid);

	TCHAR hid[256];
	HDEVINFO devinfo = SetupDiGetClassDevs(&hidGuid, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (devinfo == INVALID_HANDLE_VALUE)
	{
		return;
	}
	else
	{
		PSP_INTERFACE_DEVICE_DETAIL_DATA devDetail = NULL;
		SP_DEVICE_INTERFACE_DATA devInfoData;
		devInfoData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		for (int index = 0; SetupDiEnumInterfaceDevice(devinfo, 0, &hidGuid, index, &devInfoData) == TRUE; index++)
		{
			ULONG requiredLength = 0;
			SetupDiGetInterfaceDeviceDetail(devinfo, &devInfoData, NULL, 0, &requiredLength, NULL);//获取尺寸
			if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
			{
				devDetail = (SP_INTERFACE_DEVICE_DETAIL_DATA *)calloc(requiredLength, 1);
				devDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
				if (!SetupDiGetInterfaceDeviceDetail(devinfo, &devInfoData, devDetail, requiredLength, NULL, NULL)) //获取设备路径
				{
					free(devDetail);
					continue;
				}
				_tstring devPath = devDetail->DevicePath;
				transform(devPath.begin(), devPath.end(), devPath.begin(), ::toupper);
				size_t _28BD = devPath.find(_T("VID_28BD"));
				size_t _mi02 = devPath.find(_T("MI_02"));
				size_t _520A = devPath.find(_T("PID_095C"));
				size_t _520B = devPath.find(_T("PID_095D"));
				if ((_28BD != string::npos&& _mi02 != string::npos))
				{
					if (_520A != string::npos || _520B != string::npos)
					{
						m_pListenerGroup->DeviceNotify_listener((char*)devPath.c_str(), 1, m_pThis);
						bConncet = true;
					}

				}

				free(devDetail);
			}
		}

	}
	SetupDiDestroyDeviceInfoList(devinfo);
	if(!bConncet)
		m_pListenerGroup->DeviceNotify_listener((char*)"", 0, m_pThis);
}
