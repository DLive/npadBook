// test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "npadBook.h"
#include "test.h"


// Ctest �Ի���

IMPLEMENT_DYNAMIC(Ctest, CDialog)

Ctest::Ctest(CWnd* pParent /*=NULL*/)
	: CDialog(Ctest::IDD, pParent)
{

}

Ctest::~Ctest()
{
}

void Ctest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Ctest, CDialog)
END_MESSAGE_MAP()


// Ctest ��Ϣ�������
