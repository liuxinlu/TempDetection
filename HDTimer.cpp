// HDTimer.cpp: implementation of the CHDTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MMTimerT.h"
#include "HDTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TARGET_RESOLUTION 1         // 1-millisecond target resolution

void CALLBACK TimerHandler( UINT uID, UINT uMsg, DWORD dwUser,DWORD dw1, DWORD dw2);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHDTimer::CHDTimer(CWnd* pParent)
{
	if (pParent!=NULL) 
		m_pParentWnd = pParent;
	else
		m_pParentWnd = NULL;
	m_uiTimerID = 0;

}

CHDTimer::~CHDTimer()
{

}

bool CHDTimer::CreateTimer(unsigned long msInterval,
						   unsigned long ulEventType,
						   unsigned long ulMsg,
						   CWnd* pParent)
{
	//设置定时器精度，为1ms
	TIMECAPS tc;
	UINT     wTimerRes;
	
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
	{
		return false;
	}
	wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes);	

	//初始化定时器参数
	m_ulInterval = msInterval;
	m_ulEventType = ulEventType ;
	m_ulMsg = ulMsg;
	
	if((m_pParentWnd==NULL)&&(pParent!=NULL))
		m_pParentWnd = pParent;
	return true;
}

//启动定时器
unsigned int CHDTimer::StartTimer()
{
	if (m_pParentWnd==NULL)
	{
		
	}

	m_uiTimerID = timeSetEvent(
		m_ulInterval,		//定时器间隔，毫秒
        TARGET_RESOLUTION,
		TimerHandler,
        (DWORD)this,
        TIME_PERIODIC);    

    return m_uiTimerID;
}

void CHDTimer::SendTimerMsg()
{
	::PostMessage(m_pParentWnd->m_hWnd,m_ulMsg,m_uiTimerID,m_ulInterval);
//	::SendMessage(m_pParentWnd->m_hWnd,m_ulMsg,m_uiTimerID,m_ulInterval);
}

void CHDTimer::StopTimer()
{
    if(m_uiTimerID) // is timer event pending?
	{                
        timeKillEvent(m_uiTimerID);  // cancel the event
        m_uiTimerID = 0;
    }
}
void CALLBACK TimerHandler( UINT uID, UINT uMsg, DWORD dwUser,DWORD dw1, DWORD dw2)
{
    CHDTimer* pTimer;             // pointer to sequencer data 
    pTimer = (CHDTimer*)dwUser;
	//::PostMessage(pTimer->m_pParentWnd->m_hWnd,pTimer->m_ulMsg,pTimer->m_uiTimerID,pTimer->m_ulInterval);
	pTimer->SendTimerMsg();  	
}


