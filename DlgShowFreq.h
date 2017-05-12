#pragma once


// CDlgShowFreq 对话框

class CDlgShowFreq : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgShowFreq)

public:
	CDlgShowFreq();
	virtual ~CDlgShowFreq();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOW_FREQ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
