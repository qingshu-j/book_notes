// xppen.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "xppen.h"
#include"Listener.h"
#include"HidTablet.h"
#include<list>
#include<map>
#include <Psapi.h>
#include"Common.h"
#include "CmdHandle.h"
#pragma comment (lib,"Psapi.lib")
#pragma warning(disable: 4996)
using namespace std;

Listener* g_pListener = NULL;
CmdHandle* g_CmdHandle = NULL;

list<HidTablet*> g_pTabletList;
map<string, HidTablet*> g_pMapTablet;
char  g_lpFilePathBuf[MAX_PATH] = { 0 };

LISTENER_GROUP*				g_pListenerGroup = NULL;
//DATA_CALLBACK				g_DataCallBack = NULL;
//DEVICE_CALLBACK				g_DeviceCallBack = NULL;
void						*g_pThis = NULL;
HANDLE g_eventHandle = NULL;
extern int g_iCount;
/*
暂时保留以前的接口，调用方式改为外部只需要调用IO即可，初始和释放相关接口在dll入口调用
*/

void API_CALL TabletCallBack(unsigned char *penData, int length, void *userData)
{
	//解析原始数据然后加工成卡曼CUI协议
	//g_DataCallBack((char*)penData, length, userData);
	g_CmdHandle->CopyRecevieBuffer(penData, length);
	g_iCount--;
	if (0==g_iCount)
	{
		SetEvent(g_eventHandle);
	}
}

void API_CALL  DevCallBack(char* devPath, short status, void *userData)
{
	string strDevPath(devPath);
	if (status == 1)
	{
		HidTablet *pTablet = new HidTablet();
		pTablet->OpenDevice(devPath);
		pTablet->RegisterEvents(TabletCallBack, g_pThis);
		g_pTabletList.push_back(pTablet);

		g_pMapTablet[strDevPath] = pTablet;

		//if (g_DeviceCallBack)
		//	g_DeviceCallBack(1, userData);
	}
	if (status == 0)
	{
		map<string, HidTablet*>::iterator iter = g_pMapTablet.find(strDevPath);
		if (iter != g_pMapTablet.end()) {
			HidTablet* pTab = iter->second;
			if (g_pTabletList.size() > 0)
			{
				pTab->CloseDevice();
				g_pTabletList.remove(pTab);
				delete pTab;
				pTab = NULL;
				g_pMapTablet.erase(iter);
			}
		}
		//删除设备
		//if (g_DeviceCallBack)
		//	g_DeviceCallBack(0, userData);
	}

}

bool	API_CALL InitLib()
{
	g_eventHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!g_eventHandle)
	{
		return false;
	}
	g_CmdHandle = new CmdHandle;
	g_pListenerGroup = new LISTENER_GROUP;
	g_pListener = new Listener;
	return g_pListener->Init();
}

void	API_CALL  ReleaseLib()
{

	if (g_CmdHandle)
	{
		delete g_CmdHandle;
		g_CmdHandle = nullptr;
	}
	if (g_pListenerGroup)
	{
		g_pListenerGroup->DeviceNotify_listener = NULL;
	}
	if (g_pListener)
	{
		g_pListener->Exit();
	}
	if (g_eventHandle)
	{
		CloseHandle(g_eventHandle);
		g_eventHandle = NULL;
	}
	//g_DataCallBack = NULL;
	g_pThis = NULL;
	//g_DeviceCallBack = NULL;
}

DllExport 	void	__stdcall		RegisterCallBacks(DEVICE_CALLBACK deviceCallBack, DATA_CALLBACK dataCallBack, void *pThis)
{
	//g_DataCallBack = dataCallBack;
	//g_DeviceCallBack = deviceCallBack;
	g_pThis = pThis;

	g_pListenerGroup->DeviceNotify_listener = DevCallBack;
	g_pListener->RegisterEvents(g_pListenerGroup, g_pThis);
}
DllExport 	void	__stdcall		 UnregisterCallBacks()
{

	//g_DataCallBack = NULL;
	//g_DeviceCallBack = NULL;

}

DllExport   bool	__stdcall		 SendCommand(const char * cmd, int length, char* &errorMsg)
{
	bool  result = false;
	//解析字符串然后转发给USB
	if (g_pTabletList.size())
	{
		result = g_pTabletList.front()->WriteCmmand((BYTE*)cmd, length);
	}
	return result;
}

bool MySetFeature(const char * cmd, int length)
{
	bool  result = false;
	//解析字符串然后转发给USB
	if (g_pTabletList.size())
	{
		result = g_pTabletList.front()->MySetFeature((BYTE*)cmd, length);
	}
	return result;
}

DllExport unsigned int	CALMAN_API_CALL IO(unsigned char* cmd, unsigned int len, unsigned int* Bytes)
{
	return g_CmdHandle->IO(cmd, len, Bytes);
}
