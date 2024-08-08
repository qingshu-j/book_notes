
// excel_comDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "excel_com.h"
#include "excel_comDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Cexcel_comDlg �Ի���



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


// Cexcel_comDlg ��Ϣ�������

BOOL Cexcel_comDlg::OnInitDialog()
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

	InitExcel();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cexcel_comDlg::OnPaint()
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
HCURSOR Cexcel_comDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��ʼ��Excel��
bool Cexcel_comDlg::InitExcel()
{
	HRESULT ht;
	ht = ::CoInitialize(NULL);
	if (ht == E_INVALIDARG)
	{
		MessageBox(_T("��ʼ��COMʧ��"));
	}

	//����Execel(����Excel)
	if (!m_App.CreateDispatch(_T("Excel.application"), nullptr))
	{
		MessageBox(_T("Error!Creat Excel Application Sever Fail!"));
		exit(1);
		return FALSE;
	}

	m_App.put_Visible(FALSE);//�Ƿ���ʾEXCEL
	m_App.put_DisplayFullScreen(FALSE);//����ȫ����ʾ
	m_App.put_DisplayAlerts(FALSE);//���ξ���
	return TRUE;
}

BOOL Cexcel_comDlg::PrintExcel(const CString& strPath)
{
	//InitExcel();

	m_Books = m_App.get_Workbooks();

	try
	{
		m_WorkBook = m_Books.Add(_variant_t(strPath));//��EXCEL�ļ�
	}
	catch (CException* e)
	{
		m_Books.Close();
		MessageBox(_T("Error!open Excel file Fail!"));
		return FALSE;
		//m_WorkBook = m_Books.Add(vtMissing);//�Ҳ������½�һ��
	}

	//����  �������//
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_WorkBook.PrintOut(covOptional, covOptional, covOptional ,covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	m_WorkBook.Close(covOptional, covOptional, covOptional);
	m_Books.Close();

	return TRUE;
}


void Cexcel_comDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str(_T("C:\\Users\\13506\\Desktop\\1.xlsx"));
	PrintExcel(str);
}
