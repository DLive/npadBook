// DLupToDistancedlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DLupToDistancedlg.h"


// CDLupToDistancedlg �Ի���

IMPLEMENT_DYNAMIC(CDLupToDistancedlg, CDialog)

CDLupToDistancedlg::CDLupToDistancedlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDLupToDistancedlg::IDD, pParent)
{

}

CDLupToDistancedlg::~CDLupToDistancedlg()
{

}

void CDLupToDistancedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDLupToDistancedlg, CDialog)
	ON_WM_CREATE()
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDOK, &CDLupToDistancedlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDLupToDistancedlg ��Ϣ�������

int CDLupToDistancedlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
LONG CDLupToDistancedlg::OnInitDialog(UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);

	if (!UpdateData(FALSE))

	{
		TRACE0("Warning: UpdateData failed during dialog init.\n");
	}
	CComboBox *sta=(CComboBox*)GetDlgItem(IDC_STATUS);
	sta->InsertString(0,_T("�ݸ�"));
	sta->InsertString(1,_T("����"));
	sta->SetCurSel(0);

	return bRet;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDLupToDistancedlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_status=((CComboBox*)GetDlgItem(IDC_STATUS))->GetCurSel()==0?"draft":"public";
	CDialog::OnOK();
}
