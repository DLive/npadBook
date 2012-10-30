// projectImport.cpp : 实现文件
//

#include "stdafx.h"
#include "npadBook.h"
#include "projectImport.h"


// CprojectImport 对话框

IMPLEMENT_DYNAMIC(CprojectImport, CDialog)

CprojectImport::CprojectImport(CWnd* pParent /*=NULL*/)
	: CDialog(CprojectImport::IDD, pParent)
{

}

CprojectImport::CprojectImport(int pid,ClocalSearchResult *pLocalDlg, HTREEITEM hItem, CWnd* pParent /*=NULL*/)
: CDialog(CprojectImport::IDD, pParent)
{
	this->m_pid=pid;
	this->m_pLocalDlg=pLocalDlg;
	m_hItem=hItem;
	pInputDB=NULL;
}

CprojectImport::~CprojectImport()
{
}

void CprojectImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CprojectImport, CDialog)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDC_GETPROJECTDIR, &CprojectImport::OnBnClickedGetprojectdir)
	ON_BN_CLICKED(IDC_IMPORTBEGIN, &CprojectImport::OnBnClickedImportbegin)
END_MESSAGE_MAP()


// CprojectImport 消息处理程序

LONG CprojectImport::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);


	GetDlgItem(IDC_FILETYPE)->SetWindowText(_T(".h .cpp .js .html .txt"));
	GetDlgItem(IDC_FILTERDIR)->SetWindowText(_T(".svn"));
	
	return bRet;
}
void CprojectImport::OnBnClickedGetprojectdir()
{
	// TODO: 在此添加控件通知处理程序代码
	WCHAR       szDisplayName[MAX_PATH];       
	WCHAR       szBuffer[MAX_PATH]={0};       
	BROWSEINFO       browseInfo;       
	browseInfo.hwndOwner=m_hWnd;       
	browseInfo.pidlRoot=NULL;      
	browseInfo.pszDisplayName=szDisplayName;       
	browseInfo.lpszTitle= _T("请选择项目根目录");       
	browseInfo.ulFlags=BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS|BIF_EDITBOX;       
	browseInfo.lpfn=NULL;       
	browseInfo.lParam=0;       
	LPITEMIDLIST   lpItemIDList;       
	if((lpItemIDList=SHBrowseForFolder(&browseInfo))!=NULL)       
	{
		if(SHGetPathFromIDList(lpItemIDList,szBuffer))       
		{       
			if(szBuffer[0]== '\0 ')       
			{  
				MessageBox(_T("获取目录失败"),_T("哟！出错了"),MB_ICONSTOP|MB_OK);
				return;       
			}       

		}       
		else       
		{       
			MessageBox(_T("获取目录失败"),_T("哟！出错了"),MB_ICONSTOP|MB_OK);
			return;       
		}
	}       
	if(szBuffer[0]== '\0 ') 
	{
		MessageBox(_T("你没有选择"),_T("你好"),MB_OK); 
	}
	SetDlgItemText(IDC_PROJECTROOT,szBuffer);
	m_rootDir=szBuffer;
}

void CprojectImport::OnBnClickedImportbegin()
{
	// TODO: 在此添加控件通知处理程序代码
	if(pInputDB==NULL){
		pInputDB=new CInputDB();
	}
	GetDlgItemText(IDC_PROJECTROOT,m_rootDir);

	CString filterStr;
	CString filterDir;
	GetDlgItemText(IDC_FILETYPE,filterStr);
	if(!filterStr.IsEmpty()){
		filterStr+=_T(" ");
		Split(filterStr,m_filterFile,_T(" "));
	}

	GetDlgItemText(IDC_FILTERDIR,filterDir);
	if(!filterDir.IsEmpty()){
		filterDir+=_T(" ");	
		Split(filterDir,m_filterDir,_T(" "));
	}
	
	findFile(m_pid,m_rootDir,m_hItem);
	SetDlgItemText(IDC_IMPORTSATUS,_T("已完成"));
}


bool CprojectImport::findFile(int pId, CString pathName, HTREEITEM hItem)
{
	CFileFind fFind;
	CString dirName=pathName;	
	if(dirName.Right(1)!=_T("\\"))
		dirName+=_T("\\");
	CString tempName=dirName;
	dirName+=_T("*.*");
	CString deletefile;
	BOOL isFind=fFind.FindFile(dirName);
	int num=0;
	while(isFind)
	{
		isFind=fFind.FindNextFileW();
		if(fFind.IsDots()) continue;
		if(!fFind.IsDirectory())
		{
			//如是文件
			tempName=fFind.GetFilePath();
			if(isNeedFile(tempName)){
				SetDlgItemText(IDC_IMPORTSATUS,tempName);
				addFileToDB(pId,tempName);
			}
		}
		else{
			CString className=fFind.GetFileName();
			if(!filterDir(className)){
				CString stauts=_T("正在创建分类 ")+className;
				SetDlgItemText(IDC_IMPORTSATUS,stauts);
				int newid=m_pLocalDlg->addClass(pId,className);
				HTREEITEM newItem=m_pLocalDlg->addClassToTree(hItem,newid,className);
				findFile(newid,fFind.GetFilePath(), newItem);
			}
			
		}
	}
	fFind.Close();
	
	return true;
}
BOOL CprojectImport::addFileToDB(int cid, CString filePath){
	articleInfo* tmp=new articleInfo();
	tmp->cID=cid;
	tmp->isSavetoDb=TRUE;
	ZeroMemory(tmp->filePath,sizeof(tmp->filePath));
	lstrcpy(tmp->filePath,filePath.GetBuffer());
	filePath.ReleaseBuffer();
	
	pInputDB->getText(tmp,TRUE);

	delete tmp;
	return TRUE;
}
BOOL CprojectImport::isNeedFile(CString fileName){
	if(m_filterFile.IsEmpty())
		return TRUE;
	int dotPosi=0;
	CString artype;
	if((dotPosi=fileName.ReverseFind('.'))!=-1 && fileName.ReverseFind('\\')<dotPosi)
		artype=fileName.Right(fileName.GetLength()-dotPosi);
	else
		return TRUE;//没有扩展名   照单收了
	
	for(int i=0;i<m_filterFile.GetCount();i++){
		if(m_filterFile.GetAt(i)==artype)
			return TRUE;
	}
	return FALSE;
}
BOOL CprojectImport::filterDir(CString Dir){
	for(int i=0;i<m_filterDir.GetCount();i++){
		if(m_filterDir.GetAt(i)==Dir)
			return TRUE; //过滤
	}
	return FALSE;
}
void CprojectImport::Split(CString source, CStringArray& dest, CString division)
{
	dest.RemoveAll();
	int pos = 0;
	int pre_pos = 0;
	while( -1 != pos ){
		pre_pos = pos;
		pos = source.Find(division,(pos+1));
		CString tmp=source.Mid(pre_pos,(pos-pre_pos));
		dest.Add(tmp.Trim());
	}
}