#pragma once


// CInputDB

#include "ArticleManager.h"

class CInputDB : public CWnd
{
	DECLARE_DYNAMIC(CInputDB)

public:
	CInputDB();
	//CInputDB(CDocument *pDoc);
	virtual ~CInputDB();

	bool getText(articleInfo* aInfo,BOOL isSaveAS=FALSE);
	BOOL m_getinfo(CString pathname,CString type);
protected:
	CDocument *m_pDoc;//ÎÄµµÖ¸Õë
	CString m_text;
protected:
	DECLARE_MESSAGE_MAP()
};


