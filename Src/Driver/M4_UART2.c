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
* @brief :本驱动应用于STM32F4系列微控制的UART2
*UART发送采用 DMA 非阻塞式发送  数据方向由内存到外设，发送完成后会触发发送完成
*UART接收采用 DMA 非阻塞式接收  数据方向由外设到内存，另外设置接收空闲中断，通过查询空闲标志来确定已经接收到了数据帧，用来防止数据帧过小而没有引发DMA传输的情况
*
该文件包含3个中断服务函数 
UART2 DMA发送完成中断服务函数
UART2 DMA接收完成中断服务函数
UART全局中断服务函数
* 
* 
* 
*
* @author :
* @date :2017/5/7 7:26
***************************************************************
*/ 
#define _M4_UART2_C_
#include "M4_UART2.h"
#include "main.h"



#if (C_STDLibSupportUART2==1)
/* 标准库支持*/	  
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#pragma import(__use_no_semihosting)                            
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (uint8_t) ch;      
	return ch;
}
/*END*/

#endif





/* USART2 init function */
void MX_USART2_UART_Init(void)
{

	huart2.Instance = 		USART2;
//	huart2.Init.BaudRate = 	115200;
//	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = 	UART_STOPBITS_1;
//	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

 
 


/** 
  * Enable DMA controller clock
  */

void MX_USART2_DMA_Init(void) 
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 1, 0);		//UART2_RX
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	/* DMA1_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 2, 0);		//UART2_TX
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);		

}




/*
 UART2 异步通信配置
*/
void UART2_Cfg(void)
{
	MX_USART2_DMA_Init();	//
	MX_USART2_UART_Init();
	
	HAL_UART_Receive_DMA(&huart2,UART2_RxBuffer,UART2_Amount);	//DMA接收配置
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);    				//使能空闲中断
}





void HAL_UART2_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__HAL_RCC_USART2_CLK_ENABLE();
  
	/**USART2 GPIO Configuration	
	PA2 	------> USART2_TX
	PA3 	------> USART2_RX 
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART2 DMA Init */
	/* USART2_TX Init */
	hdma_usart2_tx.Instance = DMA1_Stream6;
	hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
	hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart2_tx.Init.Mode = DMA_NORMAL;
	hdma_usart2_tx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
	{
	  _Error_Handler(__FILE__, __LINE__);
	}

	__HAL_LINKDMA(huart,hdmatx,hdma_usart2_tx);

	/* USART2_RX Init */
	hdma_usart2_rx.Instance = DMA1_Stream5;
	hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
	hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart2_rx.Init.Mode = DMA_NORMAL;
	hdma_usart2_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
	{
	  _Error_Handler(__FILE__, __LINE__);
	}

	__HAL_LINKDMA(huart,hdmarx,hdma_usart2_rx);


	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(USART2_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	UART2_Busy =HAL_OK;

}





void HAL_UART2_MspDeInit(UART_HandleTypeDef* huart)
{

	/* Peripheral clock disable */
	__HAL_RCC_USART2_CLK_DISABLE();

	/**USART2 GPIO Configuration    
	PA2     ------> USART2_TX
	PA3     ------> USART2_RX 
	*/
	HAL_GPIO_DeInit(GPIOA, U2TX_Pin|U2RX_Pin);

	/* Peripheral DMA DeInit*/
	HAL_DMA_DeInit(huart->hdmatx);
	HAL_DMA_DeInit(huart->hdmarx);

	/* Peripheral interrupt DeInit*/
	HAL_NVIC_DisableIRQ(USART2_IRQn);

	
	UART2_Busy =HAL_OK;
}





/*
	UART2发送服务函数
*/
HAL_StatusTypeDef UART2_Transmit(uint8_t* Buffer, uint16_t Num)
{
	HAL_StatusTypeDef back =HAL_OK;
	UART2_Busy =HAL_BUSY;
	memcpy(UART2_TxBuffer, Buffer,Num);//将参数数据传递给参数指针
	back =HAL_UART_Transmit_DMA(&huart2,UART2_TxBuffer,Num);		//将接收到的数据返回

	return  back;
	
}












/**
* @brief This function handles USART2 global interrupt.
*/

void USART2_IRQHandler(void)
{

  	HAL_StatusTypeDef BackVal=HAL_OK;
    uint32_t tmp_flag = 0;
    uint32_t temp =0;
    uint32_t UART2_Rxlenth =0;
	
	
    HAL_UART_IRQHandler(&huart2);
    tmp_flag =  __HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE);//获取端口空闲中断
    if((tmp_flag != RESET))
    { 
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		
		/* 以下代码用于通信测试	也可以仿照此方式通过FIFO进行数据传递*/
		BackVal =BackVal;
		temp  = hdma_usart2_rx.Instance->NDTR;         							//读取剩余接收缓冲区的大小
		UART2_Rxlenth =  UART2_Amount - temp;   

		
		UART_RBC_BufferInput(UART_TO_FY1000_CCB_S,UART2_Rxlenth,UART2_RxBuffer);
		HAL_UART_DMAStop(&huart2);
		BackVal = HAL_UART_Receive_DMA(&huart2,UART2_RxBuffer,UART2_Amount);		//重新设置DMA 接收
		/* end*/
     }
}





/**
* @brief This function handles DMA1 stream5 global interrupt.
 UART2_RX 完成中断服务函数
*/
void DMA1_Stream5_IRQHandler(void)
{

	HAL_DMA_IRQHandler(&hdma_usart2_rx);
	/* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

	/* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
UART1_TX 完成中断服务函数
*/
void DMA1_Stream6_IRQHandler(void)
{
	static INT32U inng =0;

	inng ++;
	HAL_DMA_IRQHandler(&hdma_usart2_tx);
	/* USER CODE BEGIN DMA1_Stream6_IRQn 1 */
	


	UART2_Busy =HAL_OK;
	LED_COM2_ON;

	/* USER CODE END DMA1_Stream6_IRQn 1 */
}






 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
