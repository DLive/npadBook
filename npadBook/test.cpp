// test.cpp : 实现文件
//

#include "stdafx.h"
#include "npadBook.h"
#include "test.h"


// Ctest 对话框

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


// Ctest 消息处理程序
