#pragma once


// CmyClassTreeDlg �Ի���

class ClocalSearchResult;
class CmyClassTreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CmyClassTreeDlg)

public:
	CmyClassTreeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmyClassTreeDlg();
	
	BOOL m_classIsInit;//�����Ƿ��ʼ��
	//ͼ���б�
	CImageList Cil1;
	//������ʼ��
	BOOL m_classInit(void);
	
	ClocalSearchResult* m_parent;
	//������
	HTREEITEM FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* finLevel,int* curLevel);
// �Ի�������
	enum { IDD = IDD_CLASSTREEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

//	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnTvnSelchangedClassdlgtree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickClassdlgtree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
