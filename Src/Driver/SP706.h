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
* @brief :该文件用于驱动外部电源监测及复位控制芯片 SP706
* 
* 
* 
*
* @author :许伟
* @date :2017/8/24 13:37
***************************************************************
*/ 
#ifndef _SP706_H_
#define _SP706_H_
 


#include "typedef.h"
#include "stm32f4xx_hal.h"

 
#ifdef _SP706_C_
#define SP706_EXT
#else
#define SP706_EXT extern
#endif
 



#define SP706_Pin GPIO_PIN_3
#define SP706_GPIO_Port GPIOC


 
#define SP706_H		(HAL_GPIO_WritePin(SP706_GPIO_Port, SP706_Pin, GPIO_PIN_SET))
#define SP706_L		(HAL_GPIO_WritePin(SP706_GPIO_Port, SP706_Pin, GPIO_PIN_RESET))
#define SP706_Toggle	(HAL_GPIO_TogglePin(SP706_GPIO_Port, SP706_Pin))



#define	ExWDT_CLs		250													//定义外部看门狗清零间隔
SP706_EXT INT32U	SP706_Tick;
 




 
#ifdef _SP706_C_




#endif
 


SP706_EXT void SP706_Cfg(void);

 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
