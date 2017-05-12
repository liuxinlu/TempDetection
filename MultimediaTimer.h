/*
*���ߣ� FreeBird
*��������ý�嶨ʱ��
*���ʱ�䣺2013/7/14
*ʹ�÷��������غ���Run
*         1.�ȵ���SetTimerResolution���÷ֱ���
*         2.����SetEventType�����¼�����
*         3.����GetTimerDelayʱ������
*         ����1��3������Ĭ�ϣ�m_nType = TIME_PERIODIC;m_nDelay = 3000;m_nResolution = 1;
*         4.������ʱ��CreateTimer
*         5.��������ٶ�ʱ��DestroyTimer
*/

#pragma once
#include <MMSystem.h>
#pragma comment(lib, "Winmm.lib")

class MultimediaTimer
{
public:
	MultimediaTimer(void);
	virtual ~MultimediaTimer(void);

public:
	//������ý�嶨ʱ��
	int CreateTimer();

	//���ٶ�ý�嶨ʱ��
	int DestroyTimer();

	//���÷ֱ��ʣ���С����1ms��������õĳ�������֧�ֵķ�Χ������min������֧�ֵ���Сֵ��1��������
	int SetTimerResolution(int nResolution); 

	//��ȡ�������Լ��趨�ķֱ���
	int GetTimerResolution() const;

	//�����Ժ���ָ���¼�������
	int SetTimerDelay(int nDelay);

	//��ȡ��ʱ��ʱ������
	int GetTimerDelay() const;

	//���ö�ʱ���¼�����
	void SetEventType(int nEventType);

	//��ȡ��ʱ���¼�����
	int GetEventType() const;

	//��ý�嶨ʱ���ص�����
	static void CALLBACK TimerCallBackPro(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2);

public:
	//�������ظú���ʵ�ֲ�ͬ��ʱ����
	virtual void Run(); 

private:
	//���ϵͳ֧�ֵļ�ʱ��װ��������֧Ԯ����С�Ľ�����ֵ����ʱ�ľ��ȣ�,�������õķֱ��ʣ����ظ�����ʾʧ��
	int GetSystemPeriod(int &nPeriodMix, int &nPeriodMax);

private:
	//��ʱ���ľ��ȣ�Ĭ�����û���֧�ֵ���С���ȣ�һ����1ms
	MMRESULT  m_nTimerID;

	//�ֱ���
	int m_nResolution; 

	//�Ժ���ָ���¼�������
	int m_nDelay;

	//���ö�ʱ���¼�����
	int m_nType;

	//��ʱ���¼�����
	enum eEventType
	{
		RunOnce  = TIME_ONESHOT,      //uDelay�����ֻ����һ���¼�
		RunCycle = TIME_PERIODIC      //ÿ��uDelay���������Եز����¼���
	};
};


