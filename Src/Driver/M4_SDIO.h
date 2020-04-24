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
* @date :2017/8/25 14:37
***************************************************************
*/ 
#ifndef _M4_SDIO_H_
#define _M4_SDIO_H_
 

#include "stm32f4xx_hal.h"
#include "typedef.h"
#include "string.h"


 
#ifdef _M4_SDIO_C_
#define M4_SDIO_EXT
#else
#define M4_SDIO_EXT extern
#endif
 
M4_SDIO_EXT SD_HandleTypeDef hsd;
M4_SDIO_EXT DMA_HandleTypeDef hdma_sdio_rx;
M4_SDIO_EXT DMA_HandleTypeDef hdma_sdio_tx;

M4_SDIO_EXT HAL_SD_CardInfoTypeDef SDCardInfo;	//SDø®∆¨–≈œ¢




 
#ifdef _M4_SDIO_C_



#endif
 




M4_SDIO_EXT void SDIO_Cfg(void);

M4_SDIO_EXT HAL_StatusTypeDef SD_GetCardInfo(HAL_SD_CardInfoTypeDef *pCardInfo);

M4_SDIO_EXT void HAL_SD_MspInit(SD_HandleTypeDef* hsd);
M4_SDIO_EXT void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd);
M4_SDIO_EXT void SDIO_IRQHandler(void);
M4_SDIO_EXT void DMA2_Stream3_IRQHandler(void);
M4_SDIO_EXT void DMA2_Stream6_IRQHandler(void);










 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
