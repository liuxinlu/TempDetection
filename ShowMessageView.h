#pragma once
#include "afxcmn.h"


// CShowMessageView ������ͼ

class CShowMessageView : public CFormView
{
	DECLARE_DYNCREATE(CShowMessageView)

protected:
	CShowMessageView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CShowMessageView();

public:
	enum { IDD = IDD_SHOW_MESSAGE_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	CListCtrl m_CtlListAlarm;
//	afx_msg void OnNMClickListShowMessage(NMHDR *pNMHDR, LRESULT *pResult);
};


