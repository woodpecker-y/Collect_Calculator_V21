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
* @author :
* @date :2017/8/25 10:45
***************************************************************
*/ 
#ifndef _PCF8563_H_
#define _PCF8563_H_

#include "stm32f4xx_hal.h"
#include "TypeDef.h"
#include "M4_IIC2.h"
#include "RTC.h"


 
#ifdef _PCF8563_C_
#define PCF8563_EXT
#else
#define PCF8563_EXT extern
#endif
 
#define PCF8563_MEMADD_SIZE I2C_MEMADD_SIZE_8BIT

#define Adjust_delay	(1000UL*60*30)

#define PCF8563_ID		0X51        //芯片地址1010001
#define PCF8563START	1
#define PCF8563STOP	0

//PCF8563子地址(寄存器)宏定义
#define SECADD		0X02        //秒
#define MINADD		0X03        //分
#define HOUADD		0X04        //时
#define DAYADD		0X05        //日
#define WEEADD		0X06        //周
#define MONADD		0X07        //月
#define YEAADD		0X08        //年

#define MINALMADD		0X09        //分报警
#define HOUALMADD		0X0A        //时报警
#define DAYALMADD		0X0B        //日报警
#define WEEALMADD		0X0C        //周报警

#define CON1ADD		0X00        //控制寄存器
#define CON2ADD		0X01
#define CLKOADD		0X0D        //时钟输出寄存器
#define TIMCADD		0X0E        //定时器控制寄存器
#define TIMNADD		0X0F        //定时器数值寄存器

#define FIRST_DAY_YEAR	2000        //定义起始年



 
 




 
#ifdef _PCF8563_C_




#endif
 


PCF8563_EXT HAL_StatusTypeDef PCF8563_Set(RealClock_Str * RealTime);
PCF8563_EXT HAL_StatusTypeDef PCF8563_Read(RealClock_Str* RealTime);

 
 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
