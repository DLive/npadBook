#pragma once

#include "localSearchResult.h"
#include "DLitbookTree.h"
// CtoolDlg �Ի���
#include "resource.h"
class CtoolDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CtoolDlg)

public:
	CtoolDlg();   // ��׼���캯��
	virtual ~CtoolDlg();

// �Ի�������
	enum { IDD = IDD_TOOLDLG };

	ClocalSearchResult *m_pLocalResult;
	DLitbookTree m_classTree;
	
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LONG OnInitDialog(UINT, LONG);
	//virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateButton(CCmdUI * pCmdUI);
	afx_msg LRESULT OngoodByeLocal(WPARAM wParam,LPARAM lParam);
public:
	afx_msg void OnBnClickedLocalser();

	
};
