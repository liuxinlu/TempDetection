#pragma once


// CDlgShowFreq �Ի���

class CDlgShowFreq : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgShowFreq)

public:
	CDlgShowFreq();
	virtual ~CDlgShowFreq();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_FREQ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
