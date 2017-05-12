#pragma once

#include "ContentSheet.h"

// CMainView ������ͼ

class CMainView : public CFormView
{
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMainView();

public:
	enum { IDD = IDD_MAIN_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CContentSheet m_sheet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


