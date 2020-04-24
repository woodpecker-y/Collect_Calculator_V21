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
* @brief :STM32M4IIC2驱动文件
* 
* 
* 
*
* @author :许伟
* @date :2017/8/25 10:23
***************************************************************
*/ 
#define _M4_IIC2_C_
#include "M4_IIC2.h"
#include "main.h"




void MX_I2C2_Init(void)
{

	hi2c2.Instance = I2C2;
	hi2c2.Init.ClockSpeed = IIC2_ClockSpeed;
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}


/*

IIC2 MSP挂接函数    该函数由MX生成并整理
*/
void HAL_IIC2_MspInit(I2C_HandleTypeDef* hi2c)
{


	GPIO_InitTypeDef GPIO_InitStruct;

	
	/**I2C2 GPIO Configuration	
	PB10	   ------> I2C2_SCL
	PB11	   ------> I2C2_SDA 
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Peripheral clock enable */
	__HAL_RCC_I2C2_CLK_ENABLE();

}
 


/** Configure pins as 
IIC2通信管脚初始化
*/
void IIC2_Cfg(void)
{
	MX_I2C2_Init();
}


 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
