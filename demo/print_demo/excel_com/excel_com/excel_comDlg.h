
// excel_comDlg.h : ͷ�ļ�
//

#pragma once
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"


// Cexcel_comDlg �Ի���
class Cexcel_comDlg : public CDialogEx
{
// ����
public:
	Cexcel_comDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~Cexcel_comDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXCEL_COM_DIALOG };
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

	bool InitExcel();
	BOOL PrintExcel(const CString& strPath);
private:
	CApplication m_App;
	CWorkbook m_WorkBook;
	CWorkbooks m_Books;
public:
	afx_msg void OnBnClickedButton1();
};
