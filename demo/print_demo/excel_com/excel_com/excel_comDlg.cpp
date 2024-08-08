
// excel_comDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "excel_com.h"
#include "excel_comDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Cexcel_comDlg 对话框



Cexcel_comDlg::Cexcel_comDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXCEL_COM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

Cexcel_comDlg::~Cexcel_comDlg()
{
	m_App.Quit();
	m_App.ReleaseDispatch();
	m_App = nullptr;
}

void Cexcel_comDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cexcel_comDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cexcel_comDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cexcel_comDlg 消息处理程序

BOOL Cexcel_comDlg::OnInitDialog()
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

	InitExcel();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cexcel_comDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cexcel_comDlg::OnPaint()
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
HCURSOR Cexcel_comDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 初始化Excel库
bool Cexcel_comDlg::InitExcel()
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

BOOL Cexcel_comDlg::PrintExcel(const CString& strPath)
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
	m_WorkBook.PrintOut(covOptional, covOptional, covOptional ,covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	m_WorkBook.Close(covOptional, covOptional, covOptional);
	m_Books.Close();

	return TRUE;
}


void Cexcel_comDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str(_T("C:\\Users\\13506\\Desktop\\1.xlsx"));
	PrintExcel(str);
}
