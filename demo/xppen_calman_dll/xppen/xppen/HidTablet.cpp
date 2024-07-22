#include "stdafx.h"
#include "HidTablet.h"
#include <tchar.h>

HidTablet::HidTablet()
{
	m_pHidDevice = NULL;
	m_bExitThread = FALSE;

	m_TabletCallBack = NULL;
}


HidTablet::~HidTablet()
{
	m_bExitThread = TRUE;
	if (m_pHidDevice)
	{
		free(m_pHidDevice);
		m_pHidDevice = NULL;
	}
}
//打开HID设备
BOOL  HidTablet::OpenHidDevice(char* path)
{

	BOOL bResult = FALSE;
	m_pHidDevice = (PHID_DEVICE)malloc(sizeof(*m_pHidDevice));
	if (m_pHidDevice == NULL)
	{
		return FALSE;
	}
	memset(m_pHidDevice, 0, sizeof(HID_DEVICE));
	BOOL  bIsOpened = FALSE;


	if (OpenHidDevice(path, TRUE, TRUE, TRUE, FALSE, TRUE, m_pHidDevice))
	{

		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;

		DWORD derror = GetLastError();

		free(m_pHidDevice);
		m_pHidDevice = NULL;
	}

	return bResult;
}

BOOLEAN	HidTablet::OpenHidDevice(
	IN       PCHAR          DevicePath,
	IN       BOOL           HasReadAccess,
	IN       BOOL           HasWriteAccess,
	IN       BOOL           IsOverlapped,
	IN       BOOL           IsExclusive,
	IN       BOOL           GetDeviceInfo,
	IN OUT   PHID_DEVICE    HidDevice)
{
	DWORD   accessFlags = 0;
	DWORD   sharingFlags = 0;
	SECURITY_DESCRIPTOR  sd;
	SECURITY_ATTRIBUTES  sa;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

	sa.lpSecurityDescriptor = &sd;
	sa.nLength = 0xC;
	sa.bInheritHandle = TRUE;
	HidDevice->DevicePath = (PCHAR)malloc(strlen(DevicePath) + 1);
	if (NULL == HidDevice->DevicePath)
	{
		return (FALSE);
	}
	strcpy_s(HidDevice->DevicePath, strlen(DevicePath) + 1, DevicePath);
	if (HasReadAccess)
	{
		accessFlags |= GENERIC_READ;
	}
	if (HasWriteAccess)
	{
		accessFlags |= GENERIC_WRITE;
	}
	if (!IsExclusive)
	{
		sharingFlags = FILE_SHARE_READ | FILE_SHARE_WRITE;
	}
	HidDevice->HidDevice = CreateFileA(DevicePath,
		accessFlags,
		sharingFlags,
		&sa,        // no SECURITY_ATTRIBUTES structure
		OPEN_EXISTING, // No special create flags
		IsOverlapped ? FILE_FLAG_OVERLAPPED : 0,
		NULL);       // No template file
	if (INVALID_HANDLE_VALUE == HidDevice->HidDevice)
	{
		sharingFlags = GetLastError();

		//UgPrintf("OpenHidDeviceFAILED !CreateFileA error GetLastError() %d \n",sharingFlags);
		free(HidDevice->DevicePath);
		return FALSE;
	}
	HidDevice->OpenedForRead = HasReadAccess;
	HidDevice->OpenedForWrite = HasWriteAccess;
	HidDevice->OpenedOverlapped = IsOverlapped;
	HidDevice->OpenedExclusive = IsExclusive;

	if (GetDeviceInfo)
	{
		if (!HidD_GetPreparsedData(HidDevice->HidDevice, &HidDevice->Ppd))
		{
			free(HidDevice->DevicePath);
			CloseHandle(HidDevice->HidDevice);
			return FALSE;
		}
		if (!HidD_GetAttributes(HidDevice->HidDevice, &HidDevice->Attributes))
		{
			free(HidDevice->DevicePath);
			CloseHandle(HidDevice->HidDevice);
			HidD_FreePreparsedData(HidDevice->Ppd);
			return FALSE;
		}
		if (!HidP_GetCaps(HidDevice->Ppd, &HidDevice->Caps))
		{
			free(HidDevice->DevicePath);
			CloseHandle(HidDevice->HidDevice);
			HidD_FreePreparsedData(HidDevice->Ppd);
			return FALSE;
		}

	}
	return (TRUE);
}

BOOL	HidTablet::CloseHidDevice()//关闭设备
{
	BOOL  bResult = TRUE;
	CloseHidDevice(m_pHidDevice, TRUE);
	return bResult;
}
VOID  HidTablet::CloseHidDevice(IN  PHID_DEVICE  HidDevice, IN  BOOL FreeDeviceInfo)
{
	if (HidDevice == NULL)
		return;
	if (HidDevice->DevicePath[0] != '\0')
		free(HidDevice->DevicePath);
	if (INVALID_HANDLE_VALUE != HidDevice->HidDevice)
	{
		CloseHandle(HidDevice->HidDevice);
	}
	//
	// Only free these structure, if have a handle to an non-overlapped device
	//
	if (FreeDeviceInfo)
	{
		if (NULL != HidDevice->Ppd)
		{
			HidD_FreePreparsedData(HidDevice->Ppd);
		}
		if (NULL != HidDevice->InputReportBuffer)
		{
			free(HidDevice->InputReportBuffer);
		}
		if (NULL != HidDevice->InputData)
		{
			free(HidDevice->InputData);
		}
		if (NULL != HidDevice->InputButtonCaps)
		{
			free(HidDevice->InputButtonCaps);
		}
		if (NULL != HidDevice->InputValueCaps)
		{
			free(HidDevice->InputValueCaps);
		}
		if (NULL != HidDevice->OutputReportBuffer)
		{
			free(HidDevice->OutputReportBuffer);
		}
		if (NULL != HidDevice->OutputData)
		{
			free(HidDevice->OutputData);
		}
		if (NULL != HidDevice->OutputButtonCaps)
		{
			free(HidDevice->OutputButtonCaps);
		}
		if (NULL != HidDevice->OutputValueCaps)
		{
			free(HidDevice->OutputValueCaps);
		}
		if (NULL != HidDevice->FeatureReportBuffer)
		{
			free(HidDevice->FeatureReportBuffer);
		}
		if (NULL != HidDevice->FeatureData)
		{
			free(HidDevice->FeatureData);
		}
		if (NULL != HidDevice->FeatureButtonCaps)
		{
			free(HidDevice->FeatureButtonCaps);
		}
		if (NULL != HidDevice->FeatureValueCaps)
		{
			free(HidDevice->FeatureValueCaps);
		}
	}
	return;
}
const TCHAR *HidTablet::Hid_ErrorString(DWORD err)
{
	switch (err)
	{
	case    6: // 句柄无效
		return _T("Invalid handle");
	case   23: // 数据错误（循环冗余码检查）
		return _T("Data error");
	case   87: // 参数错误
		return _T("Invaid paramter or reposrt ID");
	case 1784: // 用户提供的buffer无效    
		return _T("Invalid buffer");
	default:
		return _T("Unknown error");
	}
}

PHID_DEVICE			HidTablet::GetHidDevice()					//获取设备句柄
{
	if (m_pHidDevice)
		return m_pHidDevice;
	else
		return NULL;
}
//BOOL			HidTablet::FillDeviceAttribute()
//{
//	if (m_pHidDevice == NULL)
//		return FALSE;
//	UCHAR data[64] = { 0 };
//	ULONG MaxXPos, MaxYPos, MaxPress, LDPI;
//
//	HidD_GetIndexedString(m_pHidDevice->HidDevice, 100, data, 64);//发送100字符串数据 获取信息 切换成驱动数据和自定义数据
//													 
//	MaxXPos = data[0] + data[1] * 0x100 + data[10] * 0x10000;
//	MaxYPos = data[2] + data[3] * 0x100 + data[11] * 0x10000;
//	MaxPress = data[6] + data[7] * 0x100;
//	LDPI = data[8] + data[9] * 0x100;
//	m_DeviceAttribute.MaxX = MaxXPos;
//	m_DeviceAttribute.MaxY = MaxYPos;
//	m_DeviceAttribute.MaxPressure = MaxPress;
//	if (LDPI == 0)
//		LDPI = 5080;
//	m_DeviceAttribute.LDPI = LDPI;
//	m_DeviceAttribute.Width = (MaxXPos * 100 / LDPI);
//	m_DeviceAttribute.Height = (MaxYPos * 100 / LDPI);
//	if (m_pHidDevice->HidDevice)
//	{
//		wchar_t wstr[64] = { 0 };
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 1, wstr, 64);//获取OEM厂商型号
//		size_t slen = wcslen(wstr);
//		wcstombs(m_DeviceAttribute.Manufacturer, wstr, slen * 2);
//
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 2, wstr, 64);//获取数位板名称
//		slen = wcslen(wstr);
//		wcstombs(m_DeviceAttribute.ProductName, wstr, slen * 2);
//
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 3, wstr, 64);//获取序列号 
//		slen = wcslen(wstr);
//		wcstombs(m_DeviceAttribute.SerialNumber, wstr, slen * 2);
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 4, wstr, 64);//获取主控版本
//		slen = wcslen(wstr);
//		wcstombs(m_DeviceAttribute.ICVersion, wstr, slen * 2);
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 5, wstr, 64);//获取日期
//		slen = wcslen(wstr);
//		wcstombs(m_DeviceAttribute.ICData, wstr, slen * 2);
//
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 110, m_DeviceAttribute.DeviceType, MAX_MYPATH_SIZE);//获取设备类型
//		HidD_GetIndexedString(m_pHidDevice->HidDevice, 131, m_DeviceAttribute.Version, MAX_MYPATH_SIZE);//获取版本
//
//
//	}
//	return TRUE;
//}

BOOL		HidTablet::ChangeDataFormat(int ID)
{
	BOOL      bResult = FALSE;
	if (m_pHidDevice == NULL)
		return bResult;

	HIDP_CAPS					Capabilities;
	PHIDP_PREPARSED_DATA         HidParsedData = NULL;
	HidD_GetPreparsedData(m_pHidDevice->HidDevice, &HidParsedData);
	if (HidParsedData == NULL)
		return FALSE;
	HidP_GetCaps(HidParsedData, &Capabilities);
	BYTE* CmdData = (BYTE *)malloc(Capabilities.OutputReportByteLength);
	HidD_FreePreparsedData(HidParsedData);
	memset(CmdData, 0, Capabilities.OutputReportByteLength);

	CmdData[0] = 0x02;
	CmdData[1] = 0xb0;//0xb0;

	CmdData[2] = ID;// 1-UC -tablePC 2-免驱 3-2种都发
	DWORD Rtn;
	OVERLAPPED  ol = { 0 };
	ULONG  ErrorCode = 0;
	ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_pHidDevice->HidDevice)
	{
		WriteFile(m_pHidDevice->HidDevice, CmdData, Capabilities.OutputReportByteLength, &Rtn, &ol);
		bResult = WaitForSingleObject(ol.hEvent, 300);
		if (bResult == WAIT_TIMEOUT || bResult == WAIT_ABANDONED)
		{
			CancelIo(&m_pHidDevice->HidDevice);

			CloseHandle(ol.hEvent);
			return bResult;
		}
		else if (bResult == WAIT_OBJECT_0)
		{

			CloseHandle(ol.hEvent);
			return TRUE;
		}
	}
	return bResult;
}
DWORD		WINAPI	HidTablet::TmpReadDataThread(LPVOID lpParam)
{
	HidTablet *pThis = (HidTablet*)lpParam;
	pThis->ReadDataFunction();
	return 1;
}
VOID	HidTablet::ReadDataFunction()
{
	OVERLAPPED					ol = { 0 };
	ULONG						ErrorCode = 0;
	DWORD						dwReturned = 0;
	HIDP_CAPS					Capabilities;
	PHIDP_PREPARSED_DATA         HidParsedData = NULL;
	BYTE						*uInputData = NULL;

	HANDLE                      ReportEvent;
	BOOL						bReturn;

	HidD_GetPreparsedData(m_pHidDevice->HidDevice, &HidParsedData);
	if (HidParsedData == NULL)
		return;
	HidP_GetCaps(HidParsedData, &Capabilities);
	uInputData = (BYTE *)malloc(Capabilities.InputReportByteLength);
	HidD_FreePreparsedData(HidParsedData);
	ReportEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ol.hEvent = ReportEvent;

	printf("HID读取线程启动中\n");
	while (!m_bExitThread)
	{
		memset(uInputData, 0, Capabilities.InputReportByteLength);
		if (m_pHidDevice)
		{
			bReturn = ReadFile(m_pHidDevice->HidDevice, uInputData, Capabilities.InputReportByteLength, &dwReturned, &ol);	//读取数据&ol
		}
		DWORD dwRt = WaitForSingleObject(ReportEvent, 1000);//	
		if (dwRt == WAIT_OBJECT_0)
		{
			if (m_TabletCallBack)
			{
				//解析转换
				m_TabletCallBack(uInputData, Capabilities.InputReportByteLength, m_pThis);
			}

		}
		ResetEvent(ReportEvent);
	}
	printf("HID读取线程关闭。\n");
	free(uInputData);
	uInputData = NULL;
}
BOOL WINAPI		HidTablet::RegisterEvents(TABLETDATA_CALLBACK TabletCallBack, void *pThis)
{
	m_TabletCallBack = TabletCallBack;
	m_pThis = pThis;
	return TRUE;
}
BOOL			HidTablet::UnregisterEvents()													//注销监听
{
	m_TabletCallBack = NULL;
	return TRUE;
}
bool HidTablet::HidGetString(unsigned int StringIndex, void * outBuffer, unsigned int length)
{
	if (m_pHidDevice == NULL)
		return false;
	if (m_pHidDevice->HidDevice)
	{
		HidD_GetIndexedString(m_pHidDevice->HidDevice, StringIndex, outBuffer, length);//获取OEM厂商型号
	}
	return false;
}
BOOL			HidTablet::CloseDevice()
{
	m_bExitThread = TRUE;
	CloseHidDevice();
	UnregisterEvents();
	return TRUE;

}
bool			HidTablet::OpenDevice(char* HidPath)
{
	if (!OpenHidDevice(HidPath))
	{
		printf("OpenHidDevice失败.\n");

		return false;
	}
	//ChangeTabletMode();
	m_hReadThread = CreateThread(0, 0, TmpReadDataThread, this, 0, NULL);		//TmpReadDataThread 读取事件线程
	return true;
}

BOOL		HidTablet::ChangeTabletMode()
{
	ChangeDataFormat(4);
	return TRUE;
}
bool	HidTablet::WriteCmmand(unsigned char *data, int length)
{
	bool      bResult = false;
	if (m_pHidDevice == NULL)
		return bResult;
	OVERLAPPED  ol = { 0 };
	ULONG  ErrorCode = 0;
	ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_pHidDevice->HidDevice)
	{
		DWORD Rtn=0;

		WriteFile(m_pHidDevice->HidDevice, data, length, &Rtn, &ol);
		int rt = WaitForSingleObject(ol.hEvent, 500);
		if (rt == WAIT_TIMEOUT || rt == WAIT_ABANDONED)
		{
			CancelIo(&m_pHidDevice->HidDevice);

			CloseHandle(ol.hEvent);
			return false;
		}
		else if (rt == WAIT_OBJECT_0)
		{

			bResult = true;
			CloseHandle(ol.hEvent);
			return true;
		}
	}
	return bResult;
}

BOOL	HidTablet::MySetFeature(unsigned char *data, int length)
{
	BOOL      bResult = FALSE;
	if (m_pHidDevice == NULL)
		return bResult;
	if (m_pHidDevice->HidDevice)
	{
		bResult = HidD_SetFeature(m_pHidDevice->HidDevice, data, length);
	}
	return bResult;
}
