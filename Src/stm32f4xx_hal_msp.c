
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
* @author :
* @date :2017/8/23 18:08
***************************************************************
*/ 
#define _STM32F4XX_HAL_MSP_C_
#include "stm32f4xx_hal_msp.h"
#include "main.h"



/** System Clock Configuration
*/
void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Configure the main internal regulator output voltage 
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks 
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks 
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                      |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time 
	*/
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	/**Configure the Systick 
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	/* BusFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	/* UsageFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	/* SVCall_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}



void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

	if(huart->Instance==USART1)
	{
		HAL_UART1_MspInit( huart);
	}
	else if(huart->Instance==USART2)
	{
		HAL_UART2_MspInit( huart);

	}
	else if(huart->Instance==USART3)
	{
		HAL_UART3_MspInit( huart);

	}
}




void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

	if(huart->Instance==USART1)
	{
		HAL_UART1_MspDeInit( huart);
	}
  	else if(huart->Instance==USART2)
	{
		HAL_UART2_MspDeInit( huart);
	}
	else if(huart->Instance==USART3)
	{
		HAL_UART3_MspDeInit( huart);

	}

}



/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM3) 
	{
		HAL_IncTick();
	}

}



/*
* 函数名：Get_ChipID
 * 描述  ：获取芯片ID
 * 输入  ：无
 * 输出  ：无
 * 说明  ：96位的ID是stm32唯一身份标识，可以以8bit、16bit、32bit读取
*/
void Get_ChipID(Chip_ID_Stru * ID)
{
  
	//地址从小到大,先放低字节，再放高字节：小端模式
	//地址从小到大,先放高字节，再放低字节：大端模式
	ID->Fourdata.ChipUniqueID[2] = *(__IO uint32_t*)(0x1FFF7A10);  // 低区

	ID->Fourdata.ChipUniqueID[1] = *(__IO uint32_t *)(0x1FFF7A14); // 中区

	ID->Fourdata.ChipUniqueID[0] = *(__IO uint32_t *)(0x1FFF7A18); // 高区
}




//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}



void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{


	if(hi2c->Instance==I2C1)
	{
		HAL_IIC1_MspInit(hi2c);
	}
	else	if(hi2c->Instance==I2C2)
	{
		HAL_IIC2_MspInit(hi2c);
	}

	

}



void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{

	if(hcrc->Instance==CRC)
	{
		/* USER CODE BEGIN CRC_MspInit 0 */

		/* USER CODE END CRC_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_CRC_CLK_ENABLE();
		/* USER CODE BEGIN CRC_MspInit 1 */

		/* USER CODE END CRC_MspInit 1 */
	}

}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{

	if(hcrc->Instance==CRC)
	{
		/* USER CODE BEGIN CRC_MspDeInit 0 */

		/* USER CODE END CRC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CRC_CLK_DISABLE();
		/* USER CODE BEGIN CRC_MspDeInit 1 */

		/* USER CODE END CRC_MspDeInit 1 */
	}

}



void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

	if(hspi->Instance==SPI1)
	{
		HAL_SPI1_MspInit(hspi);
	}

}



void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
    if(hspi->Instance==SPI1)
    {
		HAL_SPI1_MspDeInit(hspi);
    }
}









/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/

