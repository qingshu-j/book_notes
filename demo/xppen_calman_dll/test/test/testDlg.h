
// testDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include <vector>

/*
cmd:�·��ͽ���ָ��buff��ʡ��ǰ�����̶��ֽڣ�ֻ������6���ֽڣ�����Ҳ�����
len:�·�ָ��ȣ��̶�6
Bytes: ָ��ָ�����ָ��ȣ�����һ��ָ���Ҳ��������ĺ�6���ֽڣ�����n���򳤶�Ϊn*6
return:1 success, 0 failed
д��ָ�������ע�������ݣ���ѯ����Ҫ��ע����ѯ��Ϣֻ��ʹ�ò�ѯ������Ϣ�ӿڣ��ݲ�֧�ֵ�����Ϣ��ѯ
*/
typedef unsigned int(__cdecl *pIO)(unsigned char* cmd, unsigned int len, unsigned int* Bytes);

// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
