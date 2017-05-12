
// TempDetectionView.h : CTempDetectionView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "IconListBox.h"
#include "MainFrm.h"
#include "afxcmn.h"

class CTempDetectionDoc;

class CTempDetectionView : public CFormView
{
protected: // �������л�����
	CTempDetectionView();
	DECLARE_DYNCREATE(CTempDetectionView)

public:
	enum{ IDD = IDD_TEMPDETECTION_FORM };

// ����
public:
	CTempDetectionDoc* GetDocument() const;

// ����
public:
	CMainFrame *pMain;
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CTempDetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButtonST  m_CtlBtnStartMem;
	CButtonST  m_CtlBtnStopMem;
	CImageList m_imgNormal;

	afx_msg void OnBnClickedButtonStartMem();
	afx_msg void OnBnClickedButtonStopMem();
	void InitImageLists();
	void SetButtonStatus(BOOL Flag);
	void StopMem(void);
	void StartMem(void);
	afx_msg void OnNMClickTreeWindows(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_TreeCtl;
//	afx_msg void OnNMCustomdrawTreeWindows(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // TempDetectionView.cpp �еĵ��԰汾
inline CTempDetectionDoc* CTempDetectionView::GetDocument() const
   { return reinterpret_cast<CTempDetectionDoc*>(m_pDocument); }
#endif

