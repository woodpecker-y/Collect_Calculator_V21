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
* @brief :该文件用于驱动板载LED 包含LED1~LED6 以及LEDBR LEDSD
* 注意在修改管脚时，注意时钟系统的功能开启和修改
* 
* 
*
* @author :
* @date :2017/8/24 11:57
***************************************************************
*/ 
#define _LED_C_
#include "LED.h"
 



 



/*
	系统工作指示灯初始化

*/
void SysLed_Cfg(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	LEDBR_OFF;
	LEDSD_OFF;
	LED_RUN_OFF;
	LED_COM1_OFF;
	LED_COM2_OFF;
	LED_COM3_OFF;
	LED_Alarm_OFF;
	LED_Fault_OFF;

	/*Configure GPIO pins : LEDBR_Pin  */
	GPIO_InitStruct.Pin = LEDBR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LEDBR_GPIO_Port, &GPIO_InitStruct);


	/*Configure GPIO pins : LEDSD_Pin  */
	GPIO_InitStruct.Pin = LEDSD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LEDSD_GPIO_Port, &GPIO_InitStruct);	

	/*Configure GPIO pins : LED1_Pin  */
	GPIO_InitStruct.Pin = LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);		

	/*Configure GPIO pins : LED2_Pin  */
	GPIO_InitStruct.Pin = LED2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);		

	/*Configure GPIO pins : LED3_Pin  */
	GPIO_InitStruct.Pin = LED3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);		

	/*Configure GPIO pins : LED4_Pin  */
	GPIO_InitStruct.Pin = LED4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED4_GPIO_Port, &GPIO_InitStruct);			

	/*Configure GPIO pins : LED5_Pin  */
	GPIO_InitStruct.Pin = LED5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED5_GPIO_Port, &GPIO_InitStruct);		


	/*Configure GPIO pins : LED6_Pin  */
	GPIO_InitStruct.Pin = LED6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED6_GPIO_Port, &GPIO_InitStruct);	


}

 

void LEDBR_RebackFun(INT8U CTRL )
{
	if(CTRL ==1)
	{
		LEDBR_ON;
	}
	else
	{		
		LEDBR_OFF;
	}
}



 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
