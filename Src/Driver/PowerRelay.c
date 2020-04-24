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
* @brief :
* 
* 
* 
*
* @author :许伟
* @date :2017/11/29 13:14
***************************************************************
*/ 
#define _POWERRELAY_C_
#include "PowerRelay.h"
#include "PubDef.h"



void PowerRelay_Init(void)
{

#if USE_POWRELAY==1

	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_WritePin(RealyPO_GPIO_Port, RealyPO_Pin, GPIO_PIN_RESET);	
	GPIO_InitStruct.Pin = RealyPO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RealyPO_GPIO_Port, &GPIO_InitStruct);	
	

	HAL_GPIO_WritePin(RealyNE_GPIO_Port, RealyNE_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = RealyNE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(RealyNE_GPIO_Port, &GPIO_InitStruct);	
#endif	

}




void PowerRelay_ON(void)
{
#if USE_POWRELAY==1

	RealyPO_ON;
	RealyNE_OFF;
	printf("主供电回路控制继电器    闭合...\r\n");	
	
#endif	
}


void PowerRelay_OFF(void)
{
#if USE_POWRELAY==1

	RealyPO_OFF;
	RealyNE_ON;
	printf("主供电回路控制继电器    释放...\r\n");	
//	dbg_printf(DEBUG_WARNING,"主供电回路控制继电器    释放...");	
#endif


}


void PowerRelay_SET(INT16U Val)
{
#if USE_POWRELAY==1


	if(Val ==0X0A0A)
	{
		PowerRelay_ON();
	}
	else if(Val ==0XA0A0)
	{
		PowerRelay_OFF();
	}

#endif


}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
