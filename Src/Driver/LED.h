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
* @brief :该文件用于驱动板载LED 包含LED1~LED6 以及LEDBR LEDSD
* 注意在修改管脚时，注意时钟系统的功能开启和修改
* 
* 
*
* @author :许伟
* @date :2017/8/24 11:57
***************************************************************
*/ 
#ifndef _LED_H_
#define _LED_H_
 


#include "typedef.h"
#include "stm32f4xx_hal.h"
#include "pulse.h"


 
#ifdef _LED_C_
#define LED_EXT
#else
#define LED_EXT extern
#endif
 


#define LED1_Pin	GPIO_PIN_4
#define LED1_GPIO_Port GPIOE

#define LED2_Pin	GPIO_PIN_5
#define LED2_GPIO_Port	GPIOE

#define LED3_Pin	GPIO_PIN_6
#define LED3_GPIO_Port	GPIOE

#define LED4_Pin	GPIO_PIN_13
#define LED4_GPIO_Port	GPIOC

#define LED5_Pin	GPIO_PIN_14
#define LED5_GPIO_Port	GPIOC

#define LED6_Pin	GPIO_PIN_15
#define LED6_GPIO_Port	GPIOC




#define LEDBR_Pin	GPIO_PIN_7
#define LEDBR_GPIO_Port	GPIOD
#define LEDBR_ON		(HAL_GPIO_WritePin(LEDBR_GPIO_Port, LEDBR_Pin, GPIO_PIN_SET))
#define LEDBR_OFF		(HAL_GPIO_WritePin(LEDBR_GPIO_Port, LEDBR_Pin, GPIO_PIN_RESET))
#define LEDBR_Toggle	(HAL_GPIO_TogglePin(LEDBR_GPIO_Port, LEDBR_Pin))


#define LEDSD_Pin	GPIO_PIN_15
#define LEDSD_GPIO_Port	GPIOA
#define LEDSD_ON		(HAL_GPIO_WritePin(LEDSD_GPIO_Port, LEDSD_Pin, GPIO_PIN_SET))
#define LEDSD_OFF		(HAL_GPIO_WritePin(LEDSD_GPIO_Port, LEDSD_Pin, GPIO_PIN_RESET))
#define LEDSD_Toggle	(HAL_GPIO_TogglePin(LEDSD_GPIO_Port, LEDSD_Pin))




#define LED_RUN_ON	(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET))
#define LED_RUN_OFF	(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET))
#define LED_RUN_Toggle	(HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin))

#define LED_COM1_ON	(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET))
#define LED_COM1_OFF	(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET))
#define LED_COM1_Toggle	(HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin))

#define LED_COM2_ON	(HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET))
#define LED_COM2_OFF	(HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET))
#define LED_COM2_Toggle	(HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin))

#define LED_COM3_ON	(HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET))
#define LED_COM3_OFF	(HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET))
#define LED_COM3_Toggle	(HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin))

#define LED_Alarm_ON	(HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET))
#define LED_Alarm_OFF	(HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET))
#define LED_Alarm_Toggle	(HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin))

#define LED_Fault_ON	(HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET))
#define LED_Fault_OFF	(HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET))
#define LED_Fault_Toggle	(HAL_GPIO_TogglePin(LED6_GPIO_Port, LED6_Pin))




 
#ifdef _LED_C_




#endif
 




 
 

LED_EXT void SysLed_Cfg(void);


LED_EXT Pulse_Stru  *LedBR_Ctrler;
LED_EXT void LEDBR_RebackFun(INT8U CTRL );



 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
