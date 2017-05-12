#if !defined(AFX_ONDRAWVIEW_H__66093BBB_BC8A_48BC_BC60_DEF91CFB283E__INCLUDED_)
#define AFX_ONDRAWVIEW_H__66093BBB_BC8A_48BC_BC60_DEF91CFB283E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnDrawView.h : header file
//
#include "TempDetectionDoc.h"
#include "ContentSheet.h"

/////////////////////////////////////////////////////////////////////////////
// COnDrawView view

class COnDrawView : public CView
{
	DECLARE_DYNCREATE(COnDrawView)
protected:
	COnDrawView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(COnListView)
	enum { IDD = IDD_MAIN_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	

// Attributes
public:
	CTempDetectionDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTempDetectionDoc)));
		return (CTempDetectionDoc*) m_pDocument;
	}
//Operations
public:
	CContentSheet m_sheet;
	CContentSheet *pSheet;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
	protected:
		virtual ~COnDrawView();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif
		
		// Generated message map functions
		//{{AFX_MSG(COnListView)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg void OnSize(UINT nType, int cx, int cy);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONDRAWVIEW_H__66093BBB_BC8A_48BC_BC60_DEF91CFB283E__INCLUDED_)
