#pragma once


// DLeasySearch �Ի���

class DLeasySearch : public CDialogBar
{
	DECLARE_DYNAMIC(DLeasySearch)

public:
	DLeasySearch();   // ��׼���캯��
	virtual ~DLeasySearch();

// �Ի�������
	enum { IDD = IDD_EASYSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LONG OnInitDialog ( UINT, LONG );

	DECLARE_MESSAGE_MAP()
};
