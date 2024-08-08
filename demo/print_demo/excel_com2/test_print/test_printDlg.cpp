
// test_printDlg.cpp : ʵ���ļ�
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


// Ctest_printDlg �Ի���



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


// Ctest_printDlg ��Ϣ�������

BOOL Ctest_printDlg::OnInitDialog()
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
	//ö�ٴ�ӡ��������Ĭ�ϴ�ӡ��
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ctest_printDlg::OnPaint()
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
HCURSOR Ctest_printDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_printDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str, strFilePathName;
	GetDlgItemText(IDC_EDIT2, strFilePathName);
	if (!strFilePathName.GetLength())
	{
		MessageBox(_T("��ӡ�ļ�·��Ϊ��"));
		return;
	}
	if ((int)ShellExecute(m_hWnd, _T("print"), strFilePathName, NULL, NULL, SW_MINIMIZE) <= 32)
	{
		str = _T("ʧ��");
	}
	else
	{
		str = _T("�ɹ�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_COMBO1, str);
	if (SetDefaultPrinter(str))
	{
		//success
		SetDlgItemText(IDC_EDIT1, str);
	}
	else
	{
		MessageBox(_T("ʧ��"));
	}
}


void Ctest_printDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter("Excel�ļ�|*.xlsx;*.xls|All Files (*.*)|*.*||");
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

void Ctest_printDlg::InitPrintFileDir()
{
	TCHAR buf[0x80] = { 0 };
	DWORD dwRet = GetPrivateProfileString(_T("PrintConfig"), _T("PrintFileDir"), NULL, buf,sizeof(TCHAR)*0x80, _T(".\\config.ini"));
	if (0 == dwRet)
	{
		MessageBox(_T("�Ҳ����ļ���config.ini��������PrintConfig�����PrintFileDir"));
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
	m_WorkBook.PrintOut(covOptional, covOptional, covOptional, COleVariant((BYTE)FALSE), covOptional, covOptional, covOptional, covOptional, covOptional);
	m_WorkBook.Close(covOptional, covOptional, covOptional);
	m_Books.Close();

	return TRUE;
}

BOOL Ctest_printDlg::PrintOneSheet(const CString& strPath)
{

	m_Books.AttachDispatch(m_App.get_Workbooks());
	LPDISPATCH lpDisp = NULL;
	//����  �������//
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
	m_WorkBook.AttachDispatch(lpDisp);//�õ�Workbook  
	//sheets.AttachDispatch(m_WorkBook.get_Worksheets());//�õ�Worksheets  
	//lpDisp = m_WorkBook.get_ActiveSheet();//�õ���ǰ��Ծsheet������е�Ԫ�������ڱ༭״̬�У��˲������ܷ��أ���һֱ�ȴ�  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str, strFilePathName,strSN,strDir;
	GetDlgItemText(IDC_EDIT2, strDir);
	if (!strDir.GetLength())
	{
		MessageBox(_T("��ӡ�ļ�·��Ϊ��"));
		return;
	}
	GetDlgItemText(IDC_EDIT3, strSN);
	if (!strSN.GetLength())
	{
		MessageBox(_T("SNΪ��"));
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
		str = _T("�ɹ�");
	}
	else
	{
		str = _T("ʧ��");
	}
	//MessageBox(str);
	SetDlgItemText(IDC_EDIT3, _T(""));
}

void Ctest_printDlg::GetExcelFiles(const char* to_search,CArray<CString>& array)
{
	CString fileName;
	//const char *to_search = "C:\\Users\\13506\\Desktop\\*.*";
	long handle;//���ڲ��Ҿ��
	struct _finddata_t fileinfo;//�ļ���Ϣ�Ľṹ��
	handle = _findfirst(to_search, &fileinfo);//��һ�β���
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
	_findclose(handle);//�����˹رվ��
}
