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
* 
* @brief :
* 
* 
* 
*
* @author :
* @date :2016/11/8 22:30
***************************************************************
*/ 
#ifndef _UART_RBC_H_
#define _UART_RBC_H_
 

#include "TypeDef.h"
#include "stm32f4xx_hal_msp.h"

 
#ifdef _UART_RBC_C_
#define UART_RBC_EXT
#else
#define UART_RBC_EXT extern
#endif
 


#define Max_UART_RBC_NUM	6       		//宏定义协议控制器的最大数量

typedef  struct UART_RBC_Str 
{
	FunctionalState Enable;					//启用标志
    INT32U *Ticks;							//时钟基准
    
    INT8U *InputBuffer; 					//数据数据输入缓存区
    INT16U BufferSize;  					//数据输入缓冲器缓区大小

    INT16U Rx_Front;    					//接收缓冲区头指针 指示最小接收缓冲区的空地址
    INT16U Rx_Rear;							//接收缓冲区尾指针 指示最小接收缓冲区有效数据的最小地址

    INT8U TimeOut;	 						//接收缓冲区时间溢出寄存器
    INT32U RecPackTimeOut; 					//接收缓冲区时间溢出记录器



    INT8U RxPack_Mutex; 					//帧接收控制信号量 当协议进入处理阶段时不允许缓冲进栈



	void (*API_RxFunCal)(struct UART_RBC_Str *); 	//外设到应用层回调函数定义
	
    INT16U RecPackState; 					//数据包接收状态
    INT16U RecPackPoint; 					//接收帧控制头指针

    INT8U *InputPack; 						//帧预加载缓冲区
    INT16U PackSize;							//帧预加载缓冲区最大尺寸
    INT8U RecPack_Null; 						//帧缓冲区空标志位
    INT8U RecPack_Full; 						//帧缓冲区满标志位



	INT8U *OutputPack; 						//帧加载发送区
	INT16U OutputPackSize; 					//发送帧数据长度
	
	void (*API_TxFunCal)(struct UART_RBC_Str *);	//应用层到外设发送服务函数，为了保证数据发送的正确及时性该函数内需要判断总线标志状态 【SendBusy】

	HAL_StatusTypeDef* SendBusy;				//发送总线占用控制标志
	INT8U PackCreatFlag;						//发送协议创建标志 打包控制参数
	INT8U PackINPort;						//发送协议入口序号 打包控制参数
	FunctionalState PackSendFlag;				//协议发送请求标志 当该标志置位说明有数据将要发送
	

}UART_RBC_Stru ;





 
#ifdef _UART_RBC_C_

UART_RBC_Stru UART_RBC_Manager[Max_UART_RBC_NUM];
UART_RBC_EXT INT16U UART_RBC_Record;


#endif


UART_RBC_EXT void UART_RBC_ControlerInit(void);
UART_RBC_EXT INT8U UART_RBC_Creat( UART_RBC_Stru** UART_RBCMem,INT8U* InputBuffer,INT16U BufferSize,INT8U* InputPack,INT8U* OutputPack,INT16U PackSize,INT32U* TICK,INT8U TimeOut);
UART_RBC_EXT	void UART_RBC_OutputHandle_Init(UART_RBC_Stru* member, void(*Output)(UART_RBC_Stru *),HAL_StatusTypeDef *BUSY);

UART_RBC_EXT void UART_RBC_InputHandle_Init(UART_RBC_Stru* member, void (*IN)(UART_RBC_Stru *));

UART_RBC_EXT void UART_RBC_Enable(UART_RBC_Stru* member,FunctionalState Falg);
UART_RBC_EXT void UART_RBC_BufferInput(UART_RBC_Stru* member,INT16U InputNum,INT8U* InputBuffer_P);

UART_RBC_EXT void UART_RBC_TXServer(void);
UART_RBC_EXT void UART_RBC_RXServer(void);

 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
