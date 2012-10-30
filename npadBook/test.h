#pragma once


// Ctest 对话框

class Ctest : public CDialog
{
	DECLARE_DYNAMIC(Ctest)

public:
	Ctest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Ctest();

// 对话框数据
	enum { IDD = IDD_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};