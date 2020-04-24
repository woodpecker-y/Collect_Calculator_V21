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
* @brief :
* 
* 
* 
*
* @author :
* @date :2017/8/25 10:44
***************************************************************
*/ 
#define _RTC_C_
#include "RTC.h"
 




/* 获取时间戳 */
int getTimeTick(time_t *t, RealClock_Str *real)
{
	struct tm time;
	
	if(real == NULL || real->Year < 1900 | real->Month > 12 || real->Day > 31 || real->Hour > 24 || real->Minute > 60 || real->Second > 60)
	{
		return -1;
	}
	
	time.tm_year = real->Year - 1900;
	time.tm_mon = real->Month -1;
	time.tm_mday = real->Day;
	time.tm_hour = real->Hour;
	time.tm_min = real->Minute;
	time.tm_sec = real->Second;
	time.tm_yday = 0;
	time.tm_wday = 0;
	time.tm_isdst = 0;
	*t = mktime(&time);
	if((time_t)-1 == *t)
	{
		return -1;
	}
	return 0;
}

/* 获取时间戳
注意此函数为非线程安全，如果在多线程调用请加锁
**/
int getRealTime(time_t *t, RealClock_Str *real)
{
	struct tm *time;
	
	time = localtime(t);
	if(time == NULL)
	{
		return -1;
	}
	real->Year = time->tm_year + 1900;
	real->Month = time->tm_mon + 1;
	real->Day = time->tm_mday;
	real->Hour = time->tm_hour;
	real->Minute = time->tm_min;
	real->Second = time->tm_sec;
	real->Week= time->tm_wday;
	
	return 0;
}
 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
