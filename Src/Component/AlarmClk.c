/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
*
* @file :
* @version :
* @function :
* 
* 
* 
* 
* 
* 
* @brief :该文件为闹铃组件的程序源文件
* 
* 根据  年  月  日  时  分 的匹配性 触发回调函数   其中  年  月   定时参数为零时 则不纳入匹配条件  

比如
Alarm.Year =0;
Alarm.Month =0;
Alarm.Day =0;
Alarm.Hour =12
Alarm.Minute =15    //意味着每天的12:15闹铃触发


Alarm.Year =0;
Alarm.Month =0;
Alarm.Day =17
Alarm.Hour =12
Alarm.Minute =15    //意味着每月的17.12:15 闹铃触发




* 
*
* @author :许伟
* @date :2017/9/1 13:28
***************************************************************
*/ 
#define _ALARMCLK_C_
#include "AlarmClk.h"
 




/*
	闹铃软件功能模块初始化
	@para  系统实时时钟获取回调函数挂接
*/
void AlarmClk_Init(void)
{
	for(int Loop =0;Loop<MaxAlarmClkNum;Loop++)
	{
		AlarmClkManager[Loop].Enable =AlarmClk_Disable;
		AlarmClkManager[Loop].Ready = AlarmClk_NorReady;
		AlarmClkManager[Loop].Callback_Func = NULL;
		AlarmClkManager[Loop].AlarmTime = 0;
		AlarmClkManager[Loop].MinuteType = AlarmClk_Disable;	//默认分钟整除功能关闭
	}
}


/*

	创建一个闹铃模块成员

	@Enable :使能标志
	@F_callback :回调函数注册
	@ TypeEna:分钟整除触发器 使能
	@interval:分钟触发器触发间隔
	

*/
AlarmClk_Stru* AlarmClk_CreatOne( AlarmClk_Enum Enable,AlarmClkCallBack F_callback,AlarmClk_Enum TypeEna,time_t interval)
{
	if(AlarmClkRecord >= MaxAlarmClkNum)
	{
		return NULL;
	}
	AlarmClkManager[AlarmClkRecord].Enable = Enable;
	AlarmClkManager[AlarmClkRecord].Ready = AlarmClk_Ready;
	AlarmClkManager[AlarmClkRecord].MinuteType = TypeEna;
	AlarmClkManager[AlarmClkRecord].repeatInterval = interval*60;
	AlarmClkManager[AlarmClkRecord].Callback_Func = F_callback;
	AlarmClkRecord ++;
	return &AlarmClkManager[AlarmClkRecord - 1];	
}




/*
模块成员定时参数设置
@定时时间参数

*/
int AlarmClk_ParaSet( AlarmClk_Stru* Member, RealClock_Str *Parameters )
{
	time_t parm;
	int time_res;
	time_res = getTimeTick(&parm,Parameters);
	if(-1 == time_res)
	{
		dbg_printf(DEBUG_ERR,"设置闹铃组件参数发生错误");
		return -1;
	}
	Member->AlarmTime = parm;
	return 0;
}


/*
模块成员
使能/禁止 控制

*/
void AlarmClk_EnableCtrl( AlarmClk_Stru* Member,AlarmClk_Enum Enable )
{
	Member->Enable = Enable;
}


void AlarmClk_ExecutServer(void)
{

	time_t CurrentTime;

	CurrentTime = RTC_TimeTicks;						//获取当前系统时间

	for (int LOOP =0;LOOP<AlarmClkRecord;LOOP++)
	{
		/* 未启用时钟 */
		if(AlarmClkManager[LOOP].Enable != AlarmClk_Enable)
		{
			continue;
		}

		/* 已经触发过的时钟 */
		if(AlarmClkManager[LOOP].Ready != AlarmClk_Ready)
		{
			continue;
		}

		/* 时钟触发 */
		if(CurrentTime >= AlarmClkManager[LOOP].AlarmTime)
		{
			/* 判断是否为过期时钟 */
			if(CurrentTime - AlarmClkManager[LOOP].AlarmTime > MAXALARMWAIT)
			{
				/* 过期的单次时钟直接忽略，周期时钟直接排入下个周期 */
				if(AlarmClkManager[LOOP].MinuteType == AlarmClk_Disable)
				{
					/* 普通一次性时钟 */
					AlarmClkManager[LOOP].Ready = AlarmClk_NorReady;
				}
				else
				{
					/* 重复时钟设置到下一个周期 */
					AlarmClkManager[LOOP].AlarmTime = CurrentTime + AlarmClkManager[LOOP].repeatInterval - ((CurrentTime - AlarmClkManager[LOOP].AlarmTime)%AlarmClkManager[LOOP].repeatInterval);
				}
				continue;
			}
			
			/* 有闹铃触发 */
			if(AlarmClkManager[LOOP].MinuteType == AlarmClk_Disable)
			{
				/* 普通一次性时钟 */
				AlarmClkManager[LOOP].Ready = AlarmClk_NorReady;
			}
			else
			{
				AlarmClkManager[LOOP].AlarmTime += AlarmClkManager[LOOP].repeatInterval;
			}
			
			/* 执行闹钟回调函数 */
			if(AlarmClkManager[LOOP].Callback_Func != NULL)
			{
				(*AlarmClkManager[LOOP].Callback_Func)();
			}
		}
	}
	
}


 
void printAllAlarm(void)
{
	RealClock_Str real;
	
	for(int LOOP =0;LOOP<AlarmClkRecord;LOOP++)
	{
		/* 未启用时钟 */
		if(AlarmClkManager[LOOP].Enable != AlarmClk_Enable)
		{
			continue;
		}

		/* 打印处于启用状态的闹铃*/
		getRealTime(&AlarmClkManager[LOOP].AlarmTime,&real);
		os_printf("Alarm at:%d-%02d-%02d-%02d:%02d:%02d %s\r\n",real.Year,real.Month,real.Day,real.Hour,real.Minute,real.Second,AlarmClkManager[LOOP].Ready == AlarmClk_Ready ? "Enabled" : "Disabled");
	}
}



 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
