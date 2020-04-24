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
* @brief :STM32M4IIC2驱动文件

* 注意和MSP中的初始化函数挂接
* 
* 
*
* @author :许伟
* @date :2017/8/25 10:23
***************************************************************
*/ 
#ifndef _M4_IIC2_H_
#define _M4_IIC2_H_
 

#include "stm32f4xx_hal.h"


 
#ifdef _M4_IIC2_C_
#define M4_IIC2_EXT
#else
#define M4_IIC2_EXT extern
#endif
 

#define	IIC2_ClockSpeed	400000      //400K




/* Private variables ---------------------------------------------------------*/
M4_IIC2_EXT I2C_HandleTypeDef hi2c2;



 
 




 
#ifdef _M4_IIC2_C_




#endif
 




M4_IIC2_EXT void IIC2_Cfg(void);
M4_IIC2_EXT void HAL_IIC2_MspInit(I2C_HandleTypeDef* hi2c);





 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
