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
* @brief :该文件用于采集器和通信终端的主通信服务任务
* 
* 
* 
*
* @author :许伟
* @date :2017/9/5 14:11
***************************************************************
*/ 
#ifndef _CLIENTAPP_H_
#define _CLIENTAPP_H_
#include "cmsis_os.h"
#include "PubDef.h"

#include "Typedef.h"

#include "FY188Pro.h"
#include "FY2000Pro.h"
#include "HZCRL_XPro.h"
#include "XY188Pro.h"

#include "HT2X188PRO.h"
#include "BRC188PRO.h"
#include "DDF2PRO.h"
#include "NWKmodbus.h"



 
#ifdef _CLIENTAPP_C_
#define CLIENTAPP_EXT
#else
#define CLIENTAPP_EXT extern
#endif
 

#define ClientRepeatNum	3



typedef union
{
	FY188_Send_Uni FY188Data;
	FY2000_Send_Uni FY2000Data;
    
 #ifdef Meter_H_ENABLE
	HZCRL_Send_Uni HZCRLData;
 #endif

#ifdef Meter_XY_ENABLE    
	XY188_Send_Uni XY188Data;
#endif
    
#ifdef Meter_HT2X_ENABLE
	HT2X188_Pack_Uni HT2X188Data;
#endif
    
#ifdef Meter_BRC_ENABLE
	BRC188_Pack_Uni BRC188Data;
#endif
    
#ifdef Meter_DDF2_ENABLE
	DDF2_Pack_Uni   DDF2Data;
#endif

#ifdef Valve_NWK_ENABLE
	NWK_Pack_Uni   NWKData;
#endif
	
}ClientCH1_QSend_Uni;



typedef struct
{
    SysDevPara				Device;					//设备参数缓冲器
	HAL_StatusTypeDef		Busy;						//总线状态忙 标志位
	INT32U				Ticks;						//系统时钟记录记录器 用于 设备的重复超收
    HAL_StatusTypeDef		RetFlag;					//返回成功标志 
    
    INT8U				Repeat;					//单终端重复次数
	HAL_StatusTypeDef		CreatFlag;					//通信触发标志
	FlagStatus				SignleCom;					//单次传送 用于广播命令  非广播命令时该标志置位
	INT16U				UaComFlg;					//命令编码 用于标记异步通信回传
	INT8U				Uapack;					//异步抄收命令 标记

	INT8U PackCreatFlag;								//发送协议创建标志 打包控制参数
	INT8U PackINPort;								//发送协议入口序号 打包控制参数
	
	ClientCH1_QSend_Uni		SendData;					//发送协议数据区
}ClientCtrl_Stru;	//通道状态控制器


typedef struct
{
	INT16U Num;					//数量记录器
	INT32U LoopSpace;				//设备循环超收 间隔时间	

}ClientLoopCtrl_Stru;	//循环超收控制器







typedef struct
{
	SysDevPara			Device;
	
	FlagStatus			SignleCom;						    //单次传送
	INT16U			UaComFlg;						        //命令编码 用于标记是否为异步抄收命令  异步抄收命令 自行设置为0XAAAA
	INT8U			Uapack;                                 //异步抄收命令 标记

	INT8U PackCreatFlag;								    //发送协议创建标志 打包控制参数
	INT8U PackINPort;								        //发送协议入口序号 打包控制参数
	ClientCH1_QSend_Uni	SendData;						    //发送协议数据区

}ClientCH1_Queue_Stru;


CLIENTAPP_EXT ClientCtrl_Stru ClientCH1Ctrler;				//定义终端通信控制器
CLIENTAPP_EXT ClientLoopCtrl_Stru ClientReadCtrler;			//定义循环抄收控制器
CLIENTAPP_EXT ClientLoopCtrl_Stru ClientSendCtrler;			//定义循环发送控制器 用户设备数据的循环上传



#define ClientCH1_Q_NUM		16						//定义终端通信通道1消息队列的数量
CLIENTAPP_EXT QueueHandle_t ClientCH1_Msg;				//定义终端通信通道1消息队列
CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_OutArray[ClientCH1_Q_NUM];		//定义终端通信通道1管理队列
CLIENTAPP_EXT ClientCH1_Queue_Stru* ClientCH1_OutArrayP[ClientCH1_Q_NUM];	//定义终端通信通道1管理队列指针


CLIENTAPP_EXT INT8U ClientCH1_Q_NUM_Record;					//入栈计数器


CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_QueueBF;       	//消息队列缓冲器输出
CLIENTAPP_EXT ClientCH1_Queue_Stru* ClientCH1_QueueBFP;       	//消息队列缓冲器输出指针

CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_QueueIN;       	//消息自动发送 输入缓冲
//CLIENTAPP_EXT SemaphoreHandle_t ClientCH1Semaphore;			//通道占用/等待接收二值信号量





#ifdef _CLIENTAPP_C_




#endif
 





typedef struct
{
	INT8U PackCreatFlag;			//发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号

	ClientCH1_QSend_Uni SendData;	//发送数据区
}UART_TO_FY188_QueueSend_Stru;

#define UART_TO_FY188_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_FY188_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_FY188_QueueSend_Stru UART_TO_FY188_OutArray[UART_TO_FY188_Q_NUM];
CLIENTAPP_EXT UART_TO_FY188_QueueSend_Stru* UART_TO_FY188_OutArrayP[UART_TO_FY188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_FY188_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_FY188_CCB_QueueSend(UART_TO_FY188_QueueSend_Stru *DATAIN);











typedef struct
{
	INT8U PackCreatFlag;				//发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号
	ClientCH1_QSend_Uni	SendData;    	//发送数据区

}UART_TO_FY2000_QueueSend_Stru;

#define UART_TO_FY2000_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_FY2000_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_FY2000_QueueSend_Stru UART_TO_FY2000_OutArray[UART_TO_FY2000_Q_NUM];
CLIENTAPP_EXT UART_TO_FY2000_QueueSend_Stru* UART_TO_FY2000_OutArrayP[UART_TO_FY2000_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_FY2000_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_FY2000_CCB_QueueSend(UART_TO_FY2000_QueueSend_Stru *InPut);



#ifdef Meter_H_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			    //发送协议创建标志 打包控制参数
	INT8U PackINPort;				    //发送协议入口序号 打包控制参数
	INT32U ID;						    //设备编号
	
	ClientCH1_QSend_Uni	SendData;    	//发送数据区
}UART_TO_HZCRL_QueueSend_Stru;

#define UART_TO_HZCRL_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_HZCRL_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_HZCRL_QueueSend_Stru UART_TO_HZCRL_OutArray[UART_TO_HZCRL_Q_NUM];
CLIENTAPP_EXT UART_TO_HZCRL_QueueSend_Stru* UART_TO_HZCRL_OutArrayP[UART_TO_HZCRL_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_HZCRL_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_HZCRL_CCB_QueueSend(UART_TO_HZCRL_QueueSend_Stru *DATAIN);
#endif






#ifdef Meter_XY_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			//发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号

	ClientCH1_QSend_Uni SendData;		//发送数据区
}UART_TO_XY188_QueueSend_Stru;

#define UART_TO_XY188_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_XY188_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_XY188_QueueSend_Stru UART_TO_XY188_OutArray[UART_TO_XY188_Q_NUM];
CLIENTAPP_EXT UART_TO_XY188_QueueSend_Stru* UART_TO_XY188_OutArrayP[UART_TO_XY188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_XY188_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_XY188_CCB_QueueSend(UART_TO_XY188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t XY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
CLIENTAPP_EXT BaseType_t HZCRL_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif



#ifdef Meter_HT2X_ENABLE

typedef struct
{
	INT8U PackCreatFlag;				//发送协议创建标志 打包控制参数
	INT8U PackINPort;				    //发送协议入口序号 打包控制参数
	INT32U ID;						    //设备编号
	INT8U Type;                         //设备类型参数

	ClientCH1_QSend_Uni SendData;		//发送数据区
}UART_TO_HT2X188_QueueSend_Stru;

#define UART_TO_HT2X188_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_HT2X188_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_HT2X188_QueueSend_Stru UART_TO_HT2X188_OutArray[UART_TO_HT2X188_Q_NUM];
CLIENTAPP_EXT UART_TO_HT2X188_QueueSend_Stru* UART_TO_HT2X188_OutArrayP[UART_TO_HT2X188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_HT2X188_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_HT2X188_CCB_QueueSend(UART_TO_HT2X188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t HT2X_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif





#ifdef Meter_BRC_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			//发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号

	ClientCH1_QSend_Uni SendData;	//发送数据区
}UART_TO_BRC188_QueueSend_Stru;

#define UART_TO_BRC188_Q_NUM		4						//定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_BRC188_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_BRC188_QueueSend_Stru UART_TO_BRC188_OutArray[UART_TO_BRC188_Q_NUM];
CLIENTAPP_EXT UART_TO_BRC188_QueueSend_Stru* UART_TO_BRC188_OutArrayP[UART_TO_BRC188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_BRC188_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_BRC188_CCB_QueueSend(UART_TO_BRC188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t BRC_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif




#ifdef Meter_DDF2_ENABLE

typedef struct
{
	INT8U PackCreatFlag;            //发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号
	INT8U COM_Type;                 //前导参数

	ClientCH1_QSend_Uni SendData;		                        //发送数据区
}UART_TO_DDF2_QueueSend_Stru;

#define UART_TO_DDF2_Q_NUM		4						        //定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_DDF2_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_DDF2_QueueSend_Stru UART_TO_DDF2_OutArray[UART_TO_DDF2_Q_NUM];
CLIENTAPP_EXT UART_TO_DDF2_QueueSend_Stru* UART_TO_DDF2_OutArrayP[UART_TO_DDF2_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_DDF2_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_DDF2_CCB_QueueSend(UART_TO_DDF2_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t DDF2_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif




#ifdef Valve_NWK_ENABLE
typedef struct
{
	INT8U PackCreatFlag;            //发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	INT32U ID;						//设备编号
	INT8U COM_Type;                 //前导参数

	ClientCH1_QSend_Uni SendData;		                        //发送数据区
}UART_TO_NWK_QueueSend_Stru;

#define UART_TO_NWK_Q_NUM		4						        //定义发送消息队列的数量
CLIENTAPP_EXT QueueHandle_t UART_TO_NWK_Msg;					//协议控制器消息队列句柄
CLIENTAPP_EXT UART_TO_NWK_QueueSend_Stru UART_TO_NWK_OutArray[UART_TO_NWK_Q_NUM];
CLIENTAPP_EXT UART_TO_NWK_QueueSend_Stru* UART_TO_NWK_OutArrayP[UART_TO_NWK_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_NWK_OutRecord;	//入栈计数器
CLIENTAPP_EXT BaseType_t UART_TO_NWK_CCB_QueueSend(UART_TO_NWK_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t NWK_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif






CLIENTAPP_EXT BaseType_t ClientCH1_QueueSend( ClientCH1_Queue_Stru *Input);
CLIENTAPP_EXT BaseType_t FY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
CLIENTAPP_EXT BaseType_t FY_2000Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );






CLIENTAPP_EXT int ClientCH1SendMetexInit(void);




#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
