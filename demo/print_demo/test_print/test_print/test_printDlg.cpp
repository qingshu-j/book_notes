
// test_printDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_print.h"
#include "test_printDlg.h"
#include "afxdialogex.h"
#include <winspool.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HDC GetPrinterDC(void);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctest_printDlg 对话框



Ctest_printDlg::Ctest_printDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_PRINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest_printDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest_printDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ctest_printDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctest_printDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctest_printDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Ctest_printDlg 消息处理程序

BOOL Ctest_printDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//枚举打印机，设置默认打印机
	/* Need a printer DC to print to. */
	//HDC hDC = GetPrinterDC();

	WCHAR defaultName[0x20] = { 0 };
	DWORD len = 0x20;
	WCHAR defaultName2[0x20] = { 0 };
	DWORD len2 = 0x20;
	CArray<CString> array;
	EnumPrintersName(array);
	GetDefaultPrinter(defaultName, &len);
	SetDlgItemText(IDC_EDIT1, defaultName);
	if (array.GetSize())
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	}
	
	//CString strdefaultName = defaultName;
	//SetDefaultPrinter(array[1]);
	//GetDefaultPrinter(defaultName2, &len2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctest_printDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest_printDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ctest_printDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_printDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, strFilePathName;
	GetDlgItemText(IDC_EDIT2, strFilePathName);
	if (!strFilePathName.GetLength())
	{
		MessageBox(_T("打印文件路径为空"));
		return;
	}
	if ((int)ShellExecute(m_hWnd, _T("print"), strFilePathName, NULL, NULL, SW_MINIMIZE) <= 32)
	{
		str = _T("失败");
	}
	else
	{
		str = _T("成功");
	}
	MessageBox(str);
}


/*===============================*/
/* Obtain printer device context */
/* ==============================*/
HDC GetPrinterDC(void)
{
	PRINTDLG pdlg;

	/* Initialize the PRINTDLG structure. */
	memset(&pdlg, 0, sizeof(PRINTDLG));
	pdlg.lStructSize = sizeof(PRINTDLG);
	/* Set the flag to return printer DC. */
	pdlg.Flags = PD_RETURNDC;

	/* Invoke the printer dialog box. */
	PrintDlg(&pdlg);

	/* hDC member of the PRINTDLG structure contains the printer DC. */
	return pdlg.hDC;
}

void Ctest_printDlg::EnumPrintersName(CArray<CString>& array)
{
	DWORD              dwNeeded, dwReturned;
	PRINTER_INFO_4 *   pinfo4;
	EnumPrinters(PRINTER_ENUM_CONNECTIONS, NULL, 4, NULL, 0, &dwNeeded, &dwReturned);
	pinfo4 = (PRINTER_INFO_4*)malloc(dwNeeded);
	EnumPrinters(PRINTER_ENUM_CONNECTIONS, NULL, 4, (PBYTE)pinfo4, dwNeeded, &dwNeeded, &dwReturned);
	for (int i = 0; i < (int)dwReturned; i++)
	{
		array.Add(pinfo4[i].pPrinterName);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(pinfo4[i].pPrinterName);
	}
}

void Ctest_printDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_COMBO1, str);
	if (SetDefaultPrinter(str))
	{
		//success
		SetDlgItemText(IDC_EDIT1, str);
	}
	else
	{
		MessageBox(_T("失败"));
	}
}


void Ctest_printDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter("Excel文件|*.xlsx;*.xls|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR, strFilter);
	if (dlg.DoModal() != IDOK) return; // failed
	CString strFilePathName = dlg.GetPathName();
	SetDlgItemText(IDC_EDIT2, strFilePathName);
}
