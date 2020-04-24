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
* @brief :河北丰源热量表通信协议 FY188 处理框架
* 
* 
* 
*
* @author :
* @date :2017/5/24 9:37
***************************************************************
*/ 
#ifndef _FY188PRO_H_
#define _FY188PRO_H_
 


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"



 
#ifdef _FY188PRO_C_
#define FY188PRO_EXT
#else
#define FY188PRO_EXT extern
#endif
 


#define FY188Pro_PackSize			UART_TO_FY188PackSize_S
#define FY188Pro_HeadSize			11				//数据包头大小
#define FY188Pro_StartCode		0X68				//起始符
#define FY188Pro_ProtocolCode		0X25			//版本号
#define FY188Pro_ProtocolCode_C	0X20				//版本号
#define FY188Pro_BroadcastAddr		0XAAAAAAAA		//广播地址
#define FY188Pro_EndCode			0X16				//结束符


#pragma pack(1)		//字节对齐
typedef struct
{

	INT8U	Start;			//起始字符		1字节
	INT8U	Type;			//协议类型		1字节
	INT32U	SN;			//产品序列号		4字节
	INT8U	FAdd1;		//保留字节		1字节
	INT16U	FAdd2;		//保留字节		1字节
	INT8U	ConType;		//控制类型		1字节
	INT8U	Lenth;		//数据长度		2字节
}FY188Pro_Head_Stru;
#pragma pack()			//字节对齐



//FY-188 热量表通信协议包
#pragma pack(1)			//字节对齐

typedef struct
{
	INT8U	Lead1;		//引导字符1 1字节
	INT8U	Lead2;		//引导字符2 1字节
	INT8U	Lead3;		//引导字符3 1字节
	INT8U	Lead4;		//引导字符4 1字节
	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标志
	INT8U	SER;					//数据2
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack01S_Stru;					//召测实时数据

typedef struct
{

	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标志
	INT8U	SER;					//数据2
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack01C_Stru;					//召测实时数据


typedef struct
{
	INT8U	Lead1;				//引导字符1 1字节
	INT8U	Lead2;				//引导字符2 1字节
	INT8U	Lead3;				//引导字符3 1字节
	INT8U	Lead4;				//引导字符4 1字节
	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标志
	INT8U	SER;					//校验和
	INT8U	Second;				//实时时间 秒
	INT8U	Minute;				//实时时间 分
	INT8U	Hour;					//实时时间 时
	INT8U	Day;					//实时时间 日
	INT8U	Month;				//实时时间 月
	INT16U	Year;					//实时时间 年		
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack04S_Stru;					//设置实时时钟


typedef struct
{

	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标志
	INT8U	SER;					//校验和
	INT8U	Second;				//实时时间 秒
	INT8U	Minute;				//实时时间 分
	INT8U	Hour;					//实时时间 时
	INT8U	Day;					//实时时间 日
	INT8U	Month;				//实时时间 月
	INT16U	Year;					//实时时间 年		
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack04C_Stru;					//设置实时时钟

typedef struct
{
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标识
	INT8U	SER;					//序列号
	INT32U	Total_Code; 			//冷量4字节
	INT8U	Total_Code_Unit;			//冷量单位1
	
	INT32U	Total_Energy;			//热量4字节
	INT8U	Total_Energy_Unit;		//热量1字节

	INT32U	Instant_Energy; 			//热功率4字节
	INT8U	Instant_Energy_Unit;

	INT32U	Instant_Current;			//流速4字节
	INT8U	Instant_Current_Unit;		//流速1字节
	
	INT32U	Total_Current;			//累计流量4字节
	INT8U	Total_Current_Unit;
	
	INT16U	Input_TempL;
	INT8U	Input_TempH;

	INT16U	Output_TempL;
	INT8U	Output_TempH;
	
	INT16U	Work_Time_L;			//工作时间1
	INT8U	Work_Time_H;

	INT8U	Second; 				//实时时间
	INT8U	Minute; 				//实时时间
	INT8U	Hour;					//实时时间
	INT8U	Day;					//实时时间
	INT8U	Month;				//实时时间
	INT16U	Year;					//实时时间

	INT8U	STATE1; 				//状态
	INT8U	STATE2; 				//状态
	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack129S_Stru;//返回实时数据


typedef struct
{
	INT8U	Lead1;				//引导字符1 1字节
	INT8U	Lead2;				//引导字符2 1字节
	INT8U	Lead3;				//引导字符3 1字节
	INT8U	Lead4;				//引导字符4 1字节

	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//数据标识
	INT8U	SER;					//序列号
	INT32U	Total_Code; 			//冷量4字节
	INT8U	Total_Code_Unit;			//冷量单位1
	
	INT32U	Total_Energy;			//热量4字节
	INT8U	Total_Energy_Unit;		//热量1字节

	INT32U	Instant_Energy; 			//热功率4字节
	INT8U	Instant_Energy_Unit;

	INT32U	Instant_Current;			//流速4字节
	INT8U	Instant_Current_Unit;		//流速1字节
	
	INT32U	Total_Current;			//累计流量4字节
	INT8U	Total_Current_Unit;
	
	INT16U	Input_TempL;
	INT8U	Input_TempH;

	INT16U	Output_TempL;
	INT8U	Output_TempH;
	
	INT16U	Work_Time_L;			//工作时间1
	INT8U	Work_Time_H;

	INT8U	Second; 				//实时时间
	INT8U	Minute; 				//实时时间
	INT8U	Hour;					//实时时间
	INT8U	Day;					//实时时间
	INT8U	Month;				//实时时间
	INT16U	Year;					//实时时间

	INT8U	STATE1; 				//状态
	INT8U	STATE2; 				//状态
	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY188_Pack129C_Stru;//返回实时数据





typedef union
{
	INT8U Data[FY188Pro_PackSize];
	struct
	{
		
		INT8U	Start;			//起始字符	1字节
		INT8U	Type;			//协议类型	1字节
		INT32U	SN;			//产品序列号	4字节
		INT8U	FAdd1;		//保留字节	1字节
		INT16U	FAdd2;		//保留字节	1字节

		INT8U	ConType;		//控制类型	1字节
		
		INT8U	Lenth;		//数据长度	1字节
		INT8U	Available[FY188Pro_PackSize-FY188Pro_HeadSize];//有效数据
	}DefaultPack;

	struct
	{
		
		INT8U	Start;			//起始字符	1字节
		INT8U	Type;			//协议类型	1字节
		INT32U	SN;			//产品序列号	4字节
		INT8U	FAdd1;		//保留字节	1字节
		INT16U	FAdd2;		//保留字节	1字节

		INT8U	ConType;		//控制类型	1字节
		INT8U	Lenth;		//数据长度	1字节
		INT16U	Flag;			//数据标志
		INT8U	Available[FY188Pro_PackSize-FY188Pro_HeadSize-2];//有效数据
	}CheckPack;	


	FY188_Pack01S_Stru Pack0X01S;
	FY188_Pack04S_Stru Pack0X04S;
	FY188_Pack129S_Stru Pack0X129S;
	
	FY188_Pack01C_Stru Pack0X01C;
	FY188_Pack04C_Stru Pack0X04C;
	FY188_Pack129C_Stru Pack0X129C;

	
}FY188_Pack_Uni;


typedef union
{
	FY188_Pack01S_Stru Pack0X01S;
	FY188_Pack04S_Stru Pack0X04S;

}FY188_Send_Uni;



#pragma pack()		//字节对齐


 
#ifdef _FY188PRO_C_
INT8U FY188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U FY188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

INT8U FY188_Pack_0X129_S(UART_RBC_Stru* PORT);
void FY188_Pack_0X01_S(UART_RBC_Stru* PORT);
void FY188_Pack_0X04_S(UART_RBC_Stru* PORT);






#endif


FY188PRO_EXT void FY188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY188PRO_EXT INT8U FY188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);



















 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
