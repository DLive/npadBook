// baseSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "baseSet.h"


// CbaseSet �Ի���

IMPLEMENT_DYNAMIC(CbaseSet, CPropertyPage)

CbaseSet::CbaseSet(CWnd* pParent /*=NULL*/)
	:  CPropertyPage(CbaseSet::IDD)
{

}

CbaseSet::~CbaseSet()
{
}

void CbaseSet::DoDataExchange(CDataExchange* pDX)
{
	 CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CbaseSet, CDialog)
	ON_BN_CLICKED(IDC_AUTORUN, &CbaseSet::OnBnClickedAutorun)
	ON_BN_CLICKED(IDC_RELATIONTXT, &CbaseSet::OnBnClickedRelationtxt)
END_MESSAGE_MAP()


// CbaseSet ��Ϣ�������

BOOL CbaseSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CheckAutorun();

	//�жϹ���
	if(CheckFileRelation(_T(".txt"),_T("ittit.Document")))
	{
		((CButton*)GetDlgItem(IDC_RELATIONTXT))->SetCheck(true);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RELATIONTXT))->SetCheck(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BOOL CbaseSet::CheckAutorun()
{
	HKEY hKey;
	long rz1=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_READ,&hKey));
	if(rz1!=ERROR_SUCCESS)
	{
		return FALSE;
	}
	DWORD style=REG_SZ;
	DWORD length;
	TCHAR *runpath;
	rz1=(::RegQueryValueExW(hKey,_T("itbook"),NULL,&style,NULL,&length));
	if(rz1==ERROR_SUCCESS)
	{
		runpath=new WCHAR[length];
		rz1=(::RegQueryValueEx(hKey,_T("itbook"),NULL,&style,(LPBYTE)runpath,&length));
	}
	::RegCloseKey(hKey);
	if(rz1!=ERROR_SUCCESS)
	{
		((CButton*)GetDlgItem(IDC_AUTORUN))->SetCheck(false);
		return FALSE;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTORUN))->SetCheck(true);
		TCHAR exepath[MAX_PATH];
		GetModuleFileName(NULL,exepath,MAX_PATH);
		if(wcscmp(exepath,((TCHAR*)runpath))!=0)
		{
			setAutorun();
		}
		return FALSE;
	}
}
BOOL CbaseSet::setAutorun()
{
	TCHAR exepath[MAX_PATH];
	GetModuleFileName(NULL,exepath,MAX_PATH);

	HKEY hKey;
	long rz1=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_WRITE,&hKey));
	rz1=(::RegSetValueEx(hKey,_T("itbook"),0,REG_SZ,(const unsigned char*)exepath,MAX_PATH));
	::RegCloseKey(hKey);
	return TRUE;
}
void CbaseSet::OnBnClickedAutorun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_AUTORUN))->GetCheck())
	{
		setAutorun();
	}
	else
	{
		delAutorun();
	}
}
BOOL CbaseSet::delAutorun()
{
	TCHAR exepath[MAX_PATH];
	GetModuleFileName(NULL,exepath,MAX_PATH);

	HKEY hKey;
	long rz1=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_WRITE,&hKey));
	rz1=(::RegDeleteValue(hKey,_T("itbook")));
	//rz1=(::RegSetValueEx(hKey,_T("itbook"),0,REG_SZ,(const unsigned char*)exepath,MAX_PATH));
	::RegCloseKey(hKey);
	return TRUE;
}

void CbaseSet::OnBnClickedRelationtxt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RELATIONTXT))->GetCheck())
	{
		RegisterFileRelationtxt(_T(".txt"),_T("ittit.Document"));
	}
	else
	{
		RegisterFileRelationtxt(_T(".txt"),_T("txtfile"));
	}
}
// ����ļ��������
// strExt: Ҫ������չ��(����: ".txt")
// strAppKey: ExeName��չ����ע����еļ�ֵ(����: "txtfile")
// ����TRUE: ��ʾ�ѹ�����FALSE: ��ʾδ����

// ����ļ��Ƿ����
BOOL CbaseSet::CheckFileRelation(const TCHAR* strExt, const TCHAR* strAppKey)
{
	int nRet=FALSE;
    HKEY hExtKey;
    TCHAR szPath[_MAX_PATH];  
    DWORD dwSize=sizeof(szPath);  
    if(RegOpenKey(HKEY_CLASSES_ROOT,strExt,&hExtKey)==ERROR_SUCCESS)
    {
        RegQueryValueEx(hExtKey,NULL,NULL,NULL,(LPBYTE)szPath,&dwSize);
        if(_wcsicmp(szPath,strAppKey)==0)
        {
            nRet=TRUE;
        }
        RegCloseKey(hExtKey);
        return nRet;
    }
    return nRet;
}


// ע���ļ�����
// strExe: Ҫ������չ��(����: ".txt")
// strAppName: Ҫ������Ӧ�ó�����(����: "C:\MyApp\MyApp.exe")
// strAppKey: ExeName��չ����ע����еļ�ֵ(����: "txtfile")
// strDefaultIcon: ��չ��ΪstrAppName��ͼ���ļ�(����: "C:\MyApp\MyApp.exe,0")
// strDescribe: �ļ���������
void  CbaseSet::RegisterFileRelation(TCHAR *strExt, TCHAR *strAppName, TCHAR *strAppKey, TCHAR *strDefaultIcon, TCHAR *strDescribe)
{
    TCHAR strTemp[_MAX_PATH];
    HKEY hKey;
    
    RegCreateKey(HKEY_CLASSES_ROOT,strExt,&hKey);
    RegSetValue(hKey,_T(""),REG_SZ,strAppKey,wcslen(strAppKey)+1);
    RegCloseKey(hKey);
    
    RegCreateKey(HKEY_CLASSES_ROOT,strAppKey,&hKey);
    RegSetValue(hKey,_T(""),REG_SZ,strDescribe,wcslen(strDescribe)+1);
    RegCloseKey(hKey);
    
    swprintf_s(strTemp,_T("%s\\DefaultIcon"),strAppKey);
    RegCreateKeyW(HKEY_CLASSES_ROOT,strTemp,&hKey);
    RegSetValue(hKey,_T(""),REG_SZ,strDefaultIcon,wcslen(strDefaultIcon)+1);
    RegCloseKey(hKey);
    
    swprintf_s(strTemp,_T("%s\\Shell"),strAppKey);
    RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);
    RegSetValue(hKey,_T(""),REG_SZ,_T("Open"),wcslen(_T("Open"))+1);
    RegCloseKey(hKey);
    
    swprintf_s(strTemp,_T("%s\\Shell\\Open\\Command"),strAppKey);
    RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);
    swprintf_s(strTemp,_T("%s \"%%1\""),strAppName);
    RegSetValue(hKey,_T(""),REG_SZ,strTemp,wcslen(strTemp)+1);
    RegCloseKey(hKey);
}
void  CbaseSet::RegisterFileRelationtxt(TCHAR *strExt, TCHAR *strAppKey)
{
    HKEY hKey;
    
    RegCreateKey(HKEY_CLASSES_ROOT,strExt,&hKey);
    RegSetValue(hKey,_T(""),REG_SZ,strAppKey,wcslen(strAppKey)+1);
    RegCloseKey(hKey);
    
	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_FLUSHNOWAIT,0,0);
    //RegCreateKey(HKEY_CLASSES_ROOT,strAppKey,&hKey);
    //RegSetValue(hKey,_T(""),REG_SZ,strDescribe,wcslen(strDescribe)+1);
    //RegCloseKey(hKey);
    
    //swprintf_s(strTemp,_T("%s\\DefaultIcon"),strAppKey);
    //RegCreateKeyW(HKEY_CLASSES_ROOT,strTemp,&hKey);
    //RegSetValue(hKey,_T(""),REG_SZ,strDefaultIcon,wcslen(strDefaultIcon)+1);
    //RegCloseKey(hKey);
    
    //swprintf_s(strTemp,_T("%s\\Shell"),strAppKey);
    //RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);
    //RegSetValue(hKey,_T(""),REG_SZ,_T("Open"),wcslen(_T("Open"))+1);
    //RegCloseKey(hKey);
    //
    //swprintf_s(strTemp,_T("%s\\Shell\\Open\\Command"),strAppKey);
    //RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);
    //swprintf_s(strTemp,_T("%s \"%%1\""),strAppName);
    //RegSetValue(hKey,_T(""),REG_SZ,strTemp,wcslen(strTemp)+1);
    //RegCloseKey(hKey);
}