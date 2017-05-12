
// TempDetectionView.h : CTempDetectionView 类的接口
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
protected: // 仅从序列化创建
	CTempDetectionView();
	DECLARE_DYNCREATE(CTempDetectionView)

public:
	enum{ IDD = IDD_TEMPDETECTION_FORM };

// 特性
public:
	CTempDetectionDoc* GetDocument() const;

// 操作
public:
	CMainFrame *pMain;
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CTempDetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // TempDetectionView.cpp 中的调试版本
inline CTempDetectionDoc* CTempDetectionView::GetDocument() const
   { return reinterpret_cast<CTempDetectionDoc*>(m_pDocument); }
#endif

