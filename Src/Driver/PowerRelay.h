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
* @date :2017/11/29 13:14
***************************************************************
*/ 
#ifndef _POWERRELAY_H_
#define _POWERRELAY_H_

 
#include "typedef.h"
#include "stm32f4xx_hal.h"





#define RealyPO_Pin			GPIO_PIN_13
#define RealyPO_GPIO_Port	GPIOA
#define RealyPO_ON			(HAL_GPIO_WritePin(RealyPO_GPIO_Port, RealyPO_Pin, GPIO_PIN_SET))
#define RealyPO_OFF			(HAL_GPIO_WritePin(RealyPO_GPIO_Port, RealyPO_Pin, GPIO_PIN_RESET))
#define RealyPO_Toggle		(HAL_GPIO_TogglePin(RealyPO_GPIO_Port, RealyPO_Pin))





#define RealyNE_Pin			GPIO_PIN_14
#define RealyNE_GPIO_Port		GPIOA
#define RealyNE_ON			(HAL_GPIO_WritePin(RealyNE_GPIO_Port, RealyNE_Pin, GPIO_PIN_SET))
#define RealyNE_OFF			(HAL_GPIO_WritePin(RealyNE_GPIO_Port, RealyNE_Pin, GPIO_PIN_RESET))
#define RealyNE_Toggle		(HAL_GPIO_TogglePin(RealyNE_GPIO_Port, RealyNE_Pin))








 
#ifdef _POWERRELAY_C_
#define POWERRELAY_EXT
#else
#define POWERRELAY_EXT extern
#endif
 




 
 


POWERRELAY_EXT void PowerRelay_Init(void);
POWERRELAY_EXT void PowerRelay_SET(INT16U Val);


 
#ifdef _POWERRELAY_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
