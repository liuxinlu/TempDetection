
// MainFrm.h : CMainFrame ��Ľӿ�
//
#import "c:\Program Files\Common Files\System\ado\msadox.dll" 
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace \
	rename("EOF","adoEOF")rename("BOF","adoBOF")

#include "mscomm.h" //��Ӵ��ڿؼ�
#include "DlgShowAnt1.h"
#include "DlgCalibrate.h"
#pragma once

//�Զ�����Ϣ
#define WM_UPDATETIME	WM_USER+1000

//����ʱ�ӷֱ��ʣ���msΪ��λ 
# define TIMER_ACCURACY 1 

class CCommSplitWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CCommSplitWnd)

	// Implementation
public:
	CCommSplitWnd();
	~CCommSplitWnd();
	int HitTest(CPoint pt)const;//20:00
	DECLARE_MESSAGE_MAP()
	// Generated message map functions
	//{{AFX_MSG(COnListFrame)
	//}}AFX_MSG
};

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CCommSplitWnd m_wndSplitter;
public:
	////////���ڽ�����ز���//////////////////////
	CMSComm m_MSComm;
	unsigned int DotData;
	unsigned int Power_Data;
	unsigned int Freq_Data;
	int Temper_Data;
	BYTE rxdata[864]; //����BYTE���飬�洢��������
	char ReceiveData[288];
	unsigned int ascii2hex(char *buf, int len);

	//���ݿ���ز���
	_variant_t RecordsAffected;
	CStringArray dbtables;
	_RecordsetPtr m_pRecordset;
	void CreateDataBase(void);//�������ݿ��ļ�
	void InsertIntoTest(CString S_Time);
	void UpdateTest(CString e_time);
	CString GetRecordID();
	BOOL DBisOpen();
	void InsertIntoData(CString RecordID,CString ReaderID,CString AntID, CString SensorID,CString Temperature,CString RFPower,CString Frequency,CString RecordTime,CString Notes);

	void MainStatusShow(CDlgShowAnt1* pMainShow,char Reader,char Sensor, int Status,int AntID);
	void MainStatusShowAnt1(char Sensor);
	void MainStatusShowAnt2(char Sensor);
	void MainStatusShowAnt3(char Sensor);
	void MainStatusShowAnt4(char Sensor);

	void MainTemperShow(CDlgShowAnt1* pMainShow,CString Reader,CString Ant,CString Sensor,int SensorID,unsigned int Power,unsigned int Frequence, int Temp);
	void DataOperate(CString Reader,char Ant,char Sensor,unsigned int Power,unsigned int Frequence, int Temp);
	void ActivePage(void);
	int DataFix(CDlgCalibrate* pWndSensorFix,char status,int GetTemperData,int GetFreqData,int StaticTemper,int StaticFreq);

	void OutputLog(LPCTSTR logName, CString msg);
	//��ʱ�����
	long	m_TimerInterval;
	UINT wAccuracy;

// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnComm();
	afx_msg LRESULT OnUpdateTime(WPARAM wParam,LPARAM lParam);      //������Ϣ��Ӧ����
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnUpdateCommunicate(CCmdUI *pCmdUI);
	afx_msg void OnCalibration();
	afx_msg void OnUpdateUserSetPosition(CCmdUI *pCmdUI);
	afx_msg void OnCommunicate();
	afx_msg void OnUpdateCalibration(CCmdUI *pCmdUI);
	afx_msg void OnUserSetPosition();
	afx_msg void OnExit();
	afx_msg void OnUpdateExit(CCmdUI *pCmdUI);
	afx_msg void OnReaderConfig();
	afx_msg void OnUpdateReaderConfig(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void ClearShowMessage(void);
	afx_msg void OnUserSet();
	afx_msg void OnUpdateUserSet(CCmdUI *pCmdUI);
	afx_msg void OnFactorySet();
	afx_msg void OnUpdateFactorySet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFirmware();
	afx_msg void OnUpdateUpdateFirmware(CCmdUI *pCmdUI);
	afx_msg void OnStartMem();
	afx_msg void OnUpdateStartMem(CCmdUI *pCmdUI);
	afx_msg void OnStopMem();
	afx_msg void OnUpdateStopMem(CCmdUI *pCmdUI);
	afx_msg void OnChangeUser();
	afx_msg void OnUpdateChangeUser(CCmdUI *pCmdUI);
	afx_msg void OnPowerControl();
	afx_msg void OnUpdatePowerControl(CCmdUI *pCmdUI);
	afx_msg void OnRefresh();
	afx_msg void OnUpdateRefresh(CCmdUI *pCmdUI);
	void ShowPosition(int ReaderID,bool status);//��ʾÿ���������µĴ�����λ����Ϣ
	void MainTempShow(CString Temp, int Status, CString Ant,int SensorID);//statusΪ״ָ̬ʾ��0Ϊδ����״̬��1Ϊ����״̬
	void SetStatusBar(int index, CString Str);
	afx_msg void OnSetAlarmTemp();
	afx_msg void OnUpdateSetAlarmTemp(CCmdUI *pCmdUI);
	afx_msg void OnSetSilent();
	afx_msg void OnUpdateSetSilent(CCmdUI *pCmdUI);
	afx_msg void OnShowAlarmHistory();
	afx_msg void OnUpdateShowAlarmHistory(CCmdUI *pCmdUI);
	WORD GetCheckCode(const char * pSendBuf, int nEnd);
	void SendCMD(char* pSendBuf);
	afx_msg void OnScanReader();
	afx_msg void OnUpdateScanReader(CCmdUI *pCmdUI);
	afx_msg void OnCtlSingleReader();
	afx_msg void OnUpdateCtlSingleReader(CCmdUI *pCmdUI);
	afx_msg void OnModifyReadrId();
	afx_msg void OnUpdateModifyReadrId(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ReadPositionFromDB(void);
	void UpdateReaderPosition(CString ReaderID, CString Positon);
	void UpdateAlarmTemp(CString ReaderID, CString HighTemp, CString LowTemp);
	void UpdateSensorPositon(CString ReaderID, CString AntID, CString SensorID, CString Positon);
	void UpdateSensorPower(CString ReaderID, CString AntID, CString SensorID, CString Power);
	void ReadINIFile(CString FileName);
	int CountLoop;
	void ShowAllLastData(void);
	void StopTimer();
	void StartTimer(HWND hd,long time);
	void StartMem(void);
	void StopMem(void);
};


