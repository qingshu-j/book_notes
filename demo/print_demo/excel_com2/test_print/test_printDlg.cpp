
// test_printDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_print.h"
#include "test_printDlg.h"
#include "afxdialogex.h"
#include <winspool.h>
#include <io.h>

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

Ctest_printDlg::~Ctest_printDlg()
{
	m_App.Quit();
	m_App.ReleaseDispatch();
	m_App = nullptr;
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
	ON_BN_CLICKED(IDC_BUTTON4, &Ctest_printDlg::OnBnClickedButton4)
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
	CArray<CString> array, array1;
	EnumPrintersName(array);
	GetDefaultPrinter(defaultName, &len);
	SetDlgItemText(IDC_EDIT1, defaultName);
	if (array.GetSize())
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	}
	InitPrintFileDir();
	InitExcel();
	
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


bool Ctest_printDlg::InitExcel()
{
	HRESULT ht;
	ht = ::CoInitialize(NULL);
	if (ht == E_INVALIDARG)
	{
		MessageBox(_T("初始化COM失败"));
	}

	//创建Execel(启动Excel)
	if (!m_App.CreateDispatch(_T("Excel.application"), nullptr))
	{
		MessageBox(_T("Error!Creat Excel Application Sever Fail!"));
		exit(1);
		return FALSE;
	}

	m_App.put_Visible(FALSE);//是否显示EXCEL
	m_App.put_DisplayFullScreen(FALSE);//设置全屏显示
	m_App.put_DisplayAlerts(FALSE);//屏蔽警告
	return TRUE;
}

void Ctest_printDlg::InitPrintFileDir()
{
	TCHAR buf[0x80] = { 0 };
	DWORD dwRet = GetPrivateProfileString(_T("PrintConfig"), _T("PrintFileDir"), NULL, buf,sizeof(TCHAR)*0x80, _T(".\\config.ini"));
	if (0 == dwRet)
	{
		MessageBox(_T("找不到文件名config.ini或区域名PrintConfig或键名PrintFileDir"));
		return;
	}
	CString strPath(buf);
	if (strPath.GetAt(strPath.GetLength()-1) != _T('\\'))
	{
		strPath += _T('\\');
	}
	SetDlgItemText(IDC_EDIT2, strPath);
}

BOOL Ctest_printDlg::PrintExcel(const CString& strPath)
{
	//InitExcel();

	m_Books = m_App.get_Workbooks();

	try
	{
		m_WorkBook = m_Books.Add(_variant_t(strPath));//打开EXCEL文件
	}
	catch (CException* e)
	{
		m_Books.Close();
		MessageBox(_T("Error!open Excel file Fail!"));
		return FALSE;
		//m_WorkBook = m_Books.Add(vtMissing);//找不到就新建一个
	}
	//保存  定义变量//
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_WorkBook.PrintOut(covOptional, covOptional, covOptional, COleVariant((BYTE)FALSE), covOptional, covOptional, covOptional, covOptional, covOptional);
	m_WorkBook.Close(covOptional, covOptional, covOptional);
	m_Books.Close();

	return TRUE;
}

BOOL Ctest_printDlg::PrintOneSheet(const CString& strPath)
{

	m_Books.AttachDispatch(m_App.get_Workbooks());
	LPDISPATCH lpDisp = NULL;
	//保存  定义变量//
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	try
	{
		lpDisp = m_Books.Open(strPath, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	}
	catch (CException* e)
	{
		m_Books.ReleaseDispatch();
		m_Books.Close();
		MessageBox(_T("Error!open Excel file Fail!"));
		return FALSE;
	}
	m_WorkBook.AttachDispatch(lpDisp);//得到Workbook  
	//sheets.AttachDispatch(m_WorkBook.get_Worksheets());//得到Worksheets  
	//lpDisp = m_WorkBook.get_ActiveSheet();//得到当前活跃sheet，如果有单元格正处于编辑状态中，此操作不能返回，会一直等待  
	//m_WorkSheet.AttachDispatch(lpDisp);
	//m_WorkBook.PrintPreview(COleVariant((BYTE)TRUE));
	m_WorkBook.PrintOut(COleVariant((BYTE)1), COleVariant((BYTE)1), covOptional, COleVariant((BYTE)FALSE), covOptional, covOptional, covOptional, covOptional, covOptional);
	m_WorkBook.ReleaseDispatch();
	m_WorkBook.Close(covOptional, covOptional, covOptional);
	m_Books.ReleaseDispatch();
	m_Books.Close();

	return TRUE;
}

void Ctest_printDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str, strFilePathName,strSN,strDir;
	GetDlgItemText(IDC_EDIT2, strDir);
	if (!strDir.GetLength())
	{
		MessageBox(_T("打印文件路径为空"));
		return;
	}
	GetDlgItemText(IDC_EDIT3, strSN);
	if (!strSN.GetLength())
	{
		MessageBox(_T("SN为空"));
		return;
	}
	CArray<CString> array1;
	CStringA strDirA = CT2A(strDir)+"*";
	GetExcelFiles(strDirA.GetBuffer(),array1);
	for (int i=0;i<array1.GetSize();i++)
	{
		if (-1 != array1[i].Find(strSN))
		{
			strFilePathName = strDir + array1[i];
			break;
		}
	}
	

	if (PrintOneSheet(strFilePathName))
	{
		str = _T("成功");
	}
	else
	{
		str = _T("失败");
	}
	//MessageBox(str);
	SetDlgItemText(IDC_EDIT3, _T(""));
}

void Ctest_printDlg::GetExcelFiles(const char* to_search,CArray<CString>& array)
{
	CString fileName;
	//const char *to_search = "C:\\Users\\13506\\Desktop\\*.*";
	long handle;//用于查找句柄
	struct _finddata_t fileinfo;//文件信息的结构体
	handle = _findfirst(to_search, &fileinfo);//第一次查找
	if (-1 == handle) return ;

	fileName = fileinfo.name;
	if (-1!=fileName.Find(_T(".xls")) || -1 != fileName.Find(_T(".xlsx")))
	{
		array.Add(fileName);
	}
	
	while (!_findnext(handle, &fileinfo))
	{
		fileName = fileinfo.name;
		if (-1 != fileName.Find(_T(".xls")) || -1 != fileName.Find(_T(".xlsx")))
		{
			array.Add(fileName);
		}
	}
	_findclose(handle);//别忘了关闭句柄
}
