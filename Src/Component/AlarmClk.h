/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon  
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
* @brief :
* 
* 
* 
*
* @author :许伟
* @date :2017/9/1 13:28
***************************************************************
*/ 
#ifndef _ALARMCLK_H_
#define _ALARMCLK_H_
 

#include"TypeDef.h"
#include"string.h"
#include "RTC.h"
#include "time.h"
#include "debug.h"

 
#ifdef _ALARMCLK_C_
#define ALARMCLK_EXT
#else
#define ALARMCLK_EXT extern
#endif
 



#define MaxAlarmClkNum	6		//宏定义闹铃定时器组件
#define MAXALARMWAIT  10		//定义过期多少秒为过期时钟
typedef void (*AlarmClkCallBack)(void);



typedef enum
{
	 AlarmClk_Enable =(INT8U)0X01,
	 AlarmClk_Disable =(INT8U)0X00,
	 AlarmClk_Ready =(INT8U)0x02,
	 AlarmClk_NorReady =(INT8U)0x03
}AlarmClk_Enum;


typedef struct
{
	INT16U	Year;
	INT8U	Month;
	INT8U	Day;
	INT8U	Hour;
	INT8U	Minute;
	INT8U	MinuteDiv;	//整除分钟
}AlarmTime_Stru;
 
 

typedef struct
{
	AlarmClk_Enum Enable;		//使能标志
	AlarmClk_Enum	Ready;		//就绪标志,用于消除在同一分钟内闹铃被多次触发

	AlarmClk_Enum	MinuteType;	//重复触发控制器
	time_t repeatInterval;	//重复触发时间时隔
	time_t	AlarmTime;		//定时时间

	AlarmClkCallBack Callback_Func;//回调函数
	
}AlarmClk_Stru;


typedef AlarmTime_Stru (*SystemTimegeting)(void);	//系统实时时间获取函数指针



#ifdef _ALARMCLK_C_

AlarmTime_Stru	CurrentTime;		//系统当前时间
SystemTimegeting CurrentTimeget;	//获取当前系统时间服务函数

INT8U AlarmClkRecord;
AlarmClk_Stru AlarmClkManager[MaxAlarmClkNum];

#endif
 



ALARMCLK_EXT void AlarmClk_Init(void);
ALARMCLK_EXT AlarmClk_Stru* AlarmClk_CreatOne( AlarmClk_Enum Enable,AlarmClkCallBack F_callback,AlarmClk_Enum TypeEna,time_t interval);

ALARMCLK_EXT int AlarmClk_ParaSet( AlarmClk_Stru* Member, RealClock_Str *Parameters );
ALARMCLK_EXT void AlarmClk_EnableCtrl(AlarmClk_Stru* Member,AlarmClk_Enum Enable  );
ALARMCLK_EXT void AlarmClk_ExecutServer(void);
ALARMCLK_EXT void printAllAlarm(void);





 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
