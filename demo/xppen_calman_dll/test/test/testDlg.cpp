
// testDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtestDlg �Ի���



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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	LoadDll();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	��������Ϣ��	  00,f0,00,00,00,00

	����color-ɫ��  01,01,01,00,xx��01:aRGB,02:sRGB,04:DCIP3,0a:NTSC��,00
	����color-ɫ�£�  01,01,02,00,xx��01:5000K,03:6500K,04:7500K,05:9300K��,00
	����color-�Զ��壺01,01,03,01,xx��01:R,02:G,03:B��,xx��0-100��
	�������ȣ�		  01,03,00,00,����ֵxx��0-100��,00
	�������ȣ�		  01,04,00,00,�Աȶ�xx��0-100��,00
	�ָ��������ã�	  01,07,00,00,00,00

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
		MessageBox(_T("���ݴ���"));
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
		strResultT = _T("�ɹ�");
	}
	else
	{
		strResultT = _T("ʧ��");
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
	// ��ȡ·��
	TCHAR pszFilePath[MAX_PATH];
	memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
	GetModuleFileName(NULL, pszFilePath, MAX_PATH);
	CString strPath(pszFilePath);
	strPath = strPath.Mid(0, strPath.ReverseFind('\\') + 1);
	return strPath;
}

void CtestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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