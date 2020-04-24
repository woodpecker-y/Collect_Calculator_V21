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
* @date :2017/8/23 18:08
***************************************************************
*/ 
#ifndef _STM32F4XX_HAL_TIMEBASE_TIM_H_
#define _STM32F4XX_HAL_TIMEBASE_TIM_H_
 


#include "stm32f4xx_hal.h"
#include "typedef.h"

#ifdef _STM32F4XX_HAL_TIMEBASE_TIM_C_
#define STM32F4XX_HAL_TIMEBASE_TIM_EXT 
#else
#define STM32F4XX_HAL_TIMEBASE_TIM_EXT extern
#endif
 




 
 




 
#ifdef _STM32F4XX_HAL_TIMEBASE_TIM_C_



TIM_HandleTypeDef        htim3; 
uint32_t              uwIncrementState;

#endif
 






STM32F4XX_HAL_TIMEBASE_TIM_EXT volatile unsigned long long FreeRTOSRunTimeTicks;
STM32F4XX_HAL_TIMEBASE_TIM_EXT HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
STM32F4XX_HAL_TIMEBASE_TIM_EXT void HAL_SuspendTick(void);
STM32F4XX_HAL_TIMEBASE_TIM_EXT void HAL_ResumeTick(void);
STM32F4XX_HAL_TIMEBASE_TIM_EXT void TIM3_Init(uint16_t arr,uint16_t psc);
STM32F4XX_HAL_TIMEBASE_TIM_EXT void ConfigureTimeForRunTimeStats(void);
STM32F4XX_HAL_TIMEBASE_TIM_EXT void FreeRTOSRunTimeTicksUp(void);


#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
