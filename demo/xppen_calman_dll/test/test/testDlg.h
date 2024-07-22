
// testDlg.h : 头文件
//

#pragma once
#include <string>
#include <vector>

/*
cmd:下发和接收指令buff，省略前两个固定字节，只需填充后6个字节，接收也是如此
len:下发指令长度，固定6
Bytes: 指针指向接收指令长度，接收一条指令长度也是有意义的后6个字节，接收n条则长度为n*6
return:1 success, 0 failed
写入指令无需关注接收数据，查询才需要关注。查询信息只能使用查询所有信息接口，暂不支持单个信息查询
*/
typedef unsigned int(__cdecl *pIO)(unsigned char* cmd, unsigned int len, unsigned int* Bytes);

// CtestDlg 对话框
class CtestDlg : public CDialogEx
{
// 构造
public:
	CtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	bool LoadDll();
	CString GetExePath();
	pIO IO;
	HMODULE m_hmodule;
	afx_msg void OnBnClickedButton2();
	void split_string(const std::string& strData, const std::string& split_ch, std::vector<std::string>& vctList);
};
