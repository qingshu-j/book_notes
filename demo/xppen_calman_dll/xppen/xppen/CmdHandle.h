#pragma once
#include <string>
#include <vector>
#include <map>
class CmdHandle
{
public:
	CmdHandle();
	~CmdHandle();
	void CopyRecevieBuffer(unsigned char* recevieBuffer, int len);
	unsigned int IO(unsigned char* cmd, unsigned int len, unsigned int* Bytes);
	bool HandleCmd(unsigned char* cmd, unsigned int len, unsigned int* Bytes);
	bool do_get(unsigned char* cmdsrc, unsigned int len, unsigned char* p, unsigned int* Bytes);
	bool do_set(unsigned char* cmdsrc, unsigned int len, unsigned char* p, unsigned int* Bytes);
	static void split_string(const std::string& strData, const std::string& split_ch, std::vector<std::string>& vctList);
	void writelog_cmd(unsigned char* cmd, int len, int type);
	void clear_g_revData();
private:
	unsigned char* m_recevieData;
	int m_recevieDataLen;
};

