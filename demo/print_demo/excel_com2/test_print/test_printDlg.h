
// test_printDlg.h : ͷ�ļ�
//

#pragma once
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheetEx.h"

// Ctest_printDlg �Ի���
class Ctest_printDlg : public CDialogEx
{
// ����
public:
	Ctest_printDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~Ctest_printDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_PRINT_DIALOG };
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
	void EnumPrintersName(CArray<CString>& array);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	bool InitExcel();
	void InitPrintFileDir();
	BOOL PrintExcel(const CString& strPath);
	BOOL PrintOneSheet(const CString& strPath);
private:
	CApplication m_App;
	CWorkbook m_WorkBook;
	CWorkbooks m_Books;
	CWorksheetEx m_WorkSheet;
public:
	afx_msg void OnBnClickedButton4();
	void GetExcelFiles(const char* to_search, CArray<CString>& array);
};
