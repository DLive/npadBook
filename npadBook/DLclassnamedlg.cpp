// DLclassnamedlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DLclassnamedlg.h"


// CDLclassnamedlg �Ի���

IMPLEMENT_DYNAMIC(CDLclassnamedlg, CDialog)

CDLclassnamedlg::CDLclassnamedlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDLclassnamedlg::IDD, pParent)
{

}

CDLclassnamedlg::~CDLclassnamedlg()
{
}

void CDLclassnamedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDLclassnamedlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDLclassnamedlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDLclassnamedlg ��Ϣ�������

void CDLclassnamedlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_CLASSNAME,m_name);
	OnOK();
}
