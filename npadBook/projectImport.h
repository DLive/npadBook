#pragma once

#include "localSearchResult.h"
#include "InputDB.h"
// CprojectImport 对话框

class CprojectImport : public CDialog
{
	DECLARE_DYNAMIC(CprojectImport)

public:
	CprojectImport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CprojectImport();

	CprojectImport(int pid,ClocalSearchResult *pLocalDlg, HTREEITEM hItem,CWnd* pParent = NULL);
// 对话框数据
	enum { IDD = IDD_PROJECTDLG };

	CString m_rootDir;
	CStringArray m_filterFile;
	CStringArray m_filterDir;
	int m_pid;
	HTREEITEM m_hItem;
	ClocalSearchResult *m_pLocalDlg;
	CInputDB* pInputDB;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	bool findFile(int pId, CString pathName, HTREEITEM hItem);
	BOOL addFileToDB(int cid, CString filePath);
	void Split(CString source, CStringArray& dest, CString division);
	BOOL isNeedFile(CString fileName);
	BOOL filterDir(CString Dir);
public:
	afx_msg LONG OnInitDialog ( UINT, LONG );
	afx_msg void OnBnClickedGetprojectdir();
	afx_msg void OnBnClickedImportbegin();
};
