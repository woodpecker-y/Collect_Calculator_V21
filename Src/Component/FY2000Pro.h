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
* @brief :该文件用于FY-2000系列产品的主机侧通信协议
* 
* 
* 
*
* @author :许伟
* @date :2017/9/5 16:30
***************************************************************
*/ 
#ifndef _FY2000PRO_H_
#define _FY2000PRO_H_


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"


 
#ifdef _FY2000PRO_C_
#define FY2000PRO_EXT
#else
#define FY2000PRO_EXT extern
#endif
 

#define FY2000Pro_PackSize			UART_TO_FY2000PackSize_S
#define FY2000Pro_HeadSize			12			//数据包头大小
#define FY2000Pro_StartCode			0X3A			//起始符
#define FY2000Pro_ProtocolCode			0X70			//版本号
#define FY2000Pro_BroadcastAddr		0XAAAAAAAA	//广播地址
#define FY2000Pro_EndCode			0XAA			//结束符


#pragma pack(1)		//字节对齐
typedef struct
{
	INT8U	Start;		//起始字符	1字节
	INT8U	Version;	//协议版本号	1字节
	INT32U	SN;		//产品序列号	4字节
	INT16U	DESN;	//保留字节	1字节
	INT16U	GN;		//产品组号	2字节
	INT8U	ConType;	//控制类型	1字节
	INT8U	Lenth;	//数据长度	1字节
}FY2000Pro_Head_Stru;
#pragma pack()		//字节对齐



/*
	通信缓充包处理数据结构 联合体
	包括接收包和发送包
*/
#pragma pack(1)		//字节对齐

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//年
	INT8U	Month;	//月
	INT8U	Day;		//日
	INT8U	Hour;		//时
	INT8U	Minute; //分
	INT8U	Second; //秒
	INT8U	Week;	//周
	
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack50_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Delay;	//延时时间
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack51_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Delay;	//延时时间
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack52_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;

	INT8U	 ValveCtrlDemandFlg;	//动作控制命令
	INT8U	CtrlFlg;	//控制标志
	
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志

}FY2000_Pack53_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	 ValveCtrlDemandFlg;	//动作控制命令
	INT8U	CtrlFlg;	//控制标志
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack54_Stru;



typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//年
	INT8U	Month;	//月
	INT8U	Day;		//日
	INT8U	Hour;		//时
	INT8U	Minute; 	//分
	INT8U	Second; 	//秒
	INT8U	Week;	//周
	
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack55_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//延时时间
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack56_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//操作数
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack57_Stru;	


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;			//2字节
	INT8U	Month;		//1字节
	INT8U	Day;			//1字节 
	INT8U	Hour;			// 1字节
	INT8U	Minute; 		//1字节 	
	INT8U	Second; 		//1字节 
	INT16U	ShareNO;		//2字节分摊序号
	INT8U	ShareCycle;		//分摊周期
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY2000_Pack58_Stru;




typedef struct
{
	FY2000Pro_Head_Stru Head;
	
	INT16U	DATA;			//操作数
	INT32U	LoopTime;		//周期供暖时间
	INT32U	Apportion_Energy;//周期分摊热量 使用热量
	INT32U	Remain_Heat;	//剩余热量
	INT32U	Total_Heat; 	//用户购入热量
	
	INT8U	ControlType;	//费控类型
	
	INT8U	ForceCtrlFlg;	//强制控制标志
	
	INT8U	Set_TCtrlFg;		//系统温度设定标志
	INT16U	Set_Temp;		//系统设定温度

	INT8U	LimtTE_Flag;	//极限温度设定标志
	INT16U	LimtTE_Value;	//极限设定温度	
	

	INT16U	Year_S; 		//2字节
	INT8U	Month_S;		//1字节
	INT8U	Day_S;		//1字节 
	INT8U	Hour_S; 		//1字节
	INT8U	Minute_S;		//1字节 	
	INT8U	Second_S;		//1字节

	INT16U	Year_F; 		//2字节
	INT8U	Month_F;		//1字节
	INT8U	Day_F;		//1字节 
	INT8U	Hour_F; 		//1字节
	INT8U	Minute_F;		//1字节 	
	INT8U	Second_F;		//1字节 


	INT8U	Buld;			//楼栋号
	INT8U	Unit;			//单元号
	INT8U	Floor;			//楼层号
	INT8U	Cell;			//房间号
	INT16U	CellArea;		//房间面积


	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY2000_Pack59_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//年
	INT8U	Month;	//月
	INT8U	Day;		//日
	INT8U	Hour;		//时
	INT8U	Minute; //分
	INT8U	Second; //秒
	INT8U	Week;	//周		
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack60_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year_S; //2字节
	INT8U	Month_S;	//1字节
	INT8U	Day_S;	//1字节 
	INT8U	Hour_S; // 1字节
	INT8U	Minute_S;	//1字节 	
	INT8U	Second_S;	//1字节

	INT16U	Year_F; //2字节
	INT8U	Month_F;	//1字节
	INT8U	Day_F;	//1字节 
	INT8U	Hour_F; //1字节
	INT8U	Minute_F;	//1字节 	
	INT8U	Second_F;	//1字节
	
	INT8U	TimeSetFlag;	//分摊周期
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY2000_Pack61_Stru;		
typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//控制数据

	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack62_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	Buld;		//楼号
	INT8U	Unit;		//单元号
	INT8U	Floor;		//楼层号
	INT8U	Cell;		//房间号
	INT16U	CellArea;	//房间面积
	
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack63_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	CtrlFlg;	//控制标志
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack128_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;	//年
	INT8U	Month;	//月
	INT8U	Day;	//日
	INT8U	Hour;	//时
	INT8U	Minute; //分
	INT8U	Second; //秒
	INT8U	Week;	//周
	INT16U	CtrlFlg;	//控制标志
	
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack129_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//控制标志
	
	INT8U Buld; //楼号
	INT8U Unit; //单元号
	INT8U Floor;	//楼层号
	INT8U Cell; //房间号
	INT16U CellArea;	//房间面积
	
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack130_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//控制标志
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack131_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	Month;		//月
	INT8U	Day;			//日
	INT8U	Hour;			//时
	INT8U	Minute; 	//分
	
	INT8U	Buld;			//楼号
	INT8U	Unit;			//单元
	INT8U	Floor;			//楼层
	INT8U	Cell;			//房间号
	INT16U	CellArea;		//房间面积
	
	INT8U	Set_TCtrlFg;		//系统温度设定标志
	INT16U	Set_Temp;		//设定温度
	
	INT16U	Cur_Temp;		//当前温度
	INT16U	Ave_Temp;		//平均温度
	INT16U	Input_Temp; //进水温度
	INT16U	Output_Temp;	//回水温度
	
	INT8U	Valve_POS;		//阀门位置
	
	INT32U	Cycle_OpTim;	//周期开阀时间
	INT16U	Cycle_OpRat;	//周期开阀比例
	INT32U	Total_OpTim;	//累计开阀时间
	
	INT8U	Face_State; 	//面板状态
	INT8U	Valve_STate;	//阀门状态
	
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY2000_Pack132_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//控制标志
	INT8U	Check;	//校验和
	INT8U	End;	//结束标志
}FY2000_Pack133_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//房间面积
	
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY2000_Pack134_Stru;



typedef union
{
	INT8U Data[FY2000Pro_PackSize];
	struct
	{
		INT8U	Start;		//起始字符		1字节
		INT8U	Version;	//协议版本号		1字节
		INT32U	SN;		    //产品序列号		4字节
		INT16U	DESN;	    //网络序号		2字节
		INT16U	GN;		    //产品组号		2字节
		INT8U	ConType;	//控制类型		1字节
		INT8U	Lenth;	    //数据长度		1字节
		INT8U	Available[FY2000Pro_PackSize-FY2000Pro_HeadSize];//有效数据
	}DefaultPack;

	FY2000_Pack50_Stru Pack_50;
	FY2000_Pack51_Stru Pack_51;
	FY2000_Pack52_Stru Pack_52;
	FY2000_Pack53_Stru Pack_53;
	FY2000_Pack54_Stru Pack_54;
	FY2000_Pack55_Stru Pack_55;
	FY2000_Pack56_Stru Pack_56;
	FY2000_Pack57_Stru Pack_57;
	FY2000_Pack58_Stru Pack_58;
	FY2000_Pack59_Stru Pack_59;
	FY2000_Pack60_Stru Pack_60;
	FY2000_Pack61_Stru Pack_61;
	FY2000_Pack62_Stru Pack_62;
	FY2000_Pack63_Stru Pack_63;
	FY2000_Pack128_Stru Pack_128;
	FY2000_Pack129_Stru Pack_129;
	FY2000_Pack130_Stru Pack_130;
	FY2000_Pack131_Stru Pack_131;
	FY2000_Pack132_Stru Pack_132;
	FY2000_Pack133_Stru Pack_133;
	FY2000_Pack134_Stru Pack_134;
	
}FY2000_Pack_Uni;


typedef union
{

	FY2000_Pack50_Stru Pack_50;
	FY2000_Pack51_Stru Pack_51;
	FY2000_Pack52_Stru Pack_52;
	FY2000_Pack53_Stru Pack_53;
	FY2000_Pack54_Stru Pack_54;
	FY2000_Pack55_Stru Pack_55;
	FY2000_Pack56_Stru Pack_56;
	FY2000_Pack57_Stru Pack_57;
	FY2000_Pack58_Stru Pack_58;
	FY2000_Pack59_Stru Pack_59;
	FY2000_Pack60_Stru Pack_60;
	FY2000_Pack61_Stru Pack_61;
	FY2000_Pack62_Stru Pack_62;
	FY2000_Pack63_Stru Pack_63;
}FY2000_Send_Uni;


#pragma pack()		//字节对齐


 
 




 
#ifdef _FY2000PRO_C_

INT8U FY2000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



#endif
 




FY2000PRO_EXT void FY2000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY2000PRO_EXT INT8U FY2000_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);













 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
