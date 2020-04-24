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
* @brief :该例程用于演示通过使用库函数操作FRAM
* 
* 
* 
*
* @author :许伟
* @date :2017/5/9 16:47
***************************************************************
*/ 
#define _M4_IIC1_C_
#include "M4_IIC1.h"
 



void MX_I2C1_Init(void)
{

	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = IIC1_ClockSpeed;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		//Error_Handler();
	}

}


/*

IIC1 MSP挂接函数    该函数由MX生成并整理
*/
void HAL_IIC1_MspInit(I2C_HandleTypeDef* hi2c)
{


	GPIO_InitTypeDef GPIO_InitStruct;
	
	/**I2C1 GPIO Configuration    
	PB6     ------> I2C1_SCL
	PB7     ------> I2C1_SDA 
	*/
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	__HAL_RCC_I2C1_CLK_ENABLE();

}
 


/** Configure pins as 
IIC1通信管脚初始化
*/
void IIC1_Cfg(void)
{
	MX_I2C1_Init();
}








/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
