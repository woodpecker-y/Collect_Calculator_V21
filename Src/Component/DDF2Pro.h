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
* @date :2018/8/19 11:10
***************************************************************
*/ 
#ifndef _DDF2PRO_H_
#define _DDF2PRO_H_


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"

#ifdef Meter_DDF2_ENABLE

 
#ifdef _DDF2PRO_C_
#define DDF2PRO_EXT
#else
#define DDF2PRO_EXT extern
#endif
 

#define DDF2Pro_PackSize			UART_TO_DDF2PackSize_S
#define DDF2Pro_HeadSize			11				    //数据包头大小
#define DDF2Pro_StartCode		    0X68				//起始符
#define DDF2Pro_ProtocolCode		0X41				//版本号
#define DDF2Pro_EndCode			    0X16				//结束符



#pragma pack(1)		//字节对齐
typedef struct
{

	INT8U	Start;		//起始字符		1字节
	INT8U	Type;		//协议类型		1字节
	INT32U	SN;			//产品编号		4字节
	INT16U	SNRE;		//预设编码		2字节
	INT8U	FAdd2;		//保留字节		1字节
	INT8U	ConType;	//控制类型		1字节
	INT8U	Lenth;		//数据长度		1字节
}DDF2Pro_Head_Stru;
#pragma pack()			//字节对齐


//DDF2通信协议
#pragma pack(1)			//字节对齐

//数据抄收 下行
typedef struct
{
	INT8U	Lead1;		//引导字符1 1字节
	INT8U	Lead2;		//引导字符2 1字节
	INT8U	Lead3;		//引导字符3 1字节
	INT8U	Lead4;		//引导字符4 1字节
	
	DDF2Pro_Head_Stru  Head;
	
	INT16U	Flag;					//数据标识 0x902d 
	INT8U	SER;					//数据标识 2

	
	INT8U	Check;				    //校验和
	INT8U	End;					//结束标志
}DDF2Pro_Pack01_Stru;				//实时数据




typedef struct
{
	DDF2Pro_Head_Stru   Head;       //帧头
	
	INT16U	Flag;					//数据标识
	INT8U	SER;					//数据标识 2

	
    INT8U   Reserve0[27];           //保留字节 无法识别
    INT8U   IN;                     //输出标志 用于标记阀门的位置信息  0X01 关阀 0x00 开阀状态          0x03动作中
    INT8U   Reserve1[5];            //保留字节 无法识别

	
	INT8U	Check;				    //校验和
	INT8U	End;					//结束标志
}DDF2Pro_Pack02_Stru;               //返回实时数据


//阀门动作控制命令
typedef struct
{

	INT8U	Lead1;		//引导字符1 1字节
	INT8U	Lead2;		//引导字符2 1字节
	INT8U	Lead3;		//引导字符3 1字节
	INT8U	Lead4;		//引导字符4 1字节

	DDF2Pro_Head_Stru   Head;       //帧头
	
	INT16U	Flag;					//数据标识         0xa017
	INT8U	SER;					//数据标识2        0x01

	
    INT8U   OUT;                    //输出标志 用于标记阀门的控制状态    0x55 开阀          0XBB 关阀


	INT8U	Check;				    //校验和
	INT8U	End;					//结束标志
}DDF2Pro_Pack03_Stru;               //下行控制命令


//阀门动作控制返回命令
typedef struct
{
	DDF2Pro_Head_Stru   Head;       //帧头
	
	INT16U	Flag;					//数据标识         0xa017
	INT8U	SER;					//数据标识2        0x01

	
    INT8U   IN0;                     //输入标志0        0x00
    INT8U   IN1;                     //输入标志1        0X01

	INT8U	Check;				    //校验和
	INT8U	End;					//结束标志
}DDF2Pro_Pack04_Stru;               //控制执行返回结果






typedef union
{
	INT8U Data[DDF2Pro_PackSize];
	struct
	{
        DDF2Pro_Head_Stru  Head;
		INT8U	Available[DDF2Pro_PackSize-DDF2Pro_HeadSize];//有效数据
	}DefaultPack;


	DDF2Pro_Pack01_Stru Pack_01;
	DDF2Pro_Pack02_Stru Pack_02;
	DDF2Pro_Pack03_Stru Pack_03;
	DDF2Pro_Pack04_Stru Pack_04;

	
}DDF2_Pack_Uni;


typedef union
{

    DDF2Pro_Pack01_Stru Pack_01;
    DDF2Pro_Pack03_Stru Pack_03;

}DDF2_Send_Uni;


#pragma pack()			       //字节对齐结束




 
 


#ifdef _DDF2PRO_C_

INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



#endif
 




 
 

DDF2PRO_EXT void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
DDF2PRO_EXT INT8U DDF2_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);

#endif

 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
