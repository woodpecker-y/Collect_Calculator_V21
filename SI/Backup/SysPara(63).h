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
* @author :许伟
* @date :2017/8/28 15:11
***************************************************************
*/ 
#ifndef _SYSPARA_H_
#define _SYSPARA_H_
 

#include "TypeDef.h"
#include "PubDef.h"

#include "W25QXX.H"
#include "RTC.H"
 
#ifdef _SYSPARA_C_
#define SYSPARA_EXT
#else
#define SYSPARA_EXT extern
#endif
 




//*****************************************************************************************
//系统参数数据区

//定义系统参数数据模型
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT32U	Reserved0[10];			//预留空间
	INT32U	Device_BU;				//设备程序编译日期，用于跟踪	
	INT32U	Device_SN;				//设备出厂编号，也用于通信呼叫			
	INT32U	Apportion_T;			//分摊周期 单位 分钟			
		
	INT16U	BuldMeterNum;			//楼栋表数量		
	INT16U	UserNum;				//用户总数量
	INT16U	DevNum;				    //用户设备总数量
	INT16U	DevNum_T;				//系统总设备数量
	
	INT8U	IP1;					//主站IP地址1		
	INT8U	IP2;					//主站IP地址2			
	INT8U	IP3;					//主站IP地址3			
	INT8U	IP4;					//主站IP地址4			
	INT16U	PortNum;				//主站端口号

	INT8U	ReaportType;			//用户数据自动上报类型
	INT16U	ReportSpace;			//用户数据间隔上报间隔单位 分钟
	INT16U	ReportClock;			//定时上报时间点 每(1 2 3 4 6 8 12)小时整点上报

	
	
	INT8U	GPRS_COM;			//GPRS通信端口			
	INT8U	MBUS_COM;			//MBUS通信端口
	INT8U	RF_BUS_COM;			//射频卡通信端口

	
	INT16U	PassWord;				//管理密码			
	INT8U	DeviceType;			//设备类型  计量方案类型
	
	RealClock_Str	StartTime;			//供暖开始时间
	RealClock_Str 	FinalTime;			//供暖结束时间



	INT32U	SendMode;				//设备数据上报模式
	INT32U	ReadSpace;				//设备通信间隔时间
	INT32U	SendSpace;				//设备数据循环上报间隔时间


	INT32U	DebugEnable;			//系统调试使能标志
	INT32U	DebugLevel;			//系统调试信息打印级别
	
	INT32U	LoopSpace;				//设备循环超收间隔时间	  用于两个设备之间的通信切换时间


	INT16U	RelayRecord; 			//主供电回路继电器状态记录

	INT8U	Reserved[1018];			//预留空间	

	
	INT8U	CRC16H;//CRC校验
	INT8U	CRC16L;//CRC校验
}SysPara_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

SYSPARA_EXT SysPara_Stru SysPara;




//定义系统上电参数数据模型
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Year;
	INT8U	Month;
	INT8U	Day;
	INT8U	Hour;
	INT8U	Minute;
	INT8U	Second;	
	INT32U	Times;
	
	INT8U	CRC16H;//CRC校验
	INT8U	CRC16L;//CRC校验
}PowerState_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

SYSPARA_EXT PowerState_Stru PowerStateRecord;

HAL_StatusTypeDef PowerStateRecord_Init(void);
HAL_StatusTypeDef PowerStateRecord_Update(void);



//定义系统上电参数数据模型
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	HAL_StatusTypeDef	Dev_ComStatus;		//系统设备通信状态
	HAL_StatusTypeDef	ShareFlag;			//分摊控制标志   用于标记系统上电后是否允许进行热量分摊
	INT32U			LoopCtrler;			//循环控制器
	HAL_StatusTypeDef	Syspara;			//系统参数状态
	HAL_StatusTypeDef	Userpara;			//用户参数状态
	HAL_StatusTypeDef	Devpara;			//设备参数状态

	
}SysState_Stru;
#pragma pack()		//字节对齐模式 节省存储空间



SYSPARA_EXT SysState_Stru SysStatus;			//系统状态









 
#ifdef _SYSPARA_C_




#endif
 


SYSPARA_EXT HAL_StatusTypeDef SysPara_Init(void);
SYSPARA_EXT HAL_StatusTypeDef SysPara_Update(void);
SYSPARA_EXT HAL_StatusTypeDef SysPara_Reset(void);
SYSPARA_EXT HAL_StatusTypeDef GetDeviceNum(INT16U UserNum, SysDEV_Type TypeID,INT16U* Num);



#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
