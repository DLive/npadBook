#pragma once

#include "resource.h"
// CDLupClass �Ի���

class CDLupClass : public CDialog
{
	DECLARE_DYNAMIC(CDLupClass)

public:
	CDLupClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLupClass();

	int m_selIndex;

	BOOL getLocClass();
	BOOL getSerClass();
	CComboBox *m_pSelClass;
	CListCtrl *m_classList;
// �Ի�������
	enum { IDD = IDD_CLASSUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnNMClickClasslist(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnLvnItemActivateClasslist(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMCustomdrawClasslist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeDclasslist();
};