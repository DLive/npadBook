// DLeasySearch.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DLeasySearch.h"


// DLeasySearch �Ի���

IMPLEMENT_DYNAMIC(DLeasySearch, CDialogBar)

DLeasySearch::DLeasySearch()
{

}

DLeasySearch::~DLeasySearch()
{
}

void DLeasySearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX); 
}


BEGIN_MESSAGE_MAP(DLeasySearch, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog )
END_MESSAGE_MAP()


// DLeasySearch ��Ϣ�������
LONG DLeasySearch::OnInitDialog(UINT wParam, LONG lParam){
	BOOL bRet = HandleInitDialog(wParam, lParam);
	if(!UpdateData(FALSE)){
		TRACE0("Warning, Unalbe to init update.\n");
	}
	// Add Code here

	return bRet;
}