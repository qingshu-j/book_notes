#pragma once
#include<Windows.h>
extern "C"//������� ��Ȼ��������Ӵ���
{
#include "hid/hidsdi.h"
#include "hid/hid.h"
}
#pragma comment(lib,"hid.lib")
#include "xppen.h"
typedef void (API_CALL *TABLETDATA_CALLBACK)(unsigned char *penData, int length, void *userData);//tablet���ݼ���

class HidTablet
{
public:
	HidTablet();
	~HidTablet();
	bool							OpenDevice(char* HidPath);														//���豸
	BOOL							CloseDevice();																	//�ر��豸
	PHID_DEVICE						GetHidDevice();																//��ȡ�豸���	 
	BOOL WINAPI						RegisterEvents(TABLETDATA_CALLBACK TabletCallBack, void *pthis);		//ע������¼�
	BOOL							UnregisterEvents();															//ע������
	bool							HidGetString(unsigned int StringIndex, void * outBuffer, unsigned int length);//GetString
	bool							WriteCmmand(unsigned char *data, int length);
	BOOL							MySetFeature(unsigned char *data, int length);
	BOOL							ChangeTabletMode();															//���߻���
private:
	void							*m_pThis;
	int							    m_nTabletIndex;
	PHID_DEVICE						m_pHidDevice;																 //�򿪵��豸���


	HANDLE							m_hReadThread;																 //��ȡ�����߳�
	TABLETDATA_CALLBACK				m_TabletCallBack;														 //�¼�����
	BOOL							m_bExitThread;																 //�˳��̱߳�ʶ
	BOOL							OpenHidDevice(char* HidPath);												//��HID�豸
	BOOL							CloseHidDevice();															//�ر��豸
	static DWORD	WINAPI			TmpReadDataThread(LPVOID lpParam);											//�̻߳ص���������ʹ�þ�̬����->�����ת�߳�
	VOID							ReadDataFunction();															//��д����
	BOOLEAN							OpenHidDevice(IN PCHAR DevicePath, IN  BOOL HasReadAccess, IN BOOL HasWriteAccess, IN BOOL IsOverlapped, IN BOOL IsExclusive, IN BOOL GetDeviceInfo, IN OUT PHID_DEVICE  HidDevice);
	VOID							CloseHidDevice(IN PHID_DEVICE HidDevice, IN  BOOL FreeDeviceInfo);
	const TCHAR						*Hid_ErrorString(DWORD err);
	BOOL							ChangeDataFormat(int ID);
};

