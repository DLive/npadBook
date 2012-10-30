#pragma once
#include <afxcmn.h>
#include <afxwin.h>
#include "Resource.h"
#include "myClassTreeDlg.h"
#include "npadBook.h"
#include "DLDlgSizeing.h"
// ClocalSearchResult 对话框

class ClocalSearchResult : public CDialog
{
	DECLARE_DYNAMIC(ClocalSearchResult)

public:
	ClocalSearchResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ClocalSearchResult();
	

// 对话框数据
	enum { IDD = IDD_LOCALRESULT };

	//BOOL Create();

protected:
	
	CDialogBar *m_pDialogBar;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


protected:
	
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg LONG OnInitDialog ( UINT, LONG );
public:
	//图标列表
	CImageList Cil1;
	// 搜索结果列表
	CListCtrl m_serResult;
	void getexeurl(CString* purl);
	// 按标题搜索
	bool searchArticle(CString &title);
	//按分类搜索
	bool searchClassId(int cid);
	//搜索并添加
	bool searchAndAdd(CString sqlcmd);
	afx_msg void OnNMDblclkResult(NMHDR *pNMHDR, LRESULT *pResult);
	// 字符串分割
	void stringSplit(CString& source, CString& result, CString division);
	//编辑分类初始值
	CString m_beginClassname;
	//打开文章
	BOOL viewArticle(CString articleid,BOOL isFromDB=FALSE);
	//分类树
	void classInfoInit();
	//树右键菜单状态
	BOOL treeMenuStatus;
	CmyClassTreeDlg* m_classtreedlg;
	void ChangeClassName(int cid,CString cname,BOOL isActiveChange=FALSE);
	int getNowClassID();
	void OnCbnSetfocusNowclass();
	void OnCbnSelchangeNowclass();
	CString getNowTitle();
	BOOL activeChange(articleInfo * pInfo);
	BOOL activeNullInfo();
	int addClass(int pid,CString classname);
	HTREEITEM addClassToTree(HTREEITEM hItem,int cid, CString classname);
	void TravelTree(CTreeCtrl* pTb, HTREEITEM hItem ,CString &ids);
	//分页数据
	int		m_pageCount;
	int		m_pageSize;
	int		m_pageIndex;
	CString m_sqlCondition;
	void setPageButtonInfo();
	//自适应尺寸
	DLDlgSizeing* pDlgSize;
	BOOL m_treeIsInit;//类树是否初始化

	HTREEITEM FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* finLevel,int* curLevel);

	afx_msg LRESULT setClassinit(WPARAM,LPARAM);

	afx_msg void OnBnClickedLocalser();
	afx_msg void OnBnClickedDelete();

	// 删除本地文件按钮复选框
	CButton m_deletLocalFile;
	BOOL ClassInit(void);
	afx_msg void OnTvnItemexpandingClasstree(NMHDR *pNMHDR, LRESULT *pResult); //树展开
	afx_msg void OnNMRClickClasstree(NMHDR *pNMHDR, LRESULT *pResult);//树右击
	afx_msg void OnTvnEndlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult);//编辑树
	afx_msg void OnTvnBeginlabeleditClasstree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnTclassadd();
	afx_msg void OnTclassdel();
	afx_msg void OnNMDblclkResultclastree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddrootclass();
	afx_msg void OnBnClickedAfterpage();
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnCbnSelchangeJmppage();
	afx_msg void OnClassReName();
//	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg void OnUpdateButtonPrepage(CCmdUI * pCmdUI);
	afx_msg void OnUpdateButtonAfterpage(CCmdUI * pCmdUI);
	afx_msg void OnNMRClickResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUptoserver();
	afx_msg void OnUptolocal();
	afx_msg void OnUpcarticletodis();
	afx_msg void OnUpcarticletoloc();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeTitle();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEnChangeSearchkey();
	afx_msg void OnBnClickedInserttodb();
	afx_msg void OnUpdateTclassadd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTclassdel(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClassrename(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpcarticletodis(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpcarticletoloc(CCmdUI *pCmdUI);
	afx_msg void OnSaveproject();
	afx_msg void OnUpdateSaveproject(CCmdUI *pCmdUI);
	afx_msg void OnOpenfromdb();
};
