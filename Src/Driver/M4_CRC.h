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
* @brief :M4_CRC功能组件驱动文件

* 
* 
* 
*
* @author :许伟
* @date :2017/8/25 8:52
***************************************************************
*/ 
#ifndef _M4_CRC_H_
#define _M4_CRC_H_
 

#include "typedef.h"
#include "stm32f4xx_hal.h"


 
#ifdef _M4_CRC_C_
#define M4_CRC_EXT
#else
#define M4_CRC_EXT extern
#endif
 


M4_CRC_EXT CRC_HandleTypeDef hcrc;


 
 




 
#ifdef _M4_CRC_C_




#endif
 
M4_CRC_EXT void M4_CRC_PHY_Init(void);
M4_CRC_EXT uint32_t M4_CRC32_Calculate(uint32_t pBuffer[], uint32_t BufferLength);




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
