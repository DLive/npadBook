// localSearchResult.cpp : 实现文件
//

#include "stdafx.h"
#include "localSearchResult.h"
#include "Conndb.h"
#include "CommResours.h"
//#include ""



#include "DLclassnamedlg.h" //分类名对话框
#include "CppSQLite3U.h"
#include "Ccommon.h"
#include "DLsyn.h"
#include "npadBook.h"
#include "projectImport.h"
// ClocalSearchResult 对话框

IMPLEMENT_DYNAMIC(ClocalSearchResult, CDialog)

ClocalSearchResult::ClocalSearchResult(CWnd* pParent)
{
	m_pDialogBar=NULL;
	m_treeIsInit=FALSE;
	m_pageSize=30;
	treeMenuStatus=TRUE;
	pDlgSize=NULL;
	m_classtreedlg=new CmyClassTreeDlg(this); //创建分类

	
}

ClocalSearchResult::~ClocalSearchResult()
{
}

void ClocalSearchResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESULT, m_serResult);
	DDX_Control(pDX, IDC_DELLOCALFILE, m_deletLocalFile);
}


BEGIN_MESSAGE_MAP(ClocalSearchResult, CDialog)

	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULT, &ClocalSearchResult::OnNMDblclkResult)
	ON_BN_CLICKED(IDC_LOCALSER, &ClocalSearchResult::OnBnClickedLocalser)
	ON_BN_CLICKED(IDC_DELETE, &ClocalSearchResult::OnBnClickedDelete)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_RESULTCLASTREE, &ClocalSearchResult::OnTvnItemexpandingClasstree)
	ON_NOTIFY(NM_RCLICK,IDC_RESULTCLASTREE, &ClocalSearchResult::OnNMRClickClasstree)
	ON_NOTIFY(TVN_ENDLABELEDIT,IDC_RESULTCLASTREE,&ClocalSearchResult::OnTvnEndlabeleditClasstree)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_RESULTCLASTREE, &ClocalSearchResult::OnTvnBeginlabeleditClasstree)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TCLASSADD, &ClocalSearchResult::OnTclassadd)
	ON_COMMAND(ID_TCLASSDEL, &ClocalSearchResult::OnTclassdel)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULTCLASTREE, &ClocalSearchResult::OnNMDblclkResultclastree)

	ON_COMMAND(ID_ADDROOTCLASS, &ClocalSearchResult::OnAddrootclass)
	ON_BN_CLICKED(IDC_AFTERPAGE, &ClocalSearchResult::OnBnClickedAfterpage)
	ON_BN_CLICKED(IDC_PREPAGE, &ClocalSearchResult::OnBnClickedPrepage)
	ON_CBN_SELCHANGE(IDC_JMPPAGE, &ClocalSearchResult::OnCbnSelchangeJmppage)
	ON_COMMAND(ID_CLASSRENAME, &ClocalSearchResult::OnClassReName)

	ON_UPDATE_COMMAND_UI(IDC_PREPAGE,OnUpdateButtonPrepage)
	ON_UPDATE_COMMAND_UI(IDC_AFTERPAGE,OnUpdateButtonAfterpage)
//	ON_WM_UPDATEUISTATE()
	ON_NOTIFY(NM_RCLICK, IDC_RESULT, &ClocalSearchResult::OnNMRClickResult)
	ON_COMMAND(ID_UPTOSERVER, &ClocalSearchResult::OnUptoserver)
	ON_COMMAND(ID_UPTOLOCAL, &ClocalSearchResult::OnUptolocal)
	ON_COMMAND(ID_UPCARTICLETODIS, &ClocalSearchResult::OnUpcarticletodis)
	ON_COMMAND(ID_UPCARTICLETOLOC, &ClocalSearchResult::OnUpcarticletoloc)

	//ON_MESSAGE(WM_MY_CHANGEINFO, OnchangeInfo)
	
	//ON_NOTIFY(NM_DBLCLK, IDC_CLASSTREE, &CpropertyDlg::OnNMDblclkClasstree)
	ON_CBN_SELCHANGE(IDC_NOWCLASSNAME, &ClocalSearchResult::OnCbnSelchangeNowclass)
	ON_MESSAGE(WM_MY_SETCLASSINIT, setClassinit)
	ON_CBN_SETFOCUS(IDC_NOWCLASSNAME, &ClocalSearchResult::OnCbnSetfocusNowclass)

	ON_EN_CHANGE(IDC_TITLE, &ClocalSearchResult::OnEnChangeTitle)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_SEARCHKEY, &ClocalSearchResult::OnEnChangeSearchkey)
	ON_BN_CLICKED(IDC_INSERTTODB, &ClocalSearchResult::OnBnClickedInserttodb)
	ON_UPDATE_COMMAND_UI(ID_TCLASSADD, &ClocalSearchResult::OnUpdateTclassadd)
	ON_UPDATE_COMMAND_UI(ID_TCLASSDEL, &ClocalSearchResult::OnUpdateTclassdel)
	ON_UPDATE_COMMAND_UI(ID_CLASSRENAME, &ClocalSearchResult::OnUpdateClassrename)
	ON_UPDATE_COMMAND_UI(ID_UPCARTICLETODIS, &ClocalSearchResult::OnUpdateUpcarticletodis)
	ON_UPDATE_COMMAND_UI(ID_UPCARTICLETOLOC, &ClocalSearchResult::OnUpdateUpcarticletoloc)
	ON_COMMAND(ID_SAVEPROJECT, &ClocalSearchResult::OnSaveproject)
	ON_UPDATE_COMMAND_UI(ID_SAVEPROJECT, &ClocalSearchResult::OnUpdateSaveproject)
	ON_COMMAND(ID_OPENFROMDB, &ClocalSearchResult::OnOpenfromdb)
END_MESSAGE_MAP()

//BOOL ClocalSearchResult::Create()
//{
//	//CDialogBar::Create(ClocalSearchResult::IDD);
//
//	return this->ShowWindow(true);
//}

void ClocalSearchResult::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//if (m_pDialogBar!=NULL) {
	//	// modeless case -- do not call base class OnCancel
	//	m_pDialogBar->PostMessage(WM_GOODBYELOCAL, IDCANCEL);
	//}
	//else {
	//	CDialogBar::OnCancel(); // modal case
	//}
}

void ClocalSearchResult::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类


}

LONG ClocalSearchResult::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);
	if (!UpdateData(FALSE))
	{
		TRACE0("Warning: UpdateData failed during dialog init.\n");
	}
	pDlgSize=new DLDlgSizeing(this->m_hWnd);

	pDlgSize->add(8,30,0.5,0.8,IDC_INSERTTODB,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->add(80,30,0.5,0.8,IDC_PREPAGE,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->add(140,30,0.5,0.8,IDC_JMPPAGE,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->add(190,30,0.5,0.8,IDC_AFTERPAGE,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->add(245,30,0.5,0.8,IDC_DELLOCALFILE,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->add(340,30,0.5,0.8,IDC_DELETE,SWP_NOSIZE|SWP_NOOWNERZORDER,M_BOTTOM_RELATIVE); //保存数据库
	pDlgSize->mushCY(110);//扣除标题 关键字位置
	pDlgSize->add(0.01,75 ,0.39,0.99,IDC_RESULTCLASTREE,SWP_NOOWNERZORDER); //分类
	pDlgSize->add(0.41,75 ,0.59,0.99,IDC_RESULT,SWP_NOOWNERZORDER); //结果
	// TODO:  在此添加额外的初始化
	m_serResult.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_serResult.InsertColumn(0,_T("文章标题"),LVCFMT_LEFT,250,0);
	m_serResult.InsertColumn(1,_T("最后修改时间"),LVCFMT_LEFT,100,0);
	m_serResult.InsertColumn(2,_T("编号"),LVCFMT_LEFT,40,0);
	m_serResult.InsertColumn(3,_T("作者"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(4,_T("文章分类"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(5,_T("难度"),LVCFMT_LEFT,40,0);
	m_serResult.InsertColumn(6,_T("文件路径"),LVCFMT_LEFT,80,0);
	m_serResult.InsertColumn(7,_T("类型"),LVCFMT_LEFT,40,0);

	if(!m_treeIsInit)
	{
		ClassInit();
		m_treeIsInit=TRUE;
	}
	classInfoInit(); //文章所属分类
//	setPageButtonInfo();
	
	return bRet;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 搜索文章
bool ClocalSearchResult::searchArticle(CString &title)
{
	CString keyword;
	this->stringSplit(title,keyword,_T(" "));
	m_sqlCondition=keyword;  //保存查询条件
	CString pagesql;
	pagesql.Format(_T("select count(*) from articles as a where %s "),keyword);

	//设置跳转页
	CConndb db;
	int count=db.getCount(pagesql);
	m_pageCount=count/m_pageSize;
	if(count%m_pageSize!=0)
		m_pageCount++;
	if(m_pageCount>0)
	{
		CComboBox* pcb=(CComboBox*)GetDlgItem(IDC_JMPPAGE);
		pcb->ResetContent();
		wchar_t num[10];
		for(int i=0;i<m_pageCount;i++)
		{
			pcb->InsertString(i,(LPCTSTR)_itow(i+1,num,10));
		}
		pcb->SetCurSel(0);
	}

	//查询语句
	m_pageIndex=0;
	CString sqlcmd;
	sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC LIMIT %d,%d")
		,keyword
		,m_pageSize*0
		,m_pageSize
		);
	//setPageButtonInfo();
	//sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s)"),keyword);
	if(searchAndAdd(sqlcmd))
		return true;
	else
		return false;
}
//按分类ID搜索
bool ClocalSearchResult::searchClassId(int cid)
{
	CString cmdtext;
	/*if(cid!=0)
	{
	cmdtext.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and a.classid in(select id from class where id=%d or parentid=%d)"),cid,cid);
	}
	else
	{*/
	CString keyword;
	keyword.Format(_T("a.classid=%d"),cid);
	m_sqlCondition=keyword;  //保存查询条件
	CString sqlcmd;

	CString pagesql;
	pagesql.Format(_T("select count(*) from articles as a where %s"),keyword);
	//设置跳转页
	CConndb db;
	int count=db.getCount(pagesql);
	m_pageCount=count/m_pageSize;
	if(count%m_pageSize!=0)
		m_pageCount++;

	if(m_pageCount>0)
	{
		CComboBox* pcb=(CComboBox*)GetDlgItem(IDC_JMPPAGE);
		pcb->ResetContent();
		wchar_t num[10];
		for(int i=0;i<m_pageCount;i++)
		{
			pcb->InsertString(i,(LPCTSTR)_itow(i+1,num,10));
		}
		pcb->SetCurSel(0);
	}
	else
	{
		MessageBox(_T("没有相关文章，请重新搜索"));
		return false;
	}

	//查询语句
	m_pageIndex=0;
	CString cmdtext2;
	cmdtext2.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC LIMIT %d,%d")
		,keyword
		,m_pageSize*0
		,m_pageSize
		);
	//}
	//setPageButtonInfo();
	if(this->searchAndAdd(cmdtext2))
		return true;
	else
		return false;

}
bool ClocalSearchResult::searchAndAdd(CString sqlcmd)  //sqlcmd为查询条件
{
	//CConndb getarticle;
	//getarticle.search(sqlcmd);

	CConndb db;
	db.search(sqlcmd);

	CString titles,id,addtime,locaddress,classname,author,diffiNum,filetype;
	_variant_t var;
	try
	{
		if(!db.m_query->eof())
		{
			m_serResult.DeleteAllItems();
		}
		else
		{
			//MessageBox(_T("没有相关文章，请重新搜索"));
			//GetDlgItem(IDC_SEARCHKEY)->SetFocus();
			return false;
		}
		int i=0;
		while(!db.m_query->eof())
		{
			var=db.m_query->getStringField(_T("title"));
			if(var.vt!=VT_NULL)
				titles=(LPCSTR)_bstr_t(var);
			var=db.m_query->getIntField(_T("id"));
			if(var.vt!=VT_NULL)
				id=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("addtime"));
			if(var.vt!=VT_NULL)
				addtime=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("txtaddress"));
			if(var.vt!=VT_NULL)
				locaddress=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("classname"));
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("author"));
			if(var.vt!=VT_NULL)
				author=(LPCSTR)_bstr_t(var);
			else
				author=_T("");
			var=db.m_query->getIntField(_T("difficulty"));
			if(var.vt!=VT_NULL)
				diffiNum=(LPCSTR)_bstr_t(var);
			else
				diffiNum=_T("");
			var=db.m_query->getStringField(_T("artitletype"));
			if(var.vt!=VT_NULL)
				filetype=(LPCSTR)_bstr_t(var);
			else
				filetype=_T("tit");
			//添加项
			m_serResult.InsertItem(i,_T(""));
			//添加数据
			m_serResult.SetItemText(i,0,titles);
			m_serResult.SetItemText(i,1,addtime);
			m_serResult.SetItemText(i,2,id);
			m_serResult.SetItemText(i,3,author);
			m_serResult.SetItemText(i,4,classname);
			m_serResult.SetItemText(i,5,diffiNum);
			m_serResult.SetItemText(i,6,locaddress);
			m_serResult.SetItemText(i,7,filetype);
			db.m_query->nextRow();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		return false;
	}
	//m_serResult.SetFocus();
	setPageButtonInfo();
	return true;

}
void ClocalSearchResult::OnNMDblclkResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	//得到文章内容
	CString pageno;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetItemState(i,LVIS_SELECTED)==LVIS_SELECTED)
		{
			pageno=m_serResult.GetItemText(i,2);
			break;
		}
	}
	viewArticle(pageno);
	*pResult = 0;
}
BOOL ClocalSearchResult::viewArticle(CString articleid,BOOL isFromDB)
{
	CString cmdsql;
	cmdsql.Format(_T("select a.title,a.content,a.classid,a.id,a.encodetype,a.addtime,a.txtaddress,a.author,a.artitletype,a.keyword,a.difficulty,c.classname from articles AS a,class AS c where a.id=%s and a.classid=c.id"),articleid);
	//CConndb getarticle;
	//getarticle.getarticle(cmdsql);
	CConndb db;
	db.search(cmdsql);

	int id=0;
	int classid=0;
	CString title,addtime,locaddress,classname,author,keyword,difficulty,type;
	CString content;
	int encodetype=0;
	difficulty=_T("0");
	_variant_t var;
	try
	{
		if(db.m_query->eof())
		{
			MessageBox(_T("该文章已不存在，请重新搜索"));
			return FALSE;
		}
		int i=0;
		while(!db.m_query->eof())
		{
			var=db.m_query->getStringField(_T("title"));
			if(var.vt!=VT_NULL)
				title=(LPCSTR)_bstr_t(var);
			var=db.m_query->getIntField(_T("id"));
			if(var.vt!=VT_NULL)
				id=var.intVal;
			var=db.m_query->getStringField(_T("addtime"));
			if(var.vt!=VT_NULL)
				addtime=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("content"));
			if(var.vt!=VT_NULL)
			{	
				content=(LPCSTR)_bstr_t(var);

			}
			var=db.m_query->getIntField(_T("classid"));
			if(var.vt!=VT_NULL)
				classid=var.intVal;
			var=db.m_query->getIntField(_T("encodetype"));
			if(var.vt!=VT_NULL)
				encodetype=var.intVal;
			var=db.m_query->getStringField(_T("txtaddress"));
			if(var.vt!=VT_NULL)
				locaddress=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("classname"));
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("author"));
			if(var.vt!=VT_NULL)
				author=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("artitletype"));
			if(var.vt!=VT_NULL)
				type=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("difficulty"));
			if(var.vt!=VT_NULL)
				difficulty=(LPCSTR)_bstr_t(var);
			var=db.m_query->getStringField(_T("keyword"));
			if(var.vt!=VT_NULL)
				keyword=(LPCSTR)_bstr_t(var);

			db.m_query->nextRow();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());

	}
	//改成从数据库读取  这步先略
	//bool istemp=false;//是否缓存
	BOOL isReadFromLocal=TRUE;
	articleInfo* tmp=NULL;
	if(tmp=CnpadBookApp::getApp()->pArticleManage->find(id,CArticleManager::ID)){
		return CnpadBookApp::getApp()->activateBufferView(tmp->bufferID);
		
	}
	//不存在 继续添加
	tmp=CnpadBookApp::getApp()->pArticleManage->add_ID(id,0,locaddress.GetBuffer(),classid);
	lstrcpy(tmp->className,classname.GetBuffer());
	BOOL isFileExist=TRUE;
	if(GetFileAttributes(locaddress)!=INVALID_FILE_ATTRIBUTES){
		//file is exist ,where we read
		//CFileFind tempFind;
		//if(tempFind.FindFile(locaddress)){
		//	CTime wtime;
		//	tempFind.FindNextFile();
 	//		tempFind.GetLastWriteTime(wtime);
		//	CString time=wtime.Format("%Y-%m-%d %H:%M");
		//	if(time.Compare(addtime)<0){
		//		//数据库比较新
		//		isReadFromLocal=FALSE;
		//	}
		//	else{
		//		isReadFromLocal=TRUE;
		//	}
		//}
	}else{
		isFromDB=TRUE;  //文件不存在
		isFileExist=FALSE;
	}
	if(isFromDB)
	{
		//文件不存在，或较老
		if(!isFileExist){
			TCHAR *filePath=new TCHAR[MAX_PATH];
			ZeroMemory(filePath,MAX_PATH);
			getExeUrl(filePath);
			filePath=wcscat(filePath,_T("Temp\\"));
			//filePath+=_T("Temp\\");
			WIN32_FIND_DATA   wfd;
			HANDLE hFind = FindFirstFile(filePath, &wfd);
			//文件夹是否存在
			if (!((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
			{
				SECURITY_ATTRIBUTES attrib;
				attrib.bInheritHandle = FALSE;
				attrib.lpSecurityDescriptor = NULL;
				attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
				//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
				::CreateDirectory(filePath, &attrib);
			}
			FindClose(hFind);
			if(type.IsEmpty()){
				type=_T("txt");
			}
			locaddress.Format(_T("%s%s_%d.%s"),filePath,title,id,type);
			tmp->isTemp=true;//临时文件
		}
		
		CFile aFile;
		if(!aFile.Open(locaddress,CFile::modeCreate|CFile::modeReadWrite,NULL))
		{
			AfxMessageBox(_T("文件打开失败"));
			return FALSE;
		}
		switch(encodetype){
				case E_ANSI:{
					LPCSTR pc=NULL;
					pc=unicodeToAnsi(content.GetBuffer());    //应该转成 u  utf8   回来改
					aFile.Write(pc,strlen(pc));
					delete pc;
					break;
					}
				case E_UBOMUTF8:
				case E_UTF8:{
					LPCSTR pc=NULL;
					pc=unicodeToUtf8(content.GetBuffer());
					if(encodetype==E_UTF8){
						byte head[3]={0xEF,0xBB,0xBF};
						aFile.Write(head,3);
					}
					aFile.Write(pc,strlen(pc));
					delete pc;
					break;
					}
				case E_UNICODE:
				default:
					WORD wSignature =0xFEFF;//0xEFBBBF;// ; 
					aFile.Write(&wSignature,2);
					aFile.Write(content,content.GetLength());
					break;

		}		
		aFile.Close();
		
	}
	ZeroMemory(tmp->filePath,lstrlen(tmp->filePath));
	lstrcpy(tmp->filePath,locaddress);
	ZeroMemory(tmp->title,lstrlen(tmp->title));
	lstrcpy(tmp->title,title.GetBuffer());
	CnpadBookApp::getApp()->OnOpenFile(tmp);
	return TRUE;
}
BOOL ClocalSearchResult::activeChange(articleInfo * pInfo)
{

	if(pInfo->title!=NULL && lstrlen(pInfo->title)>0){
		GetDlgItem(IDC_TITLE)->SetWindowText(pInfo->title);
	}else{
		GetDlgItem(IDC_TITLE)->SetWindowText(_T(""));
	}
	ChangeClassName(pInfo->cID,pInfo->className,TRUE);
	if(pInfo->isSavetoDb){
		((CButton*)GetDlgItem(IDC_INSERTTODB))->SetCheck(TRUE);
	}else{
		((CButton*)GetDlgItem(IDC_INSERTTODB))->SetCheck(FALSE);
	}
	return TRUE;
}
BOOL ClocalSearchResult::activeNullInfo()
{
	GetDlgItem(IDC_TITLE)->SetWindowText(_T(""));
	((CButton*)GetDlgItem(IDC_INSERTTODB))->SetCheck(FALSE);
	ChangeClassName(0,_T("请选择分类"),TRUE);
	((CButton*)GetDlgItem(IDC_INSERTTODB))->SetCheck(FALSE);
	return TRUE;
}
//得到程序路径
void ClocalSearchResult::getexeurl(CString* purl)
{
	TCHAR exefileurl[MAX_PATH];
	GetModuleFileName(NULL,exefileurl,MAX_PATH);
	(_tcsrchr(exefileurl, _T('\\')))[1] = 0;
	*purl=exefileurl;
}
CString ClocalSearchResult::getNowTitle()
{
	CString title;
	GetDlgItem(IDC_TITLE)->GetWindowTextW(title);
	if(title.IsEmpty())
	{
		return NULL;

	}
	return title;
}
// 字符串分割
void ClocalSearchResult::stringSplit(CString& source, CString& result, CString division)
{
	source.TrimLeft();
	source.TrimRight();
	result.Empty();
	int pos = 0;
	int pre_pos = 0;
	bool isfirst=true;
	CString temp;
	CString tempresult;
	CString word;
	while( -1 != pos )
	{
		pre_pos = pos;
		pos = source.Find(division,(pos+1));
		if(pos!=-1)
		{
			word=source.Mid(pre_pos,(pos-pre_pos));
			word.TrimLeft();
			word.TrimRight();
		}
		else
		{
			word=source.Mid(pre_pos);
			word.TrimLeft();
			word.TrimRight();
		}
		if(word.IsEmpty())
			continue;

		temp.Format(_T("(a.title like '%c%s%c') OR (a.txtaddress like '%c%s%c')"),0x25,word,0x25,0x25,word,0x25);
		if(isfirst)
		{
			tempresult=temp;
			isfirst=false;
		}
		else
		{
			tempresult+=_T(" OR ");
			tempresult+=temp;
			//tempresult.Format(_T("%s OR %s"),tempresult,temp);
		}
	}
	result=tempresult;
}

void ClocalSearchResult::OnBnClickedLocalser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString title;
	GetDlgItem(IDC_SEARCHKEY)->GetWindowTextW(title);
	if(title.IsEmpty())
	{
		MessageBox(_T("标题不能为空"));

	}
	else
	{		
		this->searchArticle(title);

	}
}

//未测试
void ClocalSearchResult::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AfxMessageBox(_T("请确认是否删除？"),MB_OKCANCEL)==IDCANCEL)
		return;
	//CConndb del;
	CString no;
	CString localpath;
	int count=0;
	bool isdellocal=false;
	if(m_deletLocalFile.GetCheck())
		isdellocal=true;
	CArray<int,int> arr;
	CString sqlcmd;
	CConndb db;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetCheck(i))
		{
			no=m_serResult.GetItemText(i,2);
			sqlcmd.Format(_T("delete from articles where id=%s"),no);

			db.excuteSql2(sqlcmd);
			arr.SetAtGrow(count,i);
			if(isdellocal)
			{
				localpath=m_serResult.GetItemText(i,3);
				DeleteFile(localpath);
			}
			count++;
		}

	}
	if(count==0)
		AfxMessageBox(_T("您未选择内容"));

	for(int i=0;i<arr.GetSize();i++)
	{
		m_serResult.DeleteItem(arr.GetAt(arr.GetSize()-i-1));		
	}

}


BOOL ClocalSearchResult::ClassInit(void)
{
	
	CTreeCtrl* tc=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	tc->DeleteAllItems();
	DWORD dwStyle = GetWindowLong(tc->m_hWnd,GWL_STYLE);
	dwStyle |= WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS;
	SetWindowLong(tc->m_hWnd,GWL_STYLE,dwStyle);

	//添加图示列表

	Cil1.Create(16,16,ILC_COLORDDB|ILC_MASK,0,2);
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES0));
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES1));
	tc->SetImageList(&Cil1,TVSIL_NORMAL);
	Cil1.SetBkColor(tc->GetBkColor());

	CConndb db;
	CString sqlcmd=_T("SELECT * from class order by lv ASC,parentid ASC,id ASC");
	db.search(sqlcmd);
	HTREEITEM hItem,hSubItem;//树句柄
	CString classname;
	int pid;
	int curlv=1;
	int curparentid=0;
	_variant_t var;
	DWORD cid;
	int i=0;
	try{
		while(!db.m_query->eof())
		{
			
			var=db.m_query->getIntField(_T("id"));//getclass.m_pRecordset->GetCollect("id");
			if(var.vt!=VT_NULL)
				cid=var.ulVal;
			LPTSTR test=(LPTSTR)db.m_query->getStringField(_T("classname"));
			var=db.m_query->getStringField(_T("classname"));//getclass.m_pRecordset->GetCollect("classname");
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=db.m_query->getIntField(_T("parentid"));//getclass.m_pRecordset->GetCollect("parentid");
			if(var.vt!=VT_NULL)
				pid=var.intVal;
			var=db.m_query->getIntField(_T("lv"));//getclass.m_pRecordset->GetCollect("lv");
			if(var.vt!=VT_NULL)
				curlv=var.intVal;
			if(pid!=0)
			{
				curlv--;//得到该类的父节点深度
				if(pid!=curparentid)
				{
					int beginlv=1;
					hItem=FindItem(*tc,tc->GetRootItem(),pid,&curlv,&beginlv);
					curparentid=pid;
				}
				hSubItem = tc->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
			}
			else
			{
				tc->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,TVI_ROOT,TVI_LAST);
			}


			i++;

			db.m_query->nextRow();
			//getclass.m_pRecordset->MoveNext();
		}
	}
	catch(CppSQLite3Exception& e)
	{
		printf("%s",e.errorMessage());
	}

	return 0;
}

void ClocalSearchResult::OnTvnItemexpandingClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem=pNMTreeView->itemNew.hItem;

	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);

	if(pNMTreeView->action==TVE_EXPAND)
	{
		pTb->SetItemImage(hItem,1,1);
	}
	else
	{
		pTb->SetItemImage(hItem,0,1);
	}
	*pResult = 0;

}
//树右击
void ClocalSearchResult::OnNMRClickClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);

	CPoint   point; 
	TVHITTESTINFO   HitTestInfo; 
	GetCursorPos(&point); 
	pTb->ScreenToClient(&point); 
	HitTestInfo.pt   =   point; 
	//HTREEITEM   hItem   = pTb->HitTest(&HitTestInfo);

	UINT uFlags;
	HTREEITEM   hItem =pTb->HitTest(point, &uFlags);


	if( TVHT_ONITEM & uFlags)
		treeMenuStatus=TRUE;
	else
		treeMenuStatus=FALSE;

	pTb->Select(hItem, TVGN_CARET);
	GetCursorPos(&point);
	this->SetForegroundWindow();

	CMenu m_menu;
	m_menu.LoadMenu(IDR_ICONMENU);

	CMenu *psub = (CMenu *)m_menu.GetSubMenu(1);  			
	
	DWORD dwID =psub->TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y ,this);
	m_menu.DestroyMenu();



	*pResult = 0;
}
void ClocalSearchResult::classInfoInit()
{
	/*CComboBox* pCb=(CComboBox*)GetDlgItem(IDC_DIFFICULTY);
	CString num;
	for(int i=0;i<6;i++)
	{

		num.Format(_T("%d"),i);
		pCb->AddString(num);
		pCb->SetCurSel(0);
	}*/
	CComboBox* pCb=(CComboBox*)GetDlgItem(IDC_NOWCLASSNAME);
	pCb->AddString(_T("分类"));
	pCb->SetItemData(0,0);
	pCb->SetCurSel(0);
}
//添加发类
void ClocalSearchResult::OnTclassadd()
{
	//MessageBox(NULL,_T("fdsa"),0);
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int pid=pTb->GetItemData(hItem);

	CDLclassnamedlg getname;
	getname.DoModal();
	CString classname=getname.m_name;
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}
	int cid=addClass(pid,classname);

	pTb->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
	pTb->Expand(hItem,TVE_EXPAND);

	//通知初始化工具栏分类
	//CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	//CpropertyDlg* pDlg=&pMain->m_propertyBar;
	setClassinit(0,0);
	//pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);

}

int ClocalSearchResult::addClass(int pid,CString classname){

	CString sqlget;
	sqlget.Format(_T("select lv from class where id=%d"),pid);
	CConndb sqlite;
	sqlite.search(sqlget);

	int lv=0;
	if(!sqlite.m_query->eof())
	{
		_variant_t var;
		var=sqlite.m_query->getIntField(_T("lv"));
		if(var.vt!=VT_NULL)
			lv=var.intVal;		
	}
	//插入新分类
	sqlget.Format(_T("insert into class (classname,parentid,lv) values ('%s',%d,%d)"),classname,pid,lv+1);
	sqlite.excuteSql(sqlget);

	//得到刚才入的ID
	DWORD cid;
	sqlget.Format(_T("select max(id) as maxid from class"));
	sqlite.search(sqlget);
	if(!sqlite.m_query->eof())
	{
		_variant_t var;
		var=sqlite.m_query->getIntField(_T("maxid"));
		if(var.vt!=VT_NULL)
			cid=var.ulVal;
	}
	return cid;
}
//编辑分类名称
void ClocalSearchResult::OnTvnEndlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString nowname;
	nowname=pTVDispInfo->item.pszText;
	if(nowname==this->m_beginClassname)
		return;
	CString sqltext;
	sqltext.Format(_T("update class set classname='%s' where id=%d"),nowname,pTVDispInfo->item.lParam);
	CConndb update;
	if(update.excuteSql(sqltext))
	{
		CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
		TVITEMW tv;
		memset(&tv,0,sizeof(TVITEM));
		tv.mask=TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tv.hItem=pTVDispInfo->item.hItem;
		pTb->GetItem(&tv);
		tv.pszText=(LPWSTR)(nowname.GetBuffer(nowname.GetLength()));
		nowname.ReleaseBuffer();
		pTb->SetItem(&tv);
	}

	////通知初始化工具栏分类
	//CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	//CpropertyDlg* pDlg=&pMain->m_propertyBar;
	//pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
	setClassinit(0,0);
	//*pResult = 0;  
}


void ClocalSearchResult::OnTvnBeginlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	this->m_beginClassname=pTVDispInfo->item.pszText;
	*pResult = 0;
}
//删除分类
void ClocalSearchResult::OnTclassdel()
{
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	CString ids;
	TravelTree(pTb,hItem,ids);
	ids.TrimRight(',');
	/*if(pTb->ItemHasChildren(hItem))
	{
		AfxMessageBox(_T("该类含有子类,请先删除子类"));
		return;
	}*/
	CString sqlcmd;
	CConndb del;
	sqlcmd.Format(_T("select count(id) as num from articles where classid in (%s)"),ids);
	int count=del.getCount(sqlcmd);
	/*
	if(!del.m_query->eof());
	{
	_variant_t var;
	var=del.m_pRecordset->GetCollect("num");
	if(var.vt!=VT_NULL)
	count=var.ulVal;
	}*/
	
	CString info;
	info.Format(_T("此次操作将删除%d篇文章"),count);
	if(AfxMessageBox(info,MB_OKCANCEL)!=IDOK)
		return;
	if(count>0)
	{
		sqlcmd.Format(_T("delete from articles where classid in (%s)"),ids);
		del.excuteSql(sqlcmd);
	}
	sqlcmd.Format(_T("delete from class where id in (%s)"),ids);

	if(del.excuteSql(sqlcmd)==0)
	{
		pTb->DeleteItem(hItem);
	}
	setClassinit(0,0);
	////通知初始化工具栏分类
	//CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	//CpropertyDlg* pDlg=&pMain->m_propertyBar;
	//pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);_
}

void ClocalSearchResult::TravelTree(CTreeCtrl* pTb, HTREEITEM hItem ,CString &ids)
{ 
	HTREEITEM   hChildItem,hBrotherItem; 

	//查找子节点，没有就结束 
	CString tmp;
	tmp.Format(_T("%d,"),pTb->GetItemData(hItem));
	ids.Append(tmp);
	hChildItem=pTb->GetChildItem(hItem); 
	if(hChildItem!=NULL) 
	{ 
		//设置子节点的状态与当前节点的状态一致 
		//CTreeCtrl::SetItemState(   hChildItem,   INDEXTOSTATEIMAGEMASK(nState),   TVIS_STATEIMAGEMASK   ); 
		//再递归处理子节点的子节点和兄弟节点 
		
		
		TravelTree(pTb, hChildItem,ids); 

		//处理子节点的兄弟节点和其子节点 
		hBrotherItem=pTb->GetNextSiblingItem(hChildItem); 
		while   (hBrotherItem) 
		{ 
			//再递归处理子节点的兄弟节点的子节点和兄弟节点 
			//tmp.Format(_T("%d"),pTb->GetItemData(hBrotherItem));
			//ids.Append(tmp);
			TravelTree(pTb, hBrotherItem, ids); 
			hBrotherItem=pTb->GetNextSiblingItem(hBrotherItem); 
		} 
	} 
} 
void ClocalSearchResult::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(FALSE);
	//CDialog::OnClose();
}



HTREEITEM ClocalSearchResult::FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* findLevel,int* curLevel)
{
	HTREEITEM hFind;	
	if(item == NULL)
		return NULL;

	while(item != NULL)
	{
		if(*findLevel==*curLevel)
		{
			//只有在到达指定深度时,才比较
			DWORD cc=tree.GetItemData(item);
			if(cc == strText)
				return item;
		}

		if(tree.ItemHasChildren(item))
		{
			(*curLevel)++;//深度加一
			item = tree.GetChildItem(item);
			hFind = FindItem(tree, item, strText,findLevel,curLevel);		
			if(hFind)
			{
				return hFind;		
			}
			else
			{
				item= tree.GetNextSiblingItem(tree.GetParentItem(item));
				(*curLevel)--;//深度减一
			}
		}
		else
		{
			item = tree.GetNextSiblingItem(item);
			if(item == NULL)
				return NULL;
		}		
	}

	return item;
}
void ClocalSearchResult::OnNMDblclkResultclastree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	int data;
	data=pTb->GetItemData(pTb->GetSelectedItem());
	searchClassId(data);
	*pResult = 0;
}

void ClocalSearchResult::OnAddrootclass()
{
	// TODO: 在此添加命令处理程序代码
	CDLclassnamedlg getname;
	//getname.SetWindowTextW(_T("添加分类"));
	getname.DoModal();
	CString classname=getname.m_name;
	//getname.Create(CDLclassnamedlg::IDD);
	//getname.ShowWindow(TRUE);
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	//CString classname=_T("新建分类,双击修改名字");
	CConndb addclass;
	//插入新分类
	CString sqlget;//=_T("insert into class (classname,parentid,lv) values ('新建分类,双击修改名字',0,1)");
	sqlget.Format(_T("insert into class (classname,parentid,lv) values ('%s',0,1)"),classname);
	addclass.excuteSql(sqlget);

	//得到刚才入的ID
	DWORD cid;
	sqlget.Format(_T("select max(id) as maxid from class"));
	addclass.search(sqlget);
	if(!addclass.m_query->eof())
	{
		_variant_t var;
		var=addclass.m_query->getIntField(_T("maxid"));
		if(var.vt!=VT_NULL)
			cid=var.ulVal;
	}
	HTREEITEM hItem=pTb->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,TVI_ROOT,TVI_LAST);
	pTb->Expand(hItem,TVE_EXPAND);
	setClassinit(0,0);
	////通知初始化工具栏分类
	//CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	//CpropertyDlg* pDlg=&pMain->m_propertyBar;
	//pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0); 
}

void ClocalSearchResult::OnBnClickedAfterpage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pageIndex++;
	if(m_pageIndex>=m_pageCount)
	{
		m_pageIndex--;
		return;
	}
	//setPageButtonInfo();

	CString sqlcmd;
	sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC LIMIT %d,%d")
		,m_sqlCondition
		,m_pageSize*m_pageIndex
		,m_pageSize
		);

	searchAndAdd(sqlcmd);
	((CComboBox*)GetDlgItem(IDC_JMPPAGE))->SetCurSel(m_pageIndex);
}

void ClocalSearchResult::OnBnClickedPrepage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pageIndex--;
	if(m_pageIndex<0)
	{
		m_pageIndex++;
		return;
	}
	//setPageButtonInfo();

	CString sqlcmd;
	sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC LIMIT %d,%d")
		,m_sqlCondition
		,m_pageSize*m_pageIndex
		,m_pageSize
		);

	searchAndAdd(sqlcmd);
	((CComboBox*)GetDlgItem(IDC_JMPPAGE))->SetCurSel(m_pageIndex);
}

void ClocalSearchResult::OnCbnSelchangeJmppage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pageIndex=((CComboBox*)GetDlgItem(IDC_JMPPAGE))->GetCurSel();
	if(m_pageIndex<0 || m_pageIndex>m_pageCount)
		return;
	//setPageButtonInfo();

	CString sqlcmd;
	sqlcmd.Format(_T("SELECT a.title,a.id,a.classid,a.addtime,a.txtaddress,c.classname,a.author,a.difficulty,a.artitletype FROM articles AS a,class AS c where a.classid=c.id and (%s) ORDER BY a.id DESC LIMIT %d,%d")
		,m_sqlCondition
		,m_pageSize*m_pageIndex
		,m_pageSize
		);

	searchAndAdd(sqlcmd);
}

void ClocalSearchResult::setPageButtonInfo()
{
	////向前
	if(m_pageIndex<1)
		((CButton*)GetDlgItem(IDC_PREPAGE))->EnableWindow(FALSE);
	else
		((CButton*)GetDlgItem(IDC_PREPAGE))->EnableWindow(TRUE);

	//向后
	if(m_pageIndex>=(m_pageCount-1))
		((CButton*)GetDlgItem(IDC_AFTERPAGE))->EnableWindow(FALSE);
	else
		((CButton*)GetDlgItem(IDC_AFTERPAGE))->EnableWindow(TRUE);
}
void ClocalSearchResult::OnUpdateButtonPrepage(CCmdUI * pCmdUI){
	pCmdUI ->Enable(m_pageIndex<1?FALSE:TRUE);
}
void ClocalSearchResult::OnUpdateButtonAfterpage(CCmdUI * pCmdUI){
	pCmdUI ->Enable(m_pageIndex+1>=m_pageCount?FALSE:TRUE);
}


void ClocalSearchResult::OnClassReName()
{
	// TODO: 在此添加命令处理程序代

	CDLclassnamedlg getname;
	getname.DoModal();
	CString classname=getname.m_name;
	if(classname.IsEmpty())
	{
		MessageBox(_T("分类名不能为空"));
		return;
	}

	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int pid=pTb->GetItemData(hItem);
	pTb->SetItemText(hItem,classname.GetBuffer());
	classname.ReleaseBuffer();

	CString sqltext;
	sqltext.Format(_T("update class set classname='%s' where id=%d"),classname,pid);
	CConndb update;
	if(update.excuteSql(sqltext))
	{
		pTb->SetItemText(hItem,classname);
	}
	setClassinit(0,0);

	////通知初始化工具栏分类
	//CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	//CpropertyDlg* pDlg=&pMain->m_propertyBar;
	//pDlg->SendMessage(WM_MY_SETCLASSINIT,0,0);
}

//void ClocalSearchResult::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
//{
//	// 该功能要求使用 Windows 2000 或更高版本。
//	// 符号 _WIN32_WINNT 和 WINVER 必须 >= 0x0500。
//	// TODO: 在此处添加消息处理程序代码
//}

void ClocalSearchResult::OnNMRClickResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	CPoint   point; 
	GetCursorPos(&point);

	this->SetForegroundWindow();

	CMenu m_menu;
	m_menu.LoadMenu(IDR_ICONMENU);

	CMenu *psub = (CMenu *)m_menu.GetSubMenu(2);  			
	DWORD dwID =psub->TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y ,this);
	m_menu.DestroyMenu();
	*pResult = 0;
}

void ClocalSearchResult::OnUptoserver()
{
	// TODO: 在此添加命令处理程序代码
	//CArray<int,int> arr;
	CString no;
	CStringArray data;
	int count=0;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetCheck(i))
		{
			data.Add(m_serResult.GetItemText(i,2));
			//no=m_serResult.GetItemText(i,2);
			//arr.SetAtGrow(count,i);
			count++;
		}
	}
	if(count==0){
		AfxMessageBox(_T("您未选择内容"));
		return;
	}
	CDLsyn sendData;
	if(!sendData.openSession(_T("dlive.sinaapp.com"),_T("test.php")))
	{
		AfxMessageBox(_T("链接服务器出错"));
		return;
	}

	//sendData.PostData(_T("dlive.sinaapp.com"),_T("test.php"),_T("class=haha&comtent=tttttt"),_T("http://dlive.sinaapp.com.com"),80);
	sendData.upFileToSer(data);
	//for(int i=0;i<arr.GetSize();i++)
	//{
	//	m_serResult.DeleteItem(arr.GetAt(arr.GetSize()-i-1));		
	//}
}

void ClocalSearchResult::OnUptolocal()
{
	// TODO: 在此添加命令处理程序代码
	CString no;
	CStringArray data;
	int count=0;
	for(int i=0;i<m_serResult.GetItemCount();i++)
	{
		if(m_serResult.GetCheck(i))
		{
			data.Add(m_serResult.GetItemText(i,2));
			count++;
		}
	}
	if(count==0){
		AfxMessageBox(_T("您未选择内容"));
		return;
	}
	CDLsyn sendData;
	if(!sendData.openSession(_T("dlive.sinaapp.com"),_T("test.php")))
	{
		AfxMessageBox(_T("链接服务器出错"));
		return;
	}

	//sendData.PostData(_T("dlive.sinaapp.com"),_T("test.php"),_T("class=haha&comtent=tttttt"),_T("http://dlive.sinaapp.com.com"),80);
	sendData.upFileToLoc(data);

}


void ClocalSearchResult::OnUpcarticletodis()
{
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int id=pTb->GetItemData(hItem);

	CDLsyn sendData;
	if(!sendData.openSession(_T("dlive.sinaapp.com"),_T("test.php")))
	{
		AfxMessageBox(_T("链接服务器出错"));
		return;
	}
	CString idstr;
	idstr.Format(_T("%d"),id);
	//sendData.PostData(_T("dlive.sinaapp.com"),_T("test.php"),_T("class=haha&comtent=tttttt"),_T("http://dlive.sinaapp.com.com"),80);
	sendData.upClassFileToSer(idstr);
}


void ClocalSearchResult::OnUpcarticletoloc()
{
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int id=pTb->GetItemData(hItem);

	CDLsyn sendData;
	if(!sendData.openSession(_T("dlive.sinaapp.com"),_T("test.php")))
	{
		AfxMessageBox(_T("链接服务器出错"));
		return;
	}
	CString idstr;
	idstr.Format(_T("%d"),id);
	//sendData.PostData(_T("dlive.sinaapp.com"),_T("test.php"),_T("class=haha&comtent=tttttt"),_T("http://dlive.sinaapp.com.com"),80);
	sendData.upClassFileToLocal(idstr);
}

BOOL ClocalSearchResult::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->wParam==VK_RETURN && pMsg->message==WM_KEYDOWN)
	{
		if(GetFocus()->GetDlgCtrlID()==IDC_SEARCHKEY){
			CString	str;   
			GetDlgItem(IDC_SEARCHKEY)->GetWindowText(str);
			this->searchArticle(str);
		}
		else if(GetFocus()->GetDlgCtrlID()==IDC_RESULT){
			POSITION pos=m_serResult.GetFirstSelectedItemPosition();
			while(pos){
				int iTem=m_serResult.GetNextSelectedItem(pos);
				CString pageno=m_serResult.GetItemText(iTem,2);
				viewArticle(pageno);
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void ClocalSearchResult::OnCbnSelchangeNowclass()
{
	// TODO: 在此添加控件通知处理程序代码

}
LRESULT ClocalSearchResult::setClassinit(WPARAM wParam,LPARAM lParam)
{
	m_classtreedlg->m_classIsInit=FALSE;
	return 0;
}

//得到输入焦点
void ClocalSearchResult::OnCbnSetfocusNowclass()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_classtreedlg->GetSafeHwnd())
	{
		CRect cbr;
		CRect tcr;
		GetDlgItem(IDC_NOWCLASSNAME)->GetWindowRect(cbr);		
		m_classtreedlg->GetWindowRect(tcr);
		cbr.top+=20;
		cbr.right=cbr.left + tcr.Width();
		cbr.bottom=cbr.top+tcr.Height();
		m_classtreedlg->MoveWindow(cbr);

		m_classtreedlg->ShowWindow(SW_SHOW);
	}
	else
	{
		CRect cbr;
		CRect tcr;
		CComboBox* cb=(CComboBox*)GetDlgItem(IDC_NOWCLASSNAME);
		cb->GetWindowRect(cbr);
		//ScreenToClient(cbr);

		m_classtreedlg->Create(IDD_CLASSTREEDLG,this);
		m_classtreedlg->GetWindowRect(tcr);
		//ScreenToClient(tcr);
		cbr.top+=20;
		cbr.right=cbr.left + tcr.Width();
		cbr.bottom=cbr.top+tcr.Height();
		m_classtreedlg->MoveWindow(cbr);
		m_classtreedlg->ShowWindow(SW_SHOW);
	}

}
void ClocalSearchResult::ChangeClassName(int cid,CString cname,BOOL isActiveChange)
{
	//   if(m_pDoc==NULL)
	//	return;
	CComboBox* pCb=(CComboBox*)this->GetDlgItem(IDC_NOWCLASSNAME);
	//CTreeCtrl* tc=(CTreeCtrl*)(FromHandle(::GetDlgItem(m_classtreedlg->m_hWnd,IDC_CLASSDLGTREE)));
	pCb->SetItemData(0,cid);
	pCb->SetWindowTextW(cname);
	if(!isActiveChange){
		((CButton*)GetDlgItem(IDC_INSERTTODB))->SetCheck(TRUE);   //不管选没选上，反正我是选上了
		CnpadBookApp::getApp()->classChange(cid,cname.GetBuffer());
		cname.ReleaseBuffer();
	}
}
int ClocalSearchResult::getNowClassID()
{
	CComboBox* pCb=(CComboBox*)this->GetDlgItem(IDC_NOWCLASSNAME);
	//CTreeCtrl* tc=(CTreeCtrl*)(FromHandle(::GetDlgItem(m_classtreedlg->m_hWnd,IDC_CLASSDLGTREE)));
	//pCb->SetItemData(0,cid);
	return pCb->GetItemData(0);
}
void ClocalSearchResult::OnEnChangeTitle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString title;
	GetDlgItem(IDC_TITLE)->GetWindowTextW(title);
	CnpadBookApp::getApp()->titleChange(title);
}

void ClocalSearchResult::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//TRACE(L"a__%d\r\n",cy);
	if(pDlgSize)
		pDlgSize->sizeChange(cx,cy);
	// TODO: 在此处添加消息处理程序代码
}

void ClocalSearchResult::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!bShow){
		CnpadBookApp::getApp()->setMenuShowSatue(FALSE);
	}
	// TODO: 在此处添加消息处理程序代码
}

void ClocalSearchResult::OnEnChangeSearchkey()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString title;
	GetDlgItem(IDC_SEARCHKEY)->GetWindowTextW(title);
	if(!title.IsEmpty())
	{
		this->searchArticle(title);

	}
}

void ClocalSearchResult::OnBnClickedInserttodb()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL ischeck=FALSE;
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_INSERTTODB))->GetCheck())
		ischeck=TRUE;
	else
		ischeck=FALSE;
	CString cname;
	CComboBox* pCb=(CComboBox*)this->GetDlgItem(IDC_NOWCLASSNAME);
	//CTreeCtrl* tc=(CTreeCtrl*)(FromHandle(::GetDlgItem(m_classtreedlg->m_hWnd,IDC_CLASSDLGTREE)));
	int cid=pCb->GetItemData(0);
	if(cid==0){
		MessageBox(_T("请选择分类"),_T("ITbook"));
		return;
	}
	pCb->GetWindowTextW(cname);
	CnpadBookApp::getApp()->changSaveToDbStatus(ischeck,cid,cname.GetBuffer());
	cname.ReleaseBuffer();

}

void ClocalSearchResult::OnUpdateTclassadd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
	
}

void ClocalSearchResult::OnUpdateTclassdel(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
}

void ClocalSearchResult::OnUpdateClassrename(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
}

void ClocalSearchResult::OnUpdateUpcarticletodis(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
}

void ClocalSearchResult::OnUpdateUpcarticletoloc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
}

void ClocalSearchResult::OnSaveproject()
{
	// TODO: 在此添加命令处理程序代码
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	HTREEITEM hItem=pTb->GetSelectedItem();
	int pid=pTb->GetItemData(hItem);

	CprojectImport pro(pid,this, hItem);
	if(pro.DoModal()!=IDOK){
		return;
	}
}
HTREEITEM ClocalSearchResult::addClassToTree(HTREEITEM hItem,int cid, CString classname){
	CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	
	HTREEITEM ret=pTb->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
	pTb->Expand(hItem,TVE_EXPAND);
	return ret;
}
void ClocalSearchResult::OnUpdateSaveproject(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(treeMenuStatus);
}

void ClocalSearchResult::OnOpenfromdb()
{
	// TODO: 在此添加命令处理程序代码
	CPoint   point; 
	LVHITTESTINFO  HitTestInfo; 
	GetCursorPos(&point); 
	
	m_serResult.ScreenToClient(&point); 
	HitTestInfo.pt   =   point; 
	HitTestInfo.flags =	LVHT_ONITEM;

	UINT uFlags;
	int item=m_serResult.HitTest(&HitTestInfo);
	
	if(HitTestInfo.iItem!=-1){
		CString id=m_serResult.GetItemText(HitTestInfo.iItem,2);
		viewArticle(id,TRUE);
	}

}
