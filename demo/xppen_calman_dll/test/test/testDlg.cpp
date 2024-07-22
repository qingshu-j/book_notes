
// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
#define DLL_NAME _T("xppen.dll")

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


// CtestDlg 对话框



CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
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

	LoadDll();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestDlg::OnPaint()
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
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	读所有信息：	  00,f0,00,00,00,00

	设置color-色域：  01,01,01,00,xx（01:aRGB,02:sRGB,04:DCIP3,0a:NTSC）,00
	设置color-色温：  01,01,02,00,xx（01:5000K,03:6500K,04:7500K,05:9300K）,00
	设置color-自定义：01,01,03,01,xx（01:R,02:G,03:B）,xx（0-100）
	设置亮度：		  01,03,00,00,亮度值xx（0-100）,00
	设置亮度：		  01,04,00,00,对比度xx（0-100）,00
	恢复出厂设置：	  01,07,00,00,00,00

	*/
	CString strT,strResultT;
	GetDlgItemText(IDC_EDIT2, strT);
	CStringA strA = CT2A(strT);
	string str(strA.GetBuffer());
	vector<string> vct;
	split_string(str,",",vct);
	int len = vct.size();
	if (len !=6)
	{
		MessageBox(_T("数据错误！"));
		return;
	}
	unsigned char cmd[0x20] = { 0 };
	for (int i=0;i<len;i++)
	{
		char* endp;
		cmd[i] = strtol(vct[i].c_str(), &endp,16);
	}
	unsigned int bytes = 0;
	if (IO(cmd, len, &bytes))
	{
		strResultT = _T("成功");
	}
	else
	{
		strResultT = _T("失败");
	}
	SetDlgItemText(IDC_EDIT3, strResultT);
}

bool CtestDlg::LoadDll()
{
	CString libPath = GetExePath() + DLL_NAME;
	m_hmodule = LoadLibrary(libPath);
	if (!m_hmodule)
	{
		return false;
	}
	IO = (pIO)GetProcAddress(m_hmodule, "IO");
	if (IO)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString CtestDlg::GetExePath()
{
	// 获取路径
	TCHAR pszFilePath[MAX_PATH];
	memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
	GetModuleFileName(NULL, pszFilePath, MAX_PATH);
	CString strPath(pszFilePath);
	strPath = strPath.Mid(0, strPath.ReverseFind('\\') + 1);
	return strPath;
}

void CtestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CtestDlg::split_string(const std::string& strData, const std::string& split_ch, std::vector<std::string>& vctList)
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