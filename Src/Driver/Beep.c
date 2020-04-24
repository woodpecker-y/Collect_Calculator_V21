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
* @brief :系统蜂鸣器驱动文件
* 
* 
* 
*
* @author :许伟
* @date :2017/8/24 13:54
***************************************************************
*/ 
#define _BEEP_C_
#include "Beep.h"
 





/*
	系统工作指示灯初始化

*/
void SysBeep_Cfg(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */

	__HAL_RCC_GPIOA_CLK_ENABLE();
	Beep_OFF;

	/*Configure GPIO pins : LEDR_Pin  */
	GPIO_InitStruct.Pin = Beep_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Beep_GPIO_Port, &GPIO_InitStruct);

}



void BeepWork_RebackFun(INT8U CTRL )
{
	if(CTRL ==1)
	{
		Beep_ON;
	}
	else
	{		
		Beep_OFF;
	}
}

 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
