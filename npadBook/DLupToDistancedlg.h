#pragma once

// CDLupToDistancedlg �Ի���
#include "resource.h"
class CDLupToDistancedlg : public CDialog
{
	DECLARE_DYNAMIC(CDLupToDistancedlg)

public:
	CDLupToDistancedlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLupToDistancedlg();

	CStringA m_status;
// �Ի�������
	enum { IDD = IDD_UPTODISTANCEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnInitDialog ( UINT, LONG );
	afx_msg void OnBnClickedOk();
};
