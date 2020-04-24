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
* @brief :本驱动应用于STM32F4系列微控制的UART3
*UART发送采用 DMA 非阻塞式发送  数据方向由内存到外设，发送完成后会触发发送完成
*UART接收采用 DMA 非阻塞式接收  数据方向由外设到内存，另外设置接收空闲中断，通过查询空闲标志来确定已经接收到了数据帧，用来防止数据帧过小而没有引发DMA传输的情况
*
该文件包含3个中断服务函数 
UART3 DMA发送完成中断服务函数
UART3 DMA接收完成中断服务函数
UART全局中断服务函数
* 
* 
* 
*
* @author :
* @date :2017/5/7 7:26
***************************************************************
*/ 
#ifndef _M4_UART3_H_
#define _M4_UART3_H_
 


#include "stm32f4xx_hal.h"
#include "stdio.h"	
#include "Typedef.h"
#include "DMA_AddCfg.h"

 
#ifdef _M4_UART3_C_
#define M4_UART3_EXT
#else
#define M4_UART3_EXT extern
#endif
 


#define C_STDLibSupportUART3	0		//标准库支持选项 1支持 0不支持  注意通用串行输出时只能占用一个端口

#define U3TX_Pin GPIO_PIN_8
#define U3TX_GPIO_Port GPIOD

#define U3RX_Pin GPIO_PIN_9
#define U3RX_GPIO_Port GPIOD
 



M4_UART3_EXT UART_HandleTypeDef huart3;			//定义异步通信句柄
M4_UART3_EXT DMA_HandleTypeDef hdma_usart3_rx;		//DMA接收服务句柄
M4_UART3_EXT DMA_HandleTypeDef hdma_usart3_tx;		//DMA发送服务句柄



/* DMA输入输出缓冲区*/
M4_UART3_EXT uint8_t UART3_RxBuffer[UART3_Amount]__attribute__((at(UART3_RX_DMA_ADD)));//接收缓冲区
M4_UART3_EXT uint8_t UART3_TxBuffer[UART3_Amount]__attribute__((at(UART3_TX_DMA_ADD))); //接收缓冲区




//半双工收发控制管脚

#define COM3_CtrlPort	GPIOB
#define COM3_CtrlBit	GPIO_PIN_15
#define COM3_CtrlTX		(HAL_GPIO_WritePin(COM3_CtrlPort, COM3_CtrlBit, GPIO_PIN_SET))
#define COM3_CtrlRX		(HAL_GPIO_WritePin(COM3_CtrlPort, COM3_CtrlBit, GPIO_PIN_RESET))





#ifdef _M4_UART3_C_


void MX_USART3_DMA_Init(void);
void MX_USART3_UART_Init(void);

#endif
 

M4_UART3_EXT	HAL_StatusTypeDef UART3_Busy;		//发送总线忙标志位


M4_UART3_EXT	INT8U UART3_DMACONT;
M4_UART3_EXT	INT32U UART3_DMAOUT;


M4_UART3_EXT void UART3_Cfg(void);
M4_UART3_EXT HAL_StatusTypeDef UART3_Transmit( uint8_t *pData, uint16_t Size);	//发送服务函数，采用DMA非阻断方式


M4_UART3_EXT void HAL_UART3_MspInit(UART_HandleTypeDef* huart);	//MSP挂接句柄
M4_UART3_EXT void HAL_UART3_MspDeInit(UART_HandleTypeDef* huart); //MSP挂接句柄


M4_UART3_EXT void USART3_IRQHandler(void);
M4_UART3_EXT void DMA1_Stream3_IRQHandler(void);		//UART3_TX 完成中断服务函数
M4_UART3_EXT void DMA1_Stream1_IRQHandler(void);		//UART3_RX 完成中断服务函数

 

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
