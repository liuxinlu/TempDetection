// DlgShowFreq.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgShowFreq.h"
#include "afxdialogex.h"


// CDlgShowFreq 对话框

IMPLEMENT_DYNAMIC(CDlgShowFreq, CPropertyPage)

CDlgShowFreq::CDlgShowFreq()
	: CPropertyPage(CDlgShowFreq::IDD)
{

}

CDlgShowFreq::~CDlgShowFreq()
{
}

void CDlgShowFreq::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowFreq, CPropertyPage)
END_MESSAGE_MAP()


// CDlgShowFreq 消息处理程序
