// DLlistdrop.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DLlistdrop.h"
#include "CommResours.h"

// DLlistdrop

IMPLEMENT_DYNAMIC(DLlistdrop, CListCtrl)

DLlistdrop::DLlistdrop()
{
	m_iItem=-1;
}

DLlistdrop::~DLlistdrop()
{
}


BEGIN_MESSAGE_MAP(DLlistdrop, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &DLlistdrop::OnNMClick)
END_MESSAGE_MAP()



// DLlistdrop ��Ϣ�������




void DLlistdrop::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����

	if(m_iItem>=0){

		CRect rect;
		this->GetSubItemRect(m_iItem,1, LVIR_BOUNDS,rect);
		// Now scroll if we need to expose the column
		m_pSelClass->MoveWindow(rect,TRUE);
	}
	//CListCtrl::DrawItem(lpDrawItemStruct);
}


BOOL DLlistdrop::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL ret=CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
		
	m_pSelClass =new CComboBox();
	m_pSelClass->Create(WS_CHILD |WS_VISIBLE| WS_VSCROLL |CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL,CRect(0,0,0,0),this,IDC_DISCLASSSELECT);//WS_VISIBLE
	//m_pSelClass->SetParent(CWnd::FromHandle(classlist->m_hWnd));

	return ret;
}


void DLlistdrop::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iItem=pNMItemActivate->iItem;
	*pResult = 0;
}
