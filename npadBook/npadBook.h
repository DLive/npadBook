// npadBook.h : npadBook DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "ArticleManager.h"


enum EncodeType {E_UNICODE,E_ANSI,E_UTF8,E_UBOMUTF8};
// CnpadBookApp
// 有关此类实现的信息，请参阅 npadBook.cpp
//

class CnpadBookApp : public CWinApp
{
	
public:
	CnpadBookApp();
public:
	
// 重写
public:
	virtual BOOL InitInstance();
	CArticleManager* pArticleManage;
	
	static BOOL isInitDock;
	BOOL saveArticle(int bufferid);
	int articleIsExist(LPCTSTR path,articleInfo* aInfo=NULL);
	static CnpadBookApp *getApp();
	BOOL OnOpenFile(articleInfo *aInfo);
	BOOL deleteTempDir();
	BOOL activeChange(int bufferID);
	BOOL getArticleInfo(articleInfo *aInfo);
	BOOL classChange(int cID,LPCTSTR cName);
	BOOL titleChange(CString title);
	BOOL showDlg(int isInitNPP=FALSE);
	BOOL setMenuShowSatue(BOOL show);
	BOOL removeFile(int bufferID);
	BOOL changSaveToDbStatus(BOOL isSave,int cID,LPCTSTR cName);   //点击存入数据库按钮
	BOOL addNewInfo(int bufferID);
	articleInfo* findAInfo(int bufferid);
	BOOL activateBufferView(int bufferid);
	DECLARE_MESSAGE_MAP()
};
