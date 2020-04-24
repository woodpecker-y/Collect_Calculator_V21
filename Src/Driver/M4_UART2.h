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
* @brief :本驱动应用于STM32F4系列微控制的UART1
*UART发送采用 DMA 非阻塞式发送  数据方向由内存到外设，发送完成后会触发发送完成
*UART接收采用 DMA 非阻塞式接收  数据方向由外设到内存，另外设置接收空闲中断，通过查询空闲标志来确定已经接收到了数据帧，用来防止数据帧过小而没有引发DMA传输的情况
*
该文件包含3个中断服务函数 
UART1 DMA发送完成中断服务函数
UART1 DMA接收完成中断服务函数
UART全局中断服务函数
* 
* 
* 
*
* @author :
* @date :2017/5/7 7:26
***************************************************************
*/ 
#ifndef _M4_UART2_H_
#define _M4_UART2_H_
 

#include "Typedef.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"	
#include "DMA_AddCfg.h"

 
#ifdef _M4_UART2_C_
#define M4_UART2_EXT
#else
#define M4_UART2_EXT extern
#endif
 


#define C_STDLibSupportUART2	0		//标准库支持选项 1支持 0不支持  注意通用串行输出时只能占用一个端口

#define U2TX_Pin GPIO_PIN_2
#define U2TX_GPIO_Port GPIOA
#define U2RX_Pin GPIO_PIN_3
#define U2RX_GPIO_Port GPIOA
 



M4_UART2_EXT UART_HandleTypeDef huart2;			//定义异步通信句柄
M4_UART2_EXT DMA_HandleTypeDef hdma_usart2_rx;		//DMA接收服务句柄
M4_UART2_EXT DMA_HandleTypeDef hdma_usart2_tx;		//DMA发送服务句柄

/* DMA输入输出缓冲区*/
M4_UART2_EXT uint8_t UART2_RxBuffer[UART2_Amount]__attribute__((at(UART2_RX_DMA_ADD)));//接收缓冲区
M4_UART2_EXT uint8_t UART2_TxBuffer[UART2_Amount]__attribute__((at(UART2_TX_DMA_ADD))); //接收缓冲区






#ifdef _M4_UART2_C_


void MX_USART2_DMA_Init(void);
void MX_USART2_UART_Init(void);

#endif
 

M4_UART2_EXT	HAL_StatusTypeDef UART2_Busy;		//发送总线忙标志位

//M4_UART2_EXT	INT8U UART2_DMACONT;


M4_UART2_EXT void UART2_Cfg(void);
M4_UART2_EXT HAL_StatusTypeDef UART2_Transmit( uint8_t *pData, uint16_t Size);	//发送服务函数，采用DMA非阻断方式


M4_UART2_EXT void HAL_UART2_MspInit(UART_HandleTypeDef* huart);		//MSP挂接句柄
M4_UART2_EXT void HAL_UART2_MspDeInit(UART_HandleTypeDef* huart); 		//MSP挂接句柄


M4_UART2_EXT void USART2_IRQHandler(void);
M4_UART2_EXT void DMA1_Stream6_IRQHandler(void);		//UART2_TX 完成中断服务函数
M4_UART2_EXT void DMA1_Stream5_IRQHandler(void);		//UART2_RX 完成中断服务函数

 

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
