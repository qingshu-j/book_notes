#include "stdafx.h"
#include "CmdHandle.h"
#include "xppen.h"
#include <fstream>
#include <vector>
#include <io.h>
#include <direct.h>
#include <time.h>
#pragma warning(disable: 4996)
using namespace std;

int g_iCount = 0;
extern HANDLE g_eventHandle;
void writelog(const std::string& str,int type);

CmdHandle::CmdHandle()
{
	m_recevieData = new unsigned char[0x400];
	m_recevieDataLen = 0;
}


CmdHandle::~CmdHandle()
{
	if (m_recevieData)
	{
		delete[] m_recevieData;
		m_recevieData = NULL;
	}
}


void CmdHandle::CopyRecevieBuffer(unsigned char* recevieBuffer, int len)
{
	memcpy(m_recevieData+ m_recevieDataLen, recevieBuffer, len);
	m_recevieDataLen += len;
}

unsigned int CmdHandle::IO(unsigned char* cmd, unsigned int len, unsigned int* Bytes)
{
	if (len < 2)
	{
		return 0;
	}
	return HandleCmd(cmd, len, Bytes) ? 1 : 0;
}

bool CmdHandle::HandleCmd(unsigned char* cmd, unsigned int len, unsigned int* Bytes)
{
	bool bRet = false;
	unsigned char* cmdsrc = new unsigned char[len+2];
	memset(cmdsrc, 0, len + 2);
	cmdsrc[0] = 0x02;
	cmdsrc[1] = 0xb5;
	memcpy(cmdsrc + 2, cmd, len);
	memset(cmd, 0, len);
	*Bytes = 0;
	unsigned char*p = cmd;

	if (1 == cmdsrc[2])
	{
		//write
		bRet = do_set(cmdsrc, len + 2,p, Bytes);
	}
	else if (0 == cmdsrc[2])
	{
		//read
		bRet = do_get(cmdsrc, len + 2, p, Bytes);
	}
	delete[] cmdsrc;
	return bRet;
}


bool CmdHandle::do_get(unsigned char* cmdsrc, unsigned int len, unsigned char* p, unsigned int* Bytes)
{
	char errmsg[0x100] = { 0 };
	char* perrmsg = errmsg;
	BYTE newcmd[14] = { 0 };
	memcpy(newcmd, cmdsrc, len);
	writelog_cmd(cmdsrc, len, 3);
	clear_g_revData();
	bool bRet = SendCommand((char*)newcmd, 14, perrmsg);
	if (!bRet)
	{
		return bRet;
	}

	g_iCount = 1;
	if (newcmd[3] == 0xf0)//查询所有信息
	{
		g_iCount = 3;
	}
	int iCount = g_iCount;//接收数据条数
	DWORD dwObj = WaitForSingleObject(g_eventHandle, 1000);
	switch (dwObj)
	{
	case WAIT_OBJECT_0:
	{
		if (m_recevieDataLen > 7)
		{
			for (int i=0;i<iCount;i++)
			{
				memcpy(p + i * 6, m_recevieData + 2+i*14, 6);
				*Bytes += 6;//根据协议取有效数据8个字节即可，忽略头两个字节，6个
			}
		}
		ResetEvent(g_eventHandle);
	}
	break;
	default:
		break;
	}

	return bRet;
}

bool CmdHandle::do_set(unsigned char* cmdsrc, unsigned int len, unsigned char* p, unsigned int* Bytes)
{
	char errmsg[0x100] = { 0 };
	char* perrmsg = errmsg;
	BYTE newcmd[14] = { 0 };
	memcpy(newcmd, cmdsrc, len);
	writelog_cmd(cmdsrc, len, 3);
	return SendCommand((char*)newcmd, 14, perrmsg);
}

void CmdHandle::split_string(const std::string& strData, const std::string& split_ch, std::vector<std::string>& vctList)
{
	int startPos = 0;
	while (true)
	{
		int pos = strData.find(split_ch, startPos);
		if (pos != -1)
		{
			vctList.push_back(strData.substr(startPos, pos - startPos));
			startPos = pos + 1;
		}
		else
		{
			vctList.push_back(strData.substr(startPos));
			break;
		}
	}
}

void CmdHandle::writelog_cmd(unsigned char* cmd,int len,int type)
{
	int cmdLen = 3 * len + 100;
	char* chcmd = new char[cmdLen];
	memset(chcmd, 0, cmdLen);
	for (int i = 0;i<len;i++)
	{
		sprintf(chcmd+i*3, "%02X ", cmd[i]);
	}
	string strdata(chcmd);
	delete[] chcmd;
	writelog(strdata, type);
}

void writelog(const std::string& str,int type)
{
	char* path = getenv("APPDATA");
	if (!path)
	{
		return;
	}
	string strPath(path);
	strPath += "\\ugee";
	if (access(strPath.c_str(),0))
	{
		mkdir(strPath.c_str());
	}
	strPath += "\\xlabs.log";
	time_t t = time(0);
	tm* ptm = localtime(&t);
	
	string strTip;
	switch (type)
	{
	case 0:
		strTip = "calman to dll";
		break;
	case 1:
		strTip = "dll to calman";
		break;
	case 2:
		strTip = "dev to dll";
		break;
	case 3:
		strTip = "dll to dev";
		break;
	default:
		break;
	}

	char chTime[0x40] = { 0 };
	sprintf(chTime, "%d%02d%02d-%02d:%02d:%02d %s:", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, strTip.c_str());
	fstream fs;
	fs.open(strPath.c_str(), fs.out|fs.app);
	fs << chTime<< str<<endl;
	fs.close();
}

void CmdHandle::clear_g_revData()
{
	memset(m_recevieData, 0, 0x400);
	m_recevieDataLen = 0;
}