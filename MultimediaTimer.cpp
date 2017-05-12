#include "StdAfx.h"
#include "MultimediaTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MultimediaTimer::MultimediaTimer(void)
{
	m_nTimerID = 0;
	m_nType = TIME_PERIODIC;
	m_nDelay = 1000;
	m_nResolution = 1;
}

MultimediaTimer::~MultimediaTimer(void)
{	
}

int MultimediaTimer::CreateTimer()
{
	if ( timeBeginPeriod(m_nResolution) != TIMERR_NOERROR  )
		return -1;

	m_nTimerID = timeSetEvent(m_nDelay, m_nResolution, (LPTIMECALLBACK)TimerCallBackPro, (DWORD)this, m_nType);
	if ( m_nTimerID == 0)
	{
		timeEndPeriod(m_nResolution);
		return -2;		
	}
	return 0;
}

int MultimediaTimer::DestroyTimer()
{
	if ( m_nTimerID )
	{
		timeKillEvent(m_nTimerID);
		timeEndPeriod(m_nResolution);
		m_nTimerID = 0;
	}
	return 0;
}

int MultimediaTimer::SetTimerResolution( int nResolution )
{
	int nPeriodMin;  //ϵͳ֧�ֵ���Сֵ
	int nPeriodMax;  //ϵͳ֧�ֵ����ֵ

	//��û���֧�ֵķֱ�·��Χ
	if ( GetSystemPeriod(nPeriodMin, nPeriodMax) != 0 )
		return -1;

	//�����������֧�ַ�Χ����min������֧�ֵ���Сֵ��1��������
	if ( nResolution < nPeriodMin || nResolution > nPeriodMax )
	{
		m_nResolution = min( max(nPeriodMin, 1), nPeriodMax );
	}
	else 
	{
		m_nResolution = nResolution;
	}

	return 0;
}

int MultimediaTimer::GetTimerResolution() const
{
	return m_nResolution;
}

int MultimediaTimer::GetSystemPeriod(int &nPeriodMix, int &nPeriodMax)
{
	TIMECAPS  tc;  
	//���������һ����ý�嶨ʱ��       
	if ( timeGetDevCaps(&tc,sizeof(TIMECAPS)) != TIMERR_NOERROR )
		return -1;

	nPeriodMix = tc.wPeriodMin;
	nPeriodMax = tc.wPeriodMax;
	return 0;
}

int MultimediaTimer::SetTimerDelay(int nDelay)
{
	m_nDelay = nDelay;
	return 0;
}

int MultimediaTimer::GetTimerDelay() const
{
	return m_nDelay;
}

void MultimediaTimer::Run()
{

}

void MultimediaTimer::TimerCallBackPro(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2)
{
	MultimediaTimer *pMulTime = (MultimediaTimer *)dwUser; 
	pMulTime->Run();
}

void MultimediaTimer::SetEventType(int nEventType)
{
	m_nType = nEventType;
}

int MultimediaTimer::GetEventType() const
{
	return m_nType;
}