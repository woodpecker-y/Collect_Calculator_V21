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
* @brief :该例程用于演示通过使用库函数操作FRAM
* 
* 
* 
*
* @author :
* @date :2017/5/9 16:47
***************************************************************
*/ 
#ifndef _M4_IIC1_H_
#define _M4_IIC1_H_
 
#include "stm32f4xx_hal.h"


#ifdef _M4_IIC1_C_
#define M4_IIC1_EXT
#else
#define M4_IIC1_EXT extern
#endif
 

#define	IIC1_ClockSpeed	1000000




/* Private variables ---------------------------------------------------------*/
M4_IIC1_EXT I2C_HandleTypeDef hi2c1;


#ifdef _M4_IIC1_C_




#endif
 





 
 
M4_IIC1_EXT void IIC1_Cfg(void);

M4_IIC1_EXT void HAL_IIC1_MspInit(I2C_HandleTypeDef* hi2c);



 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
