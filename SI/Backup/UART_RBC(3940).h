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



#ifdef _UART_RBC_C_
#define UART_RBC_EXT
#else
#define UART_RBC_EXT extern
#endif
 


#define Max_UART_RBC_NUM	3				//宏定义协议控制器的最大数量

typedef  struct UART_RBC_Str 
{

    INT32U *Ticks;							//时钟基准
    
    INT8U *InputBuffer; 						//数据数据输入缓存区
    INT16U BufferSize;  						//数据输入缓冲器缓区大小

    INT16U Rx_Front;    					//接收缓冲区头指针 指示最小接收缓冲区的空地址
    INT16U Rx_Rear;							//接收缓冲区尾指针 指示最小接收缓冲区有效数据的最小地址

    INT8U TimeOut;	 						//接收缓冲区时间溢出寄存器
    INT32U RecPackTimeOut; 					//接收缓冲区时间溢出记录器


	void (*API_RxFunCal)(struct UART_RBC_Str *); 	//外设到应用层回调函数定义
    INT16U RecPackState; 					//数据包接收状态
    INT16U RecPackNum; 						//接收数据字节数
    INT16U RecPackPoint; 					//接收帧控制头指针

    INT8U *InputPack; 						//帧预加载缓冲区
    INT16U PackSize;							//帧预加载缓冲区最大尺寸

}UART_RBC_Stru ;




#ifdef _UART_RBC_C_



#endif


UART_RBC_EXT HAL_StatusTypeDef UART_RBC_Creat(	UART_RBC_Stru* object,
							INT8U* InputBuffer,
							INT16U BufferSize,
							INT8U* InputPack,
							INT32U* TICK,
							INT8U TimeOut);



UART_RBC_EXT void UART_RBC_Rx_Init(UART_RBC_Stru* object, void (*IN)(UART_RBC_Stru *));
UART_RBC_EXT void UART_RBC_BufferIn(UART_RBC_Stru* object,const INT16U InputNum,INT8U* InputBuffer_P);
UART_RBC_EXT HAL_StatusTypeDef UART_RBC_RxServer(UART_RBC_Stru* object);












#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 

