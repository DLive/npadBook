// npadBook.cpp : ���� DLL �ĳ�ʼ�����̡�
//


#include "stdafx.h"
#include "npadBook.h"
#include "InputDB.h"
#include <string.h>
#include "Conndb.h"
#include "Ccommon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CnpadBookApp

BEGIN_MESSAGE_MAP(CnpadBookApp, CWinApp)
END_MESSAGE_MAP()

#include "PluginDefinition.h"
#include "DockingFeature/Docking.h"

extern FuncItem funcItem[nbFunc];
extern NppData nppData;
extern ClocalSearchResult* pBookDlg;
extern tTbData mydlg;
// CnpadBookApp ����
BOOL CnpadBookApp::isInitDock=FALSE;
CnpadBookApp::CnpadBookApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	pArticleManage=new CArticleManager();
	
}


// Ψһ��һ�� CnpadBookApp ����

CnpadBookApp theApp;


// CnpadBookApp ��ʼ��

BOOL CnpadBookApp::InitInstance()
{
	CWinApp::InitInstance();

	pluginInit((HANDLE)this->m_hInstance);
	deleteTempDir();
	return TRUE;
}
CnpadBookApp *CnpadBookApp::getApp(){
	return &theApp;
}
BOOL CnpadBookApp::OnOpenFile(articleInfo *aInfo){
	if(aInfo->filePath){
		 return ::SendMessage(nppData._nppHandle, NPPM_DOOPEN,0,(LPARAM)aInfo->filePath);
	}
	return FALSE;
}
articleInfo* CnpadBookApp::findAInfo(int bufferid){
	articleInfo* pt=NULL;
	if(!(pt=pArticleManage->find(bufferid,FBufferID))){
		TCHAR path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferid,(LPARAM)path);
		pt=pArticleManage->find((LPCTSTR)path);
		if(pt)
			pt->bufferID=bufferid;
	}
	return pt;
}
BOOL CnpadBookApp::saveArticle(int bufferid){
	//::MessageBoxW(NULL,L"adfasd",L"asdf",0);
	
	if(articleInfo* pt=findAInfo(bufferid)){
		if(!pt->isSavetoDb)
			return FALSE;
		CString title=pBookDlg->getNowTitle();
		if(title.IsEmpty()){
			lstrcpy(pt->title,title.GetBuffer());
		}
		TCHAR path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferid,(LPARAM)path);
		if(lstrcmp(path,pt->filePath)==0){
			//Ϊ����

			//if(pt->isSavetoDb){
			CInputDB insert;
			insert.getText(pt,FALSE);
			//this->m_oldPath=lpszPathName;
			//this->m_isFromDb=true;
			//}
		}
		else{
			//���Ϊ
			CInputDB insert;

			insert.getText(pt,TRUE);
		}
	}
	else{
		//���ļ�
		return FALSE;
		//���ļ����档  bye bye
		TCHAR path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferid,(LPARAM)path);
		int id=0;
		id=articleIsExist(path);
		pt=pArticleManage->add_ID(id,bufferid,path,pBookDlg->getNowClassID());
		CInputDB insert;
		insert.getText(pt,TRUE);
	}
	return TRUE;
}
int CnpadBookApp::articleIsExist(LPCTSTR path,articleInfo* aInfo){
	CConndb add;//sql���Ӷ���
	CString sql;
	sql.Format(_T("select * from articles where txtaddress='%s'"),path);
	add.search(sql);
	int id=0;
	if(!add.m_query->eof())
	{
		
		_variant_t var;
		var=add.m_query->getIntField(_T("id"));
		if(var.vt!=VT_NULL)
			id=var.intVal;
		if(aInfo!=NULL){
			CString tmp;
			var=add.m_query->getIntField(_T("id"));
			if(var.vt!=VT_NULL){
				tmp=(LPCSTR)_bstr_t(var);
				lstrcpy(aInfo->title,tmp.GetBuffer());
			}
		}
	}
	
	return id;
}
BOOL CnpadBookApp::activeChange(int bufferID)
{
	articleInfo* pt=NULL;
	if(pt=findAInfo(bufferID)){
		if(pt->isSavetoDb==FALSE){
			pBookDlg->activeNullInfo();
			return FALSE;
		}
		if((pt->cID==0 ||lstrlen(pt->className)<=0) && pt->ID!=0){
			getArticleInfo(pt);
		}
		pBookDlg->activeChange(pt);
	}
	else{
		//���ļ�
		TCHAR path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferID,(LPARAM)path);
		wchar_t* pos=wcschr(path,_T('\\'));
		if(pos!=NULL){
			int id=0;
			pt=pArticleManage->add_bufferID(id,bufferID,path,pBookDlg->getNowClassID());
			if(!pt)
				return FALSE;
			id=articleIsExist(path);
			pt->ID=id;
			if(id==0){
				pt->isSavetoDb=FALSE;
				//CInputDB insert;
				//insert.getText(pt,TRUE);
			}
			else if(pt->cID==0 ||lstrlen(pt->className)<=0){
				getArticleInfo(pt);
			}
			pBookDlg->activeChange(pt);
			//pBookDlg->activeChange(pt);
		}
		else{
			pBookDlg->activeNullInfo();
		}
		
	}
	
		
	return TRUE;
}
BOOL CnpadBookApp::addNewInfo(int bufferID){
	TCHAR path[MAX_PATH];
	ZeroMemory(path,MAX_PATH);
	::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferID,(LPARAM)path);
	wchar_t* pos=wcschr(path,_T('\\'));
	if(pos!=NULL){
		int id=0;
		articleInfo* pt=pArticleManage->add_bufferID(id,bufferID,path,pBookDlg->getNowClassID());
		if(!pt)
			return FALSE;
		id=articleIsExist(path);
		pt->ID=id;
		if(id==0){
			pt->isSavetoDb=TRUE;
			CInputDB insert;
			insert.getText(pt,TRUE);
		}
		else if(pt->cID==0 ||lstrlen(pt->className)<=0){
			getArticleInfo(pt);
		}
		pBookDlg->activeChange(pt);
		//pBookDlg->activeChange(pt);
	}
	else{
		pBookDlg->activeNullInfo();
	}
}
BOOL CnpadBookApp::getArticleInfo(articleInfo *aInfo){
	CString sqlget;
	CConndb add;
	sqlget.Format(_T("select a.title,a.content,a.classid,a.id,a.encodetype,a.addtime,a.txtaddress,a.author,a.artitletype,a.keyword,a.difficulty,c.classname from articles AS a,class AS c where a.id=%d and a.classid=c.id"),aInfo->ID);
	add.search(sqlget);
	CString cName;
	if(!add.m_query->eof())
	{
		_variant_t var;
		var=add.m_query->getStringField(_T("classname"));
		if(var.vt!=VT_NULL){
			cName=(LPCSTR)_bstr_t(var);
			lstrcpy(aInfo->className,cName.GetBuffer());
			cName.ReleaseBuffer();
		}
		var=add.m_query->getStringField(_T("title"));
		if(var.vt!=VT_NULL){
			cName=(LPCSTR)_bstr_t(var);
			lstrcpy(aInfo->title,cName.GetBuffer());
			cName.ReleaseBuffer();
		}
		var=add.m_query->getIntField(_T("classid"));
		if(var.vt!=VT_NULL)
			aInfo->cID=var.intVal;

	}
	return TRUE;
}

//�������
BOOL CnpadBookApp::classChange(int cID,LPCTSTR cName){
	int bufferID=::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID,0,0);
	if(bufferID>0){
		articleInfo* aInfo=pArticleManage->find(bufferID,FBufferID);
		if(aInfo!=NULL){
			aInfo->cID=cID;
			ZeroMemory(aInfo->className,lstrlen(aInfo->className));
			lstrcpy(aInfo->className,cName);
			if(!aInfo->isSavetoDb){

				changSaveToDbStatus(TRUE,cID,cName);
			}
		}else{
			addNewInfo(bufferID);
		}
	}
	return TRUE;
}
//�������ݿ�
BOOL CnpadBookApp::changSaveToDbStatus(BOOL isSave,int cID,LPCTSTR cName){

	int bufferID=::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID,0,0);
	if(bufferID>0){
		articleInfo* aInfo=pArticleManage->find(bufferID,FBufferID);
		if(aInfo!=NULL  && isSave){
			aInfo->isSavetoDb=TRUE;
			aInfo->cID=cID;
			ZeroMemory(aInfo->className,lstrlen(aInfo->className));
			lstrcpy(aInfo->className,cName);
			
			if(aInfo->ID==0){
				
				CInputDB insert;
				insert.getText(aInfo,TRUE);
			}
			else if(aInfo->cID==0 ||lstrlen(aInfo->className)<=0){
				getArticleInfo(aInfo);
				pBookDlg->activeChange(aInfo); //���·���
			}
		}else{
			aInfo->isSavetoDb=FALSE;
		}
	}else if(!isSave){
		TCHAR path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID,bufferID,(LPARAM)path);
		wchar_t* pos=wcschr(path,_T('\\'));
		if(pos!=NULL){
			int id=0;
			articleInfo* pt=pArticleManage->add_bufferID(id,bufferID,path,pBookDlg->getNowClassID());
			if(!pt)
				return FALSE;
			id=articleIsExist(path);
			pt->ID=id;
			if(id==0){
				CInputDB insert;
				insert.getText(pt,TRUE);
			}
			else if(pt->cID==0 ||lstrlen(pt->className)<=0){
				getArticleInfo(pt);
			}
			pBookDlg->activeChange(pt);
			//pBookDlg->activeChange(pt);
		}

	}
	return TRUE;
}
BOOL CnpadBookApp::titleChange(CString title){
	int bufferID=::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID,0,0);
	if(bufferID>0){
		articleInfo* aInfo=pArticleManage->find(bufferID,FBufferID);
		if(aInfo!=NULL){
			
			ZeroMemory(aInfo->title,lstrlen(aInfo->title));
			lstrcpy(aInfo->title,title.GetBuffer());
			title.ReleaseBuffer();
		}
	}
	return TRUE;
}
BOOL CnpadBookApp::showDlg(int isInitNPP){
	if(funcItem[0]._cmdID){
		HMENU hMenu;
		hMenu=(HMENU)::SendMessage(nppData._nppHandle, NPPM_GETMENUHANDLE, NPPPLUGINMENU, 0);
		CMenu menu;
		menu.Attach(hMenu);
		BOOL isNeedShow=FALSE;
		if(isInitNPP){
			isNeedShow=(MF_CHECKED &(menu.GetMenuState(funcItem[0]._cmdID,MF_BYCOMMAND)));
		}
		else{
			isNeedShow=!(MF_CHECKED &(menu.GetMenuState(funcItem[0]._cmdID,MF_BYCOMMAND)));
		}
		
		menu.Detach();
		if(isInitNPP){
			CConndb add;
			CString sqlcmd=_T("select * from config where key='show'");
			add.search(sqlcmd);
			if(!add.m_query->eof())
			{

				CString tmp;
				_variant_t var;
				var=add.m_query->getStringField(_T("value"));
				if(var.vt!=VT_NULL){
					tmp=(LPCSTR)_bstr_t(var);
					if(tmp==_T("1"))
						isNeedShow=TRUE;
					else
						isNeedShow=FALSE;
				}
			}
		}
		if(!CnpadBookApp::isInitDock && isNeedShow){
			
			mydlg.dlgID=1;
			mydlg.hClient=pBookDlg->m_hWnd;
			mydlg.hIconTab=NULL;
			mydlg.uMask=DWS_DF_CONT_LEFT;
			mydlg.pszModuleName=TEXT("npadBook.dll");
			mydlg.pszName=TEXT("ITBook�ʼǹ���");
			mydlg.pszAddInfo=TEXT("npadBook");
			CnpadBookApp::isInitDock=::SendMessage(nppData._nppHandle,NPPM_DMMREGASDCKDLG, 0, (LPARAM)&mydlg);
			::SendMessage(nppData._nppHandle,NPPM_SETMENUITEMCHECK,funcItem[0]._cmdID, (LPARAM)TRUE);
		}else if(isNeedShow){
			::SendMessage(nppData._nppHandle,NPPM_DMMSHOW, 0, (LPARAM)mydlg.hClient);
			::SendMessage(nppData._nppHandle,NPPM_SETMENUITEMCHECK,funcItem[0]._cmdID, (LPARAM)TRUE);
		}else if(!isNeedShow){
			::SendMessage(nppData._nppHandle,NPPM_DMMHIDE, 0, (LPARAM)mydlg.hClient);
			::SendMessage(nppData._nppHandle,NPPM_SETMENUITEMCHECK,funcItem[0]._cmdID, (LPARAM)FALSE);
		}
		CConndb add;
		CString sql;
		if(isNeedShow)
			sql=_T("update  config set value='1'");
		else{
			sql=_T("update  config set value='0'");
		}
		add.excuteSql(sql);
	}
	return TRUE;
}
BOOL CnpadBookApp::setMenuShowSatue(BOOL show=FALSE)
{
	::SendMessage(nppData._nppHandle,NPPM_SETMENUITEMCHECK,funcItem[0]._cmdID, (LPARAM)show);
	return TRUE;
}
BOOL CnpadBookApp::removeFile(int bufferID){
	if(bufferID)
		pArticleManage->del(bufferID,FBufferID);
	return TRUE;
}
BOOL CnpadBookApp::activateBufferView(int bufferid){
	//�����ˣ�����
	int view=::SendMessage(nppData._nppHandle, NPPM_GETPOSFROMBUFFERID,bufferid,0);
	if(view!=-1){
		::SendMessage(nppData._nppHandle, NPPM_ACTIVATEDOC,0,view);
		return TRUE;
	}
	return FALSE;
}
BOOL CnpadBookApp::deleteTempDir(){
	Ccommon getfile;
	CString tempPath;
	getfile.getExeUrl(&tempPath);
	tempPath+=_T("Temp\\");
	Ccommon deletefile;
	deletefile.DeleteDirectory(tempPath);
	return TRUE;
}
extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{	

	switch(notifyCode->nmhdr.code){
		case NPPN_FILESAVED:
			{
			notifyCode->nmhdr.idFrom;
			TCHAR path[MAX_PATH];
			::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, notifyCode->nmhdr.idFrom,(LPARAM)path);

			theApp.saveArticle(notifyCode->nmhdr.idFrom);
			break;
			}
		case NPPN_BUFFERACTIVATED:
			{
				theApp.activeChange(notifyCode->nmhdr.idFrom);
				break;
			}
		case NPPN_FILEOPENED: //�ļ���
			{

				break;
			}
		case NPPN_FILECLOSED:
			{
				CnpadBookApp::getApp()->removeFile(notifyCode->nmhdr.idFrom);
				break;
			}
		case NPPN_READY:
			{
				
				CnpadBookApp::getApp()->showDlg(TRUE);
				//::SendMessage(nppData._nppHandle,NPPM_DMMSHOW, 0, (LPARAM)mydlg.hClient);//
				//::MessageBox(NULL, L"move", L"", MB_OK);
				break;
			}
		case NPPN_SHORTCUTREMAPPED:
			{
				//::MessageBox(NULL, L"move", L"", MB_OK);
			}

	}
}
// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	//if (Message == WM_SIZE)
	//{
	//	//::MessageBox(NULL, L"move", L"", MB_OK);
	//	int width  = LOWORD(lParam);
	//	int height = HIWORD(lParam);
	//	TRACE(L"%d\r\n",height);
	//}
	
	//if(Message==NPPN_FILESAVED){
	//	MessageBox(NULL,L"sdaf",L"asdfsd",0);
	//}
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif //UNICODE