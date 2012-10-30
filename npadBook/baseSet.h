#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CbaseSet �Ի���

class CbaseSet : public CPropertyPage
{
	DECLARE_DYNAMIC(CbaseSet)

public:
	CbaseSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CbaseSet();

// �Ի�������
	enum { IDD = IDD_BASEPROPERTY };
	
	BOOL CheckAutorun();
	BOOL setAutorun();
	BOOL delAutorun();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAutorun();
	afx_msg void OnBnClickedRelationtxt();
	// ����ļ��Ƿ����
	BOOL CheckFileRelation(const TCHAR* strExt, const TCHAR* strAppKey);
	void RegisterFileRelation(TCHAR *strExt, TCHAR *strAppName, TCHAR *strAppKey, TCHAR *strDefaultIcon, TCHAR *strDescribe);
	void RegisterFileRelationtxt(TCHAR *strExt, TCHAR *strAppKey);
};
