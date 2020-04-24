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
#ifndef _STM32F4XX_HAL_MSP_H_
#define _STM32F4XX_HAL_MSP_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h"


 
#ifdef _STM32F4XX_HAL_MSP_C_
#define STM32F4XX_HAL_MSP_EXT
#else
#define STM32F4XX_HAL_MSP_EXT extern
#endif
 



typedef union
{

	struct//4字节方式存储
	{
		uint32_t ChipUniqueID[3];
	}Fourdata;

	struct//单字节方式存取
	{
		uint8_t ChipUniqueID[12];

	}OneData;

}Chip_ID_Stru;



 
 




 
#ifdef _STM32F4XX_HAL_MSP_C_




#endif
 


STM32F4XX_HAL_MSP_EXT void SystemClock_Config(void);
STM32F4XX_HAL_MSP_EXT void HAL_MspInit(void);
STM32F4XX_HAL_MSP_EXT void HAL_UART_MspInit(UART_HandleTypeDef* huart);


STM32F4XX_HAL_MSP_EXT void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
STM32F4XX_HAL_MSP_EXT void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
STM32F4XX_HAL_MSP_EXT void Get_ChipID(Chip_ID_Stru * ID);


STM32F4XX_HAL_MSP_EXT INT32U SystemTick_ms;

STM32F4XX_HAL_MSP_EXT	INT8U SysOnbootFlag;
STM32F4XX_HAL_MSP_EXT	INT32U SysOnbootdelay;




STM32F4XX_HAL_MSP_EXT void INTX_DISABLE(void);
STM32F4XX_HAL_MSP_EXT void INTX_ENABLE(void) ;

STM32F4XX_HAL_MSP_EXT void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);

STM32F4XX_HAL_MSP_EXT void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc);
STM32F4XX_HAL_MSP_EXT void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc);






 
#endif




/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
