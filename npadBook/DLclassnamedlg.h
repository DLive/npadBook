#pragma once


// CDLclassnamedlg �Ի���

class CDLclassnamedlg : public CDialog
{
	DECLARE_DYNAMIC(CDLclassnamedlg)

public:
	CDLclassnamedlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLclassnamedlg();

// �Ի�������
	enum { IDD = IDD_CLASSNAME };

	CString m_name;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
