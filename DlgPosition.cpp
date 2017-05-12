// DlgPosition.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgPosition.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern CString SystemIniFilePath;//保存系统相关参数的文件
extern CStringArray strReaderPositionArray;//保存读卡器位置信息30大小
extern CStringArray strSensorPositionArray;//保存传感器位置信息30*4*12大小


// CDlgPosition 对话框

IMPLEMENT_DYNAMIC(CDlgPosition, CDialogEx)

CDlgPosition::CDlgPosition(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPosition::IDD, pParent)
	, nIndexAnt(0)
	, nIndexSensor(0)
	, nIndexReader(0)
{

}

CDlgPosition::~CDlgPosition()
{
}

void CDlgPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POSITION, m_CtlListPosition);
	DDX_Control(pDX, IDC_COMBO_LIST_ANT, m_CtlComboAnt);
	DDX_Control(pDX, IDC_LIST_POSITION_READER, m_CtlListReaderPosition);
}


BEGIN_MESSAGE_MAP(CDlgPosition, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgPosition::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgPosition::OnBnClickedButtonClear)
	ON_NOTIFY(NM_CLICK, IDC_LIST_POSITION, &CDlgPosition::OnNMClickListPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_LIST_ANT, &CDlgPosition::OnCbnSelchangeComboListAnt)
//	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_POSITION_READER, &CDlgPosition::OnNMClickListPositionReader)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_READER, &CDlgPosition::OnBnClickedButtonSaveReader)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_READER, &CDlgPosition::OnBnClickedButtonClearReader)
END_MESSAGE_MAP()


// CDlgPosition 消息处理程序


void CDlgPosition::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,strSensor;
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	GetDlgItem(IDC_EDIT_POSITION)->GetWindowTextA(strSensor);
	GetDlgItem(IDC_EDIT_SENSOR)->GetWindowTextA(str);
	CString reader,ant;
	reader.Format("%d",nIndexReader+1);
	ant.Format("%d",nIndexAnt+1);
	pMain->UpdateSensorPositon(reader,ant,str,strSensor);

	strSensorPositionArray.SetAt(nIndexReader*4*12+nIndexAnt*12+nIndexSensor,strSensor);

	m_CtlListPosition.DeleteAllItems();
	for (int i = 0; i < 12; i++)
	{
		CString str,strSensor;
		str.Format("%d",i+1);
		str="传感器"+str;
		m_CtlListPosition.InsertItem(i,"");
		m_CtlListPosition.SetItemText(i,0,str);
		m_CtlListPosition.SetItemText(i,1,strSensorPositionArray.GetAt(nIndexReader*4*12+nIndexAnt*12+i));
		str.FreeExtra();
		str.Empty();
	}
}


void CDlgPosition::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_POSITION)->SetWindowTextA("");
}


BOOL CDlgPosition::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndexAnt=0;
	CComboBox*   pComb_Ant   =   (CComboBox*)GetDlgItem(IDC_COMBO_LIST_ANT);   
	ASSERT(pComb_Ant);   
	pComb_Ant->SetCurSel(nIndexAnt);

	m_CtlListReaderPosition.DeleteAllItems();
	m_CtlListReaderPosition.InsertColumn(0,"读卡器号");
	m_CtlListReaderPosition.InsertColumn(1,"位置标记");
	m_CtlListReaderPosition.SetColumnWidth(0,62);
	m_CtlListReaderPosition.SetColumnWidth(1,150);
	m_CtlListReaderPosition.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	
	for (int i = 0; i < 30; i++)
	{
		CString str;
		str.Format("%d",i+1);
		str="读卡器"+str;
		m_CtlListReaderPosition.InsertItem(i,"");
		m_CtlListReaderPosition.SetItemText(i,0,str);
		m_CtlListReaderPosition.SetItemText(i,1,strReaderPositionArray.GetAt(i));
		str.FreeExtra();
		str.Empty();
	}
	
	/////////////////////////////////////////////////////////////////
	m_CtlListPosition.DeleteAllItems();
	m_CtlListPosition.InsertColumn(0,"传感器号");
	m_CtlListPosition.InsertColumn(1,"位置标记");
	m_CtlListPosition.SetColumnWidth(0,62);
	m_CtlListPosition.SetColumnWidth(1,150);
	m_CtlListPosition.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPosition::OnNMClickListPosition(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = NULL;
	nIndexSensor= -1;
	pos = m_CtlListPosition.GetFirstSelectedItemPosition();
	nIndexSensor = m_CtlListPosition.GetNextSelectedItem(pos);
	if (nIndexSensor>-1)
	{
		CString str;
		GetDlgItem(IDC_EDIT_POSITION)->SetWindowTextA(strSensorPositionArray.GetAt(nIndexReader*4*12+nIndexAnt*12+nIndexSensor));
		str.Format("%d",nIndexSensor+1);
		GetDlgItem(IDC_EDIT_SENSOR)->SetWindowTextA(str);
		str.FreeExtra();
		str.Empty();
	}
	*pResult = 0;
}


void CDlgPosition::OnCbnSelchangeComboListAnt()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_POSITION)->SetWindowTextA("");
	GetDlgItem(IDC_EDIT_SENSOR)->SetWindowTextA("");

	nIndexAnt = m_CtlComboAnt.GetCurSel();	
	m_CtlListPosition.DeleteAllItems();
	for (int i = 0; i < 12; i++)
	{
		CString str,strSensor;
		str.Format("%d",i+1);
		str="传感器"+str;
		m_CtlListPosition.InsertItem(i,"");
		m_CtlListPosition.SetItemText(i,0,str);
		m_CtlListPosition.SetItemText(i,1,strSensorPositionArray.GetAt(nIndexReader*4*12+nIndexAnt*12+i));
		str.FreeExtra();
		str.Empty();
	}
}



//void CDlgPosition::OnClose()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
//	
//	//pMain->ActivePage();
//	//pMain->ShowPosition(0);
//	//pMain->ShowPosition(1);
//	//pMain->ShowPosition(2);
//	//pMain->ShowPosition(3);
//
//	CDialogEx::OnClose();
//}


void CDlgPosition::OnNMClickListPositionReader(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = NULL;
	nIndexReader= -1;
	pos = m_CtlListReaderPosition.GetFirstSelectedItemPosition();
	nIndexReader = m_CtlListReaderPosition.GetNextSelectedItem(pos);
	if (nIndexReader>-1)
	{
		CString str,strSensor;
		GetDlgItem(IDC_EDIT_POSITION_READER)->SetWindowTextA(strReaderPositionArray.GetAt(nIndexReader));
		str.Format("%d",nIndexReader+1);
		GetDlgItem(IDC_EDIT_READER)->SetWindowTextA(str);
		str.FreeExtra();
		str.Empty();
		strSensor.FreeExtra();
		strSensor.Empty();

		m_CtlListPosition.DeleteAllItems();
		for (int i = 0; i < 12; i++)
		{
			CString str,strSensor;
			str.Format("%d",i+1);
			str="传感器"+str;
			m_CtlListPosition.InsertItem(i,"");
			m_CtlListPosition.SetItemText(i,0,str);
			m_CtlListPosition.SetItemText(i,1,strSensorPositionArray.GetAt(nIndexReader*4*12+nIndexAnt*12+i));
			str.FreeExtra();
			str.Empty();
		}

	}
	*pResult = 0;
}


void CDlgPosition::OnBnClickedButtonSaveReader()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	CString strReader,strPosition;
	GetDlgItem(IDC_EDIT_READER)->GetWindowTextA(strReader);
	GetDlgItem(IDC_EDIT_POSITION_READER)->GetWindowTextA(strPosition);
	pMain->UpdateReaderPosition(strReader,strPosition);
	strReaderPositionArray.SetAt(atoi(strReader)-1,strPosition);

	m_CtlListReaderPosition.DeleteAllItems();
	for (int i = 0; i < 30; i++)
	{
		CString str;
		str.Format("%d",i+1);
		str="读卡器"+str;
		m_CtlListReaderPosition.InsertItem(i,"");
		m_CtlListReaderPosition.SetItemText(i,0,str);
		m_CtlListReaderPosition.SetItemText(i,1,strReaderPositionArray.GetAt(i));
		str.FreeExtra();
		str.Empty();
	}
}


void CDlgPosition::OnBnClickedButtonClearReader()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_POSITION_READER)->SetWindowTextA("");
}
