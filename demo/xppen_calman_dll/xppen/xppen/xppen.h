#pragma once
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 XPPEN_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// XPPEN_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。


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
cmd:下发和接收指令buff，省略前两个固定字节，只需填充后6个字节，接收也是如此
len:下发指令长度，固定6
Bytes: 指针指向接收指令长度，接收一条指令长度也是有意义的后6个字节，接收n条则长度为n*6
return:1 success, 0 failed
写入指令无需关注接收数据，查询才需要关注。查询信息只能使用查询所有信息接口，暂不支持单个信息查询
unsigned char cmd[0x20] = { 0 };
cmd[1] = 0xf0;
int len = 6;
unsigned int bytes = 0;
IO(cmd, len, &bytes);

设置sRGB
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
