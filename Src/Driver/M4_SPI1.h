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
* @date :2017/5/10 16:41
***************************************************************
*/ 
#ifndef _M4_SPI1_H_
#define _M4_SPI1_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h"


 
#ifdef _M4_SPI1_C_
#define M4_SPI1_EXT
#else
#define M4_SPI1_EXT extern
#endif
 




 
 
#define SPI1CLK_Pin GPIO_PIN_5
#define SPI1CLK_GPIO_Port GPIOA

#define SPI1DO_Pin GPIO_PIN_6
#define SPI1DO_GPIO_Port GPIOA

#define SPI1DI_Pin GPIO_PIN_7
#define SPI1DI_GPIO_Port GPIOA




 
#ifdef _M4_SPI1_C_

u8 SPI1_ReadWriteByte(u8 TxData);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);



#endif
 



M4_SPI1_EXT SPI_HandleTypeDef SPI1_Handler;


M4_SPI1_EXT void MX_SPI1_Init(void);
M4_SPI1_EXT void HAL_SPI1_MspInit(SPI_HandleTypeDef* hspi);
M4_SPI1_EXT void HAL_SPI1_MspDeInit(SPI_HandleTypeDef* hspi);
M4_SPI1_EXT void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
M4_SPI1_EXT u8 SPI1_ReadWriteByte(u8 TxData);

 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
