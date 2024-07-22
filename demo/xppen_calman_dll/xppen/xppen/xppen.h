#pragma once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� XPPEN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// XPPEN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�


#ifdef _WIN32
#define API_CALL __stdcall
#define CALMAN_API_CALL __cdecl
#ifdef XPPEN_EXPORTS
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C" __declspec(dllimport)
#endif
#else
#define API_CALL /**< API call macro */
#define DllExport
#endif
/*
cmd:�·��ͽ���ָ��buff��ʡ��ǰ�����̶��ֽڣ�ֻ������6���ֽڣ�����Ҳ�����
len:�·�ָ��ȣ��̶�6
Bytes: ָ��ָ�����ָ��ȣ�����һ��ָ���Ҳ��������ĺ�6���ֽڣ�����n���򳤶�Ϊn*6
return:1 success, 0 failed
д��ָ�������ע�������ݣ���ѯ����Ҫ��ע����ѯ��Ϣֻ��ʹ�ò�ѯ������Ϣ�ӿڣ��ݲ�֧�ֵ�����Ϣ��ѯ
unsigned char cmd[0x20] = { 0 };
cmd[1] = 0xf0;
int len = 6;
unsigned int bytes = 0;
IO(cmd, len, &bytes);

����sRGB
unsigned char cmd[0x20] = { 0 };
cmd[0] = 1;
cmd[1] = 1;
cmd[2] = 1;
cmd[4] = 2;
int len = 6;
unsigned int bytes = 0;
IO(cmd, len, &bytes);
*/
DllExport   unsigned int	CALMAN_API_CALL		 IO(unsigned char* cmd, unsigned int len, unsigned int* Bytes);



typedef void (API_CALL *DATA_CALLBACK)(char *response, int length, void *userData);
typedef void (API_CALL *DEVICE_CALLBACK)(short status, void *userData);
DllExport	bool	API_CALL  		 InitLib();
DllExport 	void	API_CALL		 ReleaseLib();
DllExport 	void	API_CALL		 RegisterCallBacks(DEVICE_CALLBACK deviceCallBack, DATA_CALLBACK dataCallBack, void *pThis);
DllExport	void	API_CALL		 UnregisterCallBacks();
DllExport   bool	API_CALL		 SendCommand(const char * cmd, int length, char* &errorMsg);
bool MySetFeature(const char * cmd, int length);
