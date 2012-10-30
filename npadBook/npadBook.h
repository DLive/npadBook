// npadBook.h : npadBook DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "ArticleManager.h"


enum EncodeType {E_UNICODE,E_ANSI,E_UTF8,E_UBOMUTF8};
// CnpadBookApp
// �йش���ʵ�ֵ���Ϣ������� npadBook.cpp
//

class CnpadBookApp : public CWinApp
{
	
public:
	CnpadBookApp();
public:
	
// ��д
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
	BOOL changSaveToDbStatus(BOOL isSave,int cID,LPCTSTR cName);   //����������ݿⰴť
	BOOL addNewInfo(int bufferID);
	articleInfo* findAInfo(int bufferid);
	BOOL activateBufferView(int bufferid);
	DECLARE_MESSAGE_MAP()
};
