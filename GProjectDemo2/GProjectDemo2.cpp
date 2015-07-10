
// GProjectDemo2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GProjectDemo2.h"
#include "MainFrm.h"

#include "GProjectDemo2Doc.h"
#include "GProjectDemo2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGProjectDemo2App

BEGIN_MESSAGE_MAP(CGProjectDemo2App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGProjectDemo2App::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	//ON_COMMAND(ID_32775, &CGProjectDemo2App::TestDBConnect)
	//ON_COMMAND(ID_32781, &CGProjectDemo2App::Record_BPoint)
END_MESSAGE_MAP()


// CGProjectDemo2App ����

CGProjectDemo2App::CGProjectDemo2App()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GProjectDemo2.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CGProjectDemo2App ����

CGProjectDemo2App theApp;


// CGProjectDemo2App ��ʼ��

BOOL CGProjectDemo2App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGProjectDemo2Doc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CGProjectDemo2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CGProjectDemo2App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	//����Լ��Ķ����ݿ�Ĺرղ���

	DBConnPool::Instanse()->DestroyAllDBConnections();

	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CGProjectDemo2App ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CGProjectDemo2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGProjectDemo2App �Զ������/���淽��

void CGProjectDemo2App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGProjectDemo2App::LoadCustomState()
{
}

void CGProjectDemo2App::SaveCustomState()
{
}

// CGProjectDemo2App ��Ϣ�������




/*
void CGProjectDemo2App::TestDBConnect()
{
	// TODO: �ڴ���������������
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		::MessageBox(NULL,_T("����ָ��ʵ����ʧ�ܣ�"),_T("�ɹ�"),MB_OK);
		return;
	}
		try {
			_bstr_t strConnect="Driver={sql server};server=LITIANJIE-PC;uid=sa;pwd=123456;database=MapData;";
			//_bstr_t strConnect="Provider=SQLOLEDB;Server=127.0.0.1,1433;Database=PBMS;uid=sa;pwd=pp471006459;";
			//_bstr_t strConnect="Provider=SQLOLEDB.1;Password=pp471006459;Persist Security Info=True;User ID=sa;"
				//"Initial Catalog=PBMS;Data Source=127.0.0.1,1433";
			//����������strConnect��䶼�����ã������Լ�ϲ��ѡ���ð�
			//Ҫע���޸��û���uid������pwd�����ݿ���database�������������������Լ�sql server�����ݿ���Ϣ
			sqlSp->Open(strConnect,"","",adModeUnknown);
			sqlSp->Close();
		}
		catch(_com_error &e) {
			sqlSp->Close();
			::MessageBox(NULL,e.Description(),_T("����"),MB_OK);
			return;
		}
	::MessageBox(NULL,_T("�����ӳɹ���"),_T("�ɹ�"),MB_OK);
}

*/
/*
void CGProjectDemo2App::Record_BPoint()
{
	// TODO: �ڴ���������������
	CString pathName;
	CString fileName;

	TCHAR szFilters[]= _T("MIF Files (*.mif)|*.mif|All Files (*.*)|*.*||");

   // Create an Open dialog; the default file name extension is ".my".
   CFileDialog fileDlg(TRUE, _T("mif"), _T("*.mif"),
      OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
		if(fileDlg.DoModal() == IDOK)
	   {
		  pathName = fileDlg.GetPathName();

		  // Implement opening and reading file in here.

		  //Change the window's title to the opened file's title.
		  fileName = fileDlg.GetFileTitle();
	   }
	RecordBuildingPointTool RBP;
	RBP.FilePosition=pathName;
	if(RBP.RecordBuildingLayerInfoToDB()==true)
	::MessageBox(NULL,_T("��¼��ɹ���"),_T("�ɹ�"),MB_OK);
}
*/