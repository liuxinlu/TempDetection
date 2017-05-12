/*
*作者： FreeBird
*描述：多媒体定时器
*完成时间：2013/7/14
*使用方法：重载函数Run
*         1.先调用SetTimerResolution设置分辨率
*         2.调用SetEventType设置事件类型
*         3.调用GetTimerDelay时间周期
*         以上1到3不设置默认：m_nType = TIME_PERIODIC;m_nDelay = 3000;m_nResolution = 1;
*         4.创建定时器CreateTimer
*         5.用完后销毁定时器DestroyTimer
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
	//创建多媒体定时器
	int CreateTimer();

	//销毁对媒体定时器
	int DestroyTimer();

	//设置分辨率，最小精度1ms，如果设置的超出机器支持的范围，则按照min（机器支持的最小值，1）来设置
	int SetTimerResolution(int nResolution); 

	//获取调用者自己设定的分辨率
	int GetTimerResolution() const;

	//设置以毫秒指定事件的周期
	int SetTimerDelay(int nDelay);

	//获取定时器时间周期
	int GetTimerDelay() const;

	//设置定时器事件类型
	void SetEventType(int nEventType);

	//获取定时器事件类型
	int GetEventType() const;

	//多媒体定时器回调函数
	static void CALLBACK TimerCallBackPro(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2);

public:
	//子类重载该函数实现不同定时功能
	virtual void Run(); 

private:
	//获得系统支持的计时器装置驱动所支援的最小的解析度值（延时的精度）,返回设置的分辨率，返回负数表示失败
	int GetSystemPeriod(int &nPeriodMix, int &nPeriodMax);

private:
	//计时器的精度，默认设置机器支持的最小精度，一般是1ms
	MMRESULT  m_nTimerID;

	//分辨率
	int m_nResolution; 

	//以毫秒指定事件的周期
	int m_nDelay;

	//设置定时器事件类型
	int m_nType;

	//定时器事件类型
	enum eEventType
	{
		RunOnce  = TIME_ONESHOT,      //uDelay毫秒后只产生一次事件
		RunCycle = TIME_PERIODIC      //每隔uDelay毫秒周期性地产生事件。
	};
};


