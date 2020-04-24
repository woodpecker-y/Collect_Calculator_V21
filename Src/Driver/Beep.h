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
* @brief :系统蜂鸣器驱动文件
* 
* 
* 
*
* @author :许伟
* @date :2017/8/24 13:54
***************************************************************
*/ 
#ifndef _BEEP_H_
#define _BEEP_H_
 

#include "stm32f4xx_hal.h"
#include "typedef.h "
#include "Pulse.h"


 
#ifdef _BEEP_C_
#define BEEP_EXT
#else
#define BEEP_EXT extern
#endif
 




 
#define Beep_Pin GPIO_PIN_0
#define Beep_GPIO_Port GPIOC
 
#define Beep_ON	(HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET))
#define Beep_OFF	(HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_RESET))
#define Beep_Toggle	(HAL_GPIO_TogglePin(Beep_GPIO_Port, Beep_Pin))




 
#ifdef _BEEP_C_




#endif
 

BEEP_EXT Pulse_Stru  *Beep_Ctrler;
BEEP_EXT void BeepWork_RebackFun(INT8U CTRL );



BEEP_EXT void SysBeep_Cfg(void);
BEEP_EXT void BeepWork_RebackFun(INT8U CTRL );





 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
