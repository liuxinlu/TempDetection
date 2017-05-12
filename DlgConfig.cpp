// DlgConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern bool PortOpenFlag;//true已经打开 false未打开端口
char ConfigReaderCMD[15]={0x00,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//读取器配置

// CDlgConfig 对话框

IMPLEMENT_DYNAMIC(CDlgConfig, CDialogEx)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfig::IDD, pParent)
{

}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ANT, m_CtlComboAnt);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_CtlBtnDown);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_CtlBtnClose);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDlgConfig::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgConfig::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT, &CDlgConfig::OnCbnSelchangeComboAnt)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgConfig::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgConfig 消息处理程序


void CDlgConfig::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (PortOpenFlag)
	{
		CString strPath;
		::GetModuleFileName( NULL, strPath.GetBuffer(MAX_PATH), MAX_PATH );
		strPath.ReleaseBuffer();
		strPath = strPath.Left(strPath.ReverseFind('\\')); 

		switch (nIndexReaderID)
		{
		case 0:
			strPath=strPath+"\\ReaderConfigFiles\\Reader01";
			break;
		case 1:
			strPath=strPath+"\\ReaderConfigFiles\\Reader02";
			break;
		case 2:
			strPath=strPath+"\\ReaderConfigFiles\\Reader03";
			break;
		case 3:
			strPath=strPath+"\\ReaderConfigFiles\\Reader04";
			break;
		case 4:
			strPath=strPath+"\\ReaderConfigFiles\\Reader05";
			break;
		case 5:
			strPath=strPath+"\\ReaderConfigFiles\\Reader06";
			break;
		case 6:
			strPath=strPath+"\\ReaderConfigFiles\\Reader07";
			break;
		case 7:
			strPath=strPath+"\\ReaderConfigFiles\\Reader08";
			break;
		case 8:
			strPath=strPath+"\\ReaderConfigFiles\\Reader09";
			break;
		case 9:
			strPath=strPath+"\\ReaderConfigFiles\\Reader10";
			break;
		case 10:
			strPath=strPath+"\\ReaderConfigFiles\\Reader11";
			break;
		case 11:
			strPath=strPath+"\\ReaderConfigFiles\\Reader12";
			break;
		case 12:
			strPath=strPath+"\\ReaderConfigFiles\\Reader13";
			break;
		case 13:
			strPath=strPath+"\\ReaderConfigFiles\\Reader14";
			break;
		case 14:
			strPath=strPath+"\\ReaderConfigFiles\\Reader15";
			break;
		case 15:
			strPath=strPath+"\\ReaderConfigFiles\\Reader16";
			break;
		case 16:
			strPath=strPath+"\\ReaderConfigFiles\\Reader17";
			break;
		case 17:
			strPath=strPath+"\\ReaderConfigFiles\\Reader18";
			break;
		case 18:
			strPath=strPath+"\\ReaderConfigFiles\\Reader19";
			break;
		case 19:
			strPath=strPath+"\\ReaderConfigFiles\\Reader20";
			break;
		case 20:
			strPath=strPath+"\\ReaderConfigFiles\\Reader21";
			break;
		case 21:
			strPath=strPath+"\\ReaderConfigFiles\\Reader22";
			break;
		case 22:
			strPath=strPath+"\\ReaderConfigFiles\\Reader23";
			break;
		case 23:
			strPath=strPath+"\\ReaderConfigFiles\\Reader24";
			break;
		case 24:
			strPath=strPath+"\\ReaderConfigFiles\\Reader25";
			break;
		case 25:
			strPath=strPath+"\\ReaderConfigFiles\\Reader26";
			break;
		case 26:
			strPath=strPath+"\\ReaderConfigFiles\\Reader27";
			break;
		case 27:
			strPath=strPath+"\\ReaderConfigFiles\\Reader28";
			break;
		case 28:
			strPath=strPath+"\\ReaderConfigFiles\\Reader29";
			break;
		case 29:
			strPath=strPath+"\\ReaderConfigFiles\\Reader30";
			break;
		default:
			break;
		}
		switch (nIndex_Ant)
		{
		case 0:
			strPath=strPath+"\\file1.txt";
			break;
		case 1:
			strPath=strPath+"\\file2.txt";
			break;
		case 2:
			strPath=strPath+"\\file3.txt";
			break;
		case 3:
			strPath=strPath+"\\file4.txt";
			break;
		case 4:
			strPath=strPath+"\\file4.txt";
			break;
		default:
			break;
		}
		//读取txt文件并进行解析
		CStdioFile file;
		file.Open(strPath,CFile::modeRead);
		CString strLine;
		CString FileStr;
		while(file.ReadString(strLine))
		{
			FileStr=FileStr+strLine;
		}
		file.Close();

		//串口发送数据
		CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
		int strLen = FileStr.GetLength();
		char ch[1000]; 
		for (int i = 0; i < 1000; i++)
		{
			ch[i]=0xff;
		}
		if ((strLen%8)==0)
		{
			GetDlgItem(IDC_STATIC_DOWN)->SetWindowText("配置文件下载中……");
			for (int i = 0; i < strLen/2; i++)
			{
				int temp=strtol(FileStr.Mid(2*i,2),NULL,16);
				ch[i]=(char)(temp&0x00ff);
			}
			ConfigReaderCMD[0]=(char)(nIndexReaderID+1);
			strLen=strLen/2;
			int i,j;
			if ((strLen%8)!=0)
			{
				for (j=0;j<=(strLen/8);j++)
				{
					ConfigReaderCMD[3]=(char)(j&0x00ff);
					ConfigReaderCMD[2]=(char)((j&0xff00)>>8);
					if (j==strLen/8)
					{
						ConfigReaderCMD[4]=0x80|(strLen%8);
					} 
					else
					{
						ConfigReaderCMD[4]=0x00;
					}

					for(i=0;i<8;i++)
					{
						if ((j*8+i)>strLen)
						{
							ConfigReaderCMD[5+i]=0x00;
						}
						else
						{
							ConfigReaderCMD[5+i]=ch[j*8+i];
						}
					}
					pMain->SendCMD(ConfigReaderCMD);
					//Sleep(50);//由于下位机接受处理速度稍慢，这里延时15ms
				}
			}
			else
			{
				for (j=0;j<(strLen/8);j++)
				{
					ConfigReaderCMD[3]=(char)(j&0x00ff);
					ConfigReaderCMD[2]=(char)((j&0xff00)>>8);
					if (j==(strLen/8)-1)
					{
						ConfigReaderCMD[4]=0xff;
					} 
					else
					{
						ConfigReaderCMD[4]=0x00;
					}
					for(i=0;i<8;i++)
					{
						ConfigReaderCMD[5+i]=ch[j*8+i];
					}
					pMain->SendCMD(ConfigReaderCMD);
					Sleep(50);//由于下位机接受处理速度稍慢，这里延时15ms
				}
			}
			GetDlgItem(IDC_STATIC_DOWN)->SetWindowText("");
			AfxMessageBox("配置文件下载完成!");
		}else
		{
			AfxMessageBox("文件数据长度有误！");
		}
	} 
	else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}

}


void CDlgConfig::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CDlgConfig::OnCbnSelchangeComboAnt()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndex_Ant = m_CtlComboAnt.GetCurSel();

}


BOOL CDlgConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndex_Ant=0;
	nIndexReaderID=0;
	CComboBox*   pComb_ant   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT);   
	ASSERT(pComb_ant);   
	pComb_ant->SetCurSel(nIndex_Ant);
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReaderID);
	m_CtlBtnDown.SetIcon(IDI_ICON_DOWN/*导入的那个icon ID*/);
	m_CtlBtnDown.SetFlat(TRUE/*让这个按钮扁平还是立体*/);
	m_CtlBtnDown.SetTooltipText("下载");
	m_CtlBtnClose.SetIcon(IDI_ICON_CLOSE/*导入的那个icon ID*/);
	m_CtlBtnClose.SetFlat(TRUE/*让这个按钮扁平还是立体*/);
	m_CtlBtnClose.SetTooltipText("下载");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgConfig::OnCbnSelchangeComboReader()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReaderID = m_CtlComboReaderID.GetCurSel();	
}
