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
* @author :ÐíÎ°
* @date :2017/8/25 10:44
***************************************************************
*/ 
#ifndef _RTC_H_
#define _RTC_H_
 


#include"Typedef.h"
#include "time.h"

#ifdef _RTC_C_
#define RTC_EXT
#else
#define RTC_EXT extern
#endif
 



typedef struct
{
	INT16U  Year;
	INT8U   Month;
	INT8U   Day;
	INT8U   Week;
	INT8U   Hour;
	INT8U   Minute;
	INT8U   Second;
}RealClock_Str;

RTC_EXT RealClock_Str RTC_Time;


 
 
RTC_EXT time_t RTC_TimeTicks;



 
#ifdef _RTC_C_




#endif
 




 
 


RTC_EXT int getTimeTick(time_t *t, RealClock_Str *real);
RTC_EXT int getRealTime(time_t *t, RealClock_Str *real);
 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
