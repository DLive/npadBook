#pragma once


// Ctest �Ի���

class Ctest : public CDialog
{
	DECLARE_DYNAMIC(Ctest)

public:
	Ctest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Ctest();

// �Ի�������
	enum { IDD = IDD_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};