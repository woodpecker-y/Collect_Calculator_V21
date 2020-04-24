/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
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
* @brief :该文件用于驱动外部电源监测及复位控制芯片 SP706

* 
* 
* 
*
* @author :
* @date :2017/8/24 13:37
***************************************************************
*/ 
#define _SP706_C_
#include "SP706.h"
 



 



/*
	系统外部看门狗初始化
*/
void SP706_Cfg(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */

	__HAL_RCC_GPIOC_CLK_ENABLE();
	SP706_L;

	/*Configure GPIO pins : SP706_Pin  */
	GPIO_InitStruct.Pin = SP706_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SP706_GPIO_Port, &GPIO_InitStruct);

}
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
