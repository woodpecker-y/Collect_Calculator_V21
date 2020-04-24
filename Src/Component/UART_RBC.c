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
* @brief :  1.该组件模块用于低速通信的缓冲控制处理，属于硬件外设和通信协议的中间服务层（缓冲处理）
	          2.可以实现低速或者内存拷贝数据的双向传输和协议处理
		  3.推荐基于硬件和处理协议的关系创建组件块成员(关系)。
		  4.应用层 到硬件外设 需要挂接 硬件发送服务函数
		  5.硬件层到应用层需要自行编写协议处理函数
		  

		  运行机制：	外设（串行）通过中断，DMA,内存拷贝的方式将数据送入缓冲区
		  			应用层通过判断缓冲区标志位判断是否有数据需要处理
					应用层 协议解析、处理完毕以后通过中间层把运行结果（协议）进行返回
					实现外设接口到不同应用接口的自由切换

					从硬件层往里看，外设数据不断的的输入到事先定义好的缓冲区
					从应用层往外看，加载着不同通信协议的数据进入缓冲缓冲序列，只需要使用不同的协议进行处理即可
* 
* 
* 
*
* @author :许伟
* @date :2016/11/8 22:30
***************************************************************
*/ 
#define _UART_RBC_C_
#include "UART_RBC.h"


/*

UART_RBC 组件功能初始化

*/
void UART_RBC_ControlerInit(void)
{

	INT16U Loop =0;
	for(Loop =0;Loop<Max_UART_RBC_NUM;Loop++)
	{
	    UART_RBC_Manager[Loop].Enable = DISABLE;

	    UART_RBC_Manager[Loop].Rx_Front = 0;
	    UART_RBC_Manager[Loop].Rx_Rear = 0;
//	    UART_RBC_Manager[Loop].Rx_Full = 0;
//	    UART_RBC_Manager[Loop].Rx_Null = 1;

	    UART_RBC_Manager[Loop].RecPackTimeOut = 0;
	    UART_RBC_Manager[Loop].InputPack = 0;
//	    UART_RBC_Manager[Loop].InputPackSize = 0;

	    UART_RBC_Manager[Loop].RxPack_Mutex = 1;

	    UART_RBC_Manager[Loop].RecPackState = 0;
	    UART_RBC_Manager[Loop].RecPackPoint = 0;
	}

}
 

 
 /*
 输入缓冲控制器创建函数，
 @ UART_RBCMem: 控制器指针
 @ InputBuffer:输入缓冲器首地址
 @ BufferSize :输入缓冲器大小
 @ InputPack: 缓冲队列首地址
 @ OutputPack: 输出队列首地址
 @ PackSize: 缓冲队列大小
 @ TICK:	时基 推荐使用系统时钟
 @ TimeOut:时间溢出值
 
 */
 
INT8U UART_RBC_Creat( UART_RBC_Stru** UART_RBCMem,INT8U* InputBuffer,INT16U BufferSize,INT8U* InputPack,INT8U* OutputPack,INT16U PackSize,INT32U* TICK,INT8U TimeOut)
{
    if(UART_RBC_Record >= Max_UART_RBC_NUM)
    {
            return 0X0F;
    }
    UART_RBC_Manager[UART_RBC_Record].InputBuffer = InputBuffer;
    UART_RBC_Manager[UART_RBC_Record].BufferSize =BufferSize;
    UART_RBC_Manager[UART_RBC_Record].Rx_Front = 0;
    UART_RBC_Manager[UART_RBC_Record].Rx_Rear = 0;
//    UART_RBC_Manager[UART_RBC_Record].Rx_Full =0;
//    UART_RBC_Manager[UART_RBC_Record].Rx_Null =1;
    UART_RBC_Manager[UART_RBC_Record].TimeOut=TimeOut;
    UART_RBC_Manager[UART_RBC_Record].RecPackTimeOut=*TICK;
	UART_RBC_Manager[UART_RBC_Record].Ticks=TICK;

    UART_RBC_Manager[UART_RBC_Record].InputPack=InputPack;
	UART_RBC_Manager[UART_RBC_Record].OutputPack=OutputPack;
    UART_RBC_Manager[UART_RBC_Record].PackSize=PackSize;
//    UART_RBC_Manager[UART_RBC_Record].InputPackSize =0;
    UART_RBC_Manager[UART_RBC_Record].RxPack_Mutex =1;
    UART_RBC_Manager[UART_RBC_Record].RecPackState =0;
    UART_RBC_Manager[UART_RBC_Record].RecPackPoint =0;	 
    UART_RBC_Manager[UART_RBC_Record].Enable = DISABLE;

    UART_RBC_Record ++;
    *UART_RBCMem =(UART_RBC_Stru*)&(UART_RBC_Manager[UART_RBC_Record - 1]);
    return 0X00;
    }


/*
	组件模块参数初始化
	
	member ：组件成员
	Output：APP输出到硬件服务函数接口
	BUSY:
输出总线忙标志指针
	
	返回值：空
	

*/
void UART_RBC_OutputHandle_Init(UART_RBC_Stru* member, void(*Output)(UART_RBC_Stru *),HAL_StatusTypeDef *BUSY)
{
	member->API_TxFunCal = Output;	//输出函数地址交接
	member->SendBusy = BUSY;		//输出函数地址交接
	


}

/*
	组件模块参数初始化
	
	member ：组件成员
	IN：外设到应用层函数接口
	返回值：空
	

*/
void UART_RBC_InputHandle_Init(UART_RBC_Stru* member, void (*IN)(UART_RBC_Stru *))
{
	member->API_RxFunCal = IN;	//输出函数地址交接


}


/*
	组件模块使能服务函数
	Falg:使能标志 Enable/DISABLE
	返回值：空

*/
void UART_RBC_Enable(UART_RBC_Stru* member,FunctionalState Falg)
{
    member->Enable = Falg;
  
}







/*
控制器数据输入服务函数:
@ InputNum 输入数据大小
@ InputBuffer_P 输入数据首地址
*/
void UART_RBC_BufferInput(UART_RBC_Stru* member,INT16U InputNum,INT8U* InputBuffer_P)
{
	INT16U loop =0;
	for(loop =0;loop<InputNum;loop++)
	{
		member->InputBuffer[member->Rx_Front] =*(InputBuffer_P+loop);
		member->Rx_Front +=1;
		if( member->Rx_Front >=member->BufferSize)
		{
			member->Rx_Front =0;
		}
/*		if( member->Rx_Front ==member->Rx_Rear)
		{
			member->Rx_Full =1;
		}
		else
		{
			member->Rx_Full =0;
		}
*/
	}
}





/*
	组件模块自服务函数
	自动完成应用层到硬件的数据发送控制
*/
void UART_RBC_TXServer(void)
{
	INT16U Loop =0;
	for ( Loop = 0; Loop < UART_RBC_Record; Loop++)
	{
		if ( UART_RBC_Manager[Loop].Enable == ENABLE)
		{
			(*UART_RBC_Manager[Loop].API_TxFunCal)(UART_RBC_Manager+Loop);
		}		
	}
}
/* end   */



/*
	组件模块自服务函数
	完成各个成员模块的数据缓冲和解析

*/
void UART_RBC_RXServer(void)
{
	INT16U Loop =0;
	for ( Loop = 0; Loop < UART_RBC_Record; Loop++)
	{
		if ( UART_RBC_Manager[Loop].Enable == ENABLE)
		{
			(*UART_RBC_Manager[Loop].API_RxFunCal)(UART_RBC_Manager+Loop);
		}		
	}
}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
