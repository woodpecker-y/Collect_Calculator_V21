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
* @brief :本文件用于汇中仪表的CRL-G 以及CRL-H系列超声波热量表通信协议
* 
* 
* 
*
* @author :
* @date :2017/10/9 14:01
***************************************************************
*/ 
#ifndef _HZCRL_XPRO_H_
#define _HZCRL_XPRO_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"
#include <string.h>

#ifdef Meter_H_ENABLE


typedef enum
{
    S_Start,                    //起始符
    S_Type,                     //仪表类型
    S_Address,                  //仪表地址
    S_Ctr,                      //控制码
    S_Len,                      //长度
    S_Data,                     //数据
    S_Sum,                      //校验
    S_End                      //结束符
}recState_S;

#pragma pack(1)			        //字节对齐

typedef struct
{
    INT8U	start;					//起始符
    INT8U	type;					//仪表类型
    INT8U	addPlace[3];			//地址占位符，默认全零，无意义
    INT32U	address;				//地址(SN)
    INT8U	ctr;                  //控制应答
    INT8U	len;                  //数据长度
}HZCRL_Pack_Head_t;

typedef struct
{
    INT16U	datamark;				//数据标识
    INT8U	serialNum;				//序列号
    
    INT32U	settleEnergy;        	//结算日热量
    INT8U	settleEnergy_Unit;    	//结算日热量单位
    
    INT32U	totalEnergy;         	//当前热量
    INT8U	totalEnergy_Unit;     	//当前热量单位
    
    INT32U	instant_Energy;			//热功率
    INT8U	instant_Energy_Unit;		//热功率单位
    
    INT32U	Current;				//流量
    INT8U	Current_Unit;			//流量单位
    
    INT32U	totalCurrent;			//累计流量
    INT8U	totalCurrent_Unit;			//累计流量单位
    
    INT8U	inputTempH;         	//供水温度高位
    INT16U	inputTempL;         	//供水温度低位
    
    INT8U	outputTempH;        	//回水温度高位
    INT16U	outputTempL;        	//回水温度低位
    
    INT8U	totalWorkH;         	//累计工作时间高位
    INT16U	totalWorkL;         	//累计工作时间低位
    
    INT16U	Year;					//年（实时时间）
    INT8U	Month;				//月（实时时间）
    INT8U	Day;					//日（实时时间）
    INT8U	Hour;					//时（实时时间）
    INT8U	Minute; 			    //分（实时时间）
    INT8U	Second; 			    //秒（实时时间） 
    
    INT8U	state1;				//状态1
    INT8U	state2;				//状态2
}HZCRL_Pack_Value_t;

typedef struct
{
	HZCRL_Pack_Head_t Head;
	INT16U datamark;            //数据标识
    INT8U serialNum;            //序列号
	INT8U sum;				    //校验和
	INT8U end;					//结束标志
}HZCRL_Pack01S_Stru;			//抄收实时数据


typedef struct
{
	HZCRL_Pack_Head_t Head;     //协议头
	HZCRL_Pack_Value_t data;    //热量表实时数据
	INT8U sum;				    //校验和
	INT8U end;					//结束标志
}HZCRL_Pack01S_ACK_Stru;		//实时数据返回


typedef union
{
	HZCRL_Pack01S_Stru Pack0X01S;
}HZCRL_Send_Uni;

#pragma pack()		            //字节对齐

#define Start_Mark  0x68        //起始符
#define End_Mark    0x16        //结束符


 
#ifdef _HZCRL_XPRO_C_
#define HZCRL_XPRO_EXT
#else
#define HZCRL_XPRO_EXT extern
#endif
 




 
 




 
#ifdef _HZCRL_XPRO_C_






#endif
 




 
void HZCRL_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
INT8U HZCRL_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);
void HZCRL_Pack_0X01_S(UART_RBC_Stru* PORT);
INT8U HZCRL_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);

#endif
 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
