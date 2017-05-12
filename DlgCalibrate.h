#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_LOOPREADER WM_USER+1001
// CDlgCalibrate 对话框

class CDlgCalibrate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalibrate)

public:
	CDlgCalibrate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCalibrate();

// 对话框数据
	enum { IDD = IDD_DIALOG_CALIBRATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCalibrate();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnCbnSelchangeComboSensorId();
	virtual BOOL OnInitDialog();
	CComboBox m_CtlComboSensorID;
	int nIndex_Sensor;
	int nIndex_Ant;
	int nIndex_Reader;
	CString ShowFreq;

	afx_msg void OnCbnSelchangeComboAntId();
	CComboBox m_CtlComboAntID;
	afx_msg void OnBnClickedButtonCalibrateAll();
	afx_msg void OnBnClickedButtonStartMem();
	afx_msg void OnBnClickedButtonStopMem();
	afx_msg void OnBnClickedButtonClear();
	CComboBox m_CtlComboReaderID;
	afx_msg void OnCbnSelchangeComboReader();
	void DataShow(float GetTemperData,int GetFreqData,int StaticTemper,int StaticFreq);
public:
	CProgressCtrl m_CtlProgressCal;
};
