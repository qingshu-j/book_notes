#pragma once
#include<Windows.h>
extern "C"//必须这个 不然会出现链接错误
{
#include "hid/hidsdi.h"
#include "hid/hid.h"
}
#pragma comment(lib,"hid.lib")
#include "xppen.h"
typedef void (API_CALL *TABLETDATA_CALLBACK)(unsigned char *penData, int length, void *userData);//tablet数据监听

class HidTablet
{
public:
	HidTablet();
	~HidTablet();
	bool							OpenDevice(char* HidPath);														//打开设备
	BOOL							CloseDevice();																	//关闭设备
	PHID_DEVICE						GetHidDevice();																//获取设备句柄	 
	BOOL WINAPI						RegisterEvents(TABLETDATA_CALLBACK TabletCallBack, void *pthis);		//注册监听事件
	BOOL							UnregisterEvents();															//注销监听
	bool							HidGetString(unsigned int StringIndex, void * outBuffer, unsigned int length);//GetString
	bool							WriteCmmand(unsigned char *data, int length);
	BOOL							MySetFeature(unsigned char *data, int length);
	BOOL							ChangeTabletMode();															//休眠唤醒
private:
	void							*m_pThis;
	int							    m_nTabletIndex;
	PHID_DEVICE						m_pHidDevice;																 //打开的设备句柄


	HANDLE							m_hReadThread;																 //读取数据线程
	TABLETDATA_CALLBACK				m_TabletCallBack;														 //事件监听
	BOOL							m_bExitThread;																 //退出线程标识
	BOOL							OpenHidDevice(char* HidPath);												//打开HID设备
	BOOL							CloseHidDevice();															//关闭设备
	static DWORD	WINAPI			TmpReadDataThread(LPVOID lpParam);											//线程回调函数必须使用静态函数->这个中转线程
	VOID							ReadDataFunction();															//读写数据
	BOOLEAN							OpenHidDevice(IN PCHAR DevicePath, IN  BOOL HasReadAccess, IN BOOL HasWriteAccess, IN BOOL IsOverlapped, IN BOOL IsExclusive, IN BOOL GetDeviceInfo, IN OUT PHID_DEVICE  HidDevice);
	VOID							CloseHidDevice(IN PHID_DEVICE HidDevice, IN  BOOL FreeDeviceInfo);
	const TCHAR						*Hid_ErrorString(DWORD err);
	BOOL							ChangeDataFormat(int ID);
};

