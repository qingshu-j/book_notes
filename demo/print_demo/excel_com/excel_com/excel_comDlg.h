
// excel_comDlg.h : 头文件
//

#pragma once
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"


// Cexcel_comDlg 对话框
class Cexcel_comDlg : public CDialogEx
{
// 构造
public:
	Cexcel_comDlg(CWnd* pParent = NULL);	// 标准构造函数
	~Cexcel_comDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXCEL_COM_DIALOG };
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

	bool InitExcel();
	BOOL PrintExcel(const CString& strPath);
private:
	CApplication m_App;
	CWorkbook m_WorkBook;
	CWorkbooks m_Books;
public:
	afx_msg void OnBnClickedButton1();
};
