#pragma once


// DLitbookTree

class DLitbookTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(DLitbookTree)

public:
	DLitbookTree();
	virtual ~DLitbookTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//ͼ���б�
	CImageList Cil1;
	 HTREEITEM FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* finLevel,int* curLevel); //���ҽ��
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��
	BOOL classInit(void);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


