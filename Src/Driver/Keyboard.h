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
* @date :2017/8/26 14:51
***************************************************************
*/ 
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
 

#include "typedef.h"
#include "stm32f4xx_hal.h"


 
#ifdef _KEYBOARD_C_
#define KEYBOARD_EXT
#else
#define KEYBOARD_EXT extern
#endif


#define	KEY_CO		0X01    //确认
#define	KEY_ML		0X02    //左移
#define	KEY_MU		0X03    //上移
#define	KEY_MR		0X04    //右移
#define	KEY_CA		0X05    //返回
#define	KEY_MD		0X06    //下移


 


#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOB
#define KEY1_Val	(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))


#define KEY2_Pin GPIO_PIN_9
#define KEY2_GPIO_Port GPIOB
#define KEY2_Val	(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin))


#define KEY3_Pin GPIO_PIN_0
#define KEY3_GPIO_Port GPIOE
#define KEY3_Val	(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin))

#define KEY4_Pin GPIO_PIN_1
#define KEY4_GPIO_Port GPIOE
#define KEY4_Val	(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin))


#define KEY5_Pin GPIO_PIN_2
#define KEY5_GPIO_Port GPIOE
#define KEY5_Val	(HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin))

#define KEY6_Pin GPIO_PIN_3
#define KEY6_GPIO_Port GPIOE
#define KEY6_Val	(HAL_GPIO_ReadPin(KEY6_GPIO_Port,KEY6_Pin))





 
 




 
#ifdef _KEYBOARD_C_




#endif
 




 
 
KEYBOARD_EXT void Keyboard_GPIO_Init(void);



 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
