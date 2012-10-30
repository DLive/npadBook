#pragma once
#include "localSearchResult.h"
//
// CpropertyDlg �Ի���
#include "myClassTreeDlg.h"

class CpropertyDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CpropertyDlg)

public:
	CpropertyDlg();   // ��׼���캯��
	virtual ~CpropertyDlg();

// �Ի�������
	enum { IDD = IDD_PROPERTY };
	CDocument* m_pDoc;
	ClocalSearchResult* m_pLocalResult;//��ѯ�Ի���
	
	
	//������
	BOOL m_classdlgIsCreate;//false is not 
	CmyClassTreeDlg* m_classtreedlg;
	
	
	//�����ʼ��
	void classInfoInit();

	void ChangeClassName(int cid,CString cname);//��������
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LONG OnInitDialog ( UINT, LONG );
	afx_msg LRESULT OnchangeInfo(WPARAM, LPARAM);
	afx_msg LRESULT setClassinit(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnNMDblclkClasstree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeNowclass();

	afx_msg void OnCbnSetfocusNowclass();
	afx_msg void OnEnChangeTitle();
	afx_msg void OnEnKillfocusAuthor();
	afx_msg void OnEnKillfocusKeyword();
	afx_msg void OnCbnSelchangeDifficulty();
	afx_msg void OnBnClickedInserttodb();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnUpdateButtontest(CCmdUI * pCmdUI);
	afx_msg void OnBnClickedSavelocal();
};
