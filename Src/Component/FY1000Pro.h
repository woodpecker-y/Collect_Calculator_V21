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
* @date :2017/9/26 11:42
***************************************************************
*/ 
#ifndef _FY1000PRO_H_
#define _FY1000PRO_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"
#include "updateparm.h"


 
#ifdef _FY1000PRO_C_
#define FY1000PRO_EXT
#else
#define FY1000PRO_EXT extern
#endif
 





typedef enum
{
	COMBack_OK =0X00,				//设备执行成功
	COMBack_FT =0X01,				//设备执行失败
	COMBack_NF =0X02,				//设备查询失败
	COMBack_CE =0X03,				//设备通信错误
	
}COMBackStaType;					//设备通信返回执行结果说明


#define FY1000Pro_PackSize			UART_TO_FY1000PackSize_S
#define FY1000Pro_HeadSize			11			//数据包头大小
#define FY1000Pro_StartCode			0X59			//起始符
#define FY1000Pro_ProtocolCode		0X57			//版本号
#define FY1000Pro_BroadcastAddr		0XAAAAAAAA	//广播地址
#define FY1000Pro_EndCode			0XAA			//结束符




//丰源智控FY-1000通信协议包
#pragma pack(1)		//字节对齐
typedef struct
{

	INT8U	Start;		//起始字符	1字节
	INT8U	Version;	//协议类型	1字节
	INT32U	SN;		//产品ID/SN	4字节
	INT8U	ConType;	//协议编码	1字节
	INT32U	Lenth;	//数据长度	4字节
}FY1000Pro_Head_Stru;



//1.	*（0X01）主站发送终端设备数据抄收命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//控制标志
	INT8U	Dev_Type;			//设备类型
	INT32U	Dev_ID;			//设备ID
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X01_Stru;


//2.	*（0X02）主站发送终端设备数据抄收命令返回	
//设备查询失败
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志

	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_N_Stru;
//设备通信失败
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志

	INT32U	ComTolNum;			//通信总次数
	INT32U	ComSucNum; 	  		//通信成功次数
	INT32U	ComFauNum;	  		//连续通信失败次数
	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_F_Stru;

//设备抄收成功或者返回成功  楼栋表设备
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志
	
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度

	INT32U	Instant_Current;			//瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;		//单位

	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;		//单位

	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX	X100
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//累计冷量 表底数据
	INT8U	Total_Code_Unit;			//单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	Work_Time;				//工作时间
	INT8U	STATE1; 				//热表故障状态1
	INT8U	STATE2; 				//热表故障状态1
	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_D1_Stru;


//设备抄收成功或者返回成功  用户表设备
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				    //设备编号
	INT8U	BackFlag;				//回馈标志

	
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度

	INT32U	Instant_Current;        //瞬时流量(流速)
	INT8U	Instant_Current_Unit;   //单位

	INT32U	Instant_Energy;			//瞬时热量(功率)
	INT8U	Instant_Energy_Unit;		//单位

	INT32U	Total_Current;			//累计流量
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//累计冷量 表底数据
	INT8U	Total_Code_Unit;			//单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1; 				//热表故障状态1
	INT8U	STATE2; 				//热表故障状态1
	

	
	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_D2_Stru;

//设备抄收成功或者返回成功  通断控制器1
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志

	INT16U	Set_Temp;				//面板的设定温度
	INT16U	Cur_Temp;				//当前温度
	INT16U	Ave_Temp;				//平均温度
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度
	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Face_State; 			//面板状态
	INT8U	Valve_State;			//阀门状态
	

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_D3_Stru;


//设备抄收成功或者返回成功  通断控制器2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				    //设备编号
	INT8U	BackFlag;				//回馈标志

	
	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Valve_State;			//阀门状态	


	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_D4_Stru;

//设备抄收成功或者返回成功  耐威科楼栋调节阀
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				    //控制标志
	INT8U	Dev_Type;				    //设备类型
	INT32U	Dev_ID;				        //设备编号
	INT8U	BackFlag;				    //回馈标志
	
	float	Input_Temp;                 //进水温度
	float	Output_Temp;                //回水温度
    float   EnterWater_Pressure;        //进水压力
    float   ReturnWater_Pressure;       //回水压力
    float   Room_Temp;                  //室温
    float   Current_Valve_Open;         //当前阀门开度值
    float   SetValue_Open;              //设置阀门开度值
    float   Temp_Diff;                  //温差设定值
    float   ReturnTemp_Set;             //回水温度设定值
    float   PressureDiff_Set;           //回水温度设定值
    INT16U  Error;                      //错误代码 0为正常，1为堵转，2为进水温度传感器开路，3.回水温度传感器开路，4.进水压力传感器开路，5回水压力传感器开路
    INT16U  Software_Version;           //软件版本号  100 则为 V1.0 
    INT16U  Run_Mode;                   //运行模式  0为开度模式；1为温差模式2为回温模式3为压差模式4.就地控制模式（电机掉电）5.4-20控制开度模式（需硬件支持）6 TIME
    INT16U  Address;                    //地址 1-247，默认为1
    INT16U  Motor_Steering;             //电机转向 0为正向阀，1为反向阀
    INT16U  Adjust_Switch;              //自动行程校正开关，0关闭，1为打开，值为1时每次上电自动校正行程
    INT16U  Adjust_Tigger;              //写0x5555触发一次
    INT16U  Dc_Motor_Speed;             //直流电机速度

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0X02_D5_Stru;


//主站发送采集器重启命令
typedef struct
{
	FY1000Pro_Head_Stru Head;

	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X03_Stru; 


//采集器返回即将重启命令
typedef struct
{
	FY1000Pro_Head_Stru Head;

	INT8U	State;			//反馈结果
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X04_Stru;







//主站发送用户温度设置命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//全局控制标志
	
	INT8U	Dev_Type;			//设备类型
	INT32U	Dev_ID;			//设备ID

	INT8U	Set_TCtrlFg;			//设定温度控制标志	
	INT16U	Set_Temp;			//设定温度
	
	INT8U	LimtTE_Flag;		//极限温度设定标志	
	INT16U	LimtTE_Value;		//极限设定温度
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X05_Stru;



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//反馈结果
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X06_Stru;


typedef struct
{
	FY1000Pro_Head_Stru Head;


	INT8U	Dev_Type;			//设备类型
	INT32U	Dev_ID;			//设备ID
	INT32U	CycBot_Energy;		//周期表底，用于记录周期开始时的热量值
	INT8U	CycBot_Energy_Unit;	//单位 表底数据
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X07_Stru;




typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//反馈结果
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X08_Stru;




//主站广播发送开阀/关阀命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlDemand;		//请求标志
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X09_Stru;			//主站发送采集器广播开关阀命令

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//反馈结果
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X0A_Stru;			//主站发送采集器广播开关阀命令




//主站广播发送阀门强制状态命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlDemand;		//请求标志
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X0B_Stru;			//主站发送采集器广播开关阀命令

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//反馈结果
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X0C_Stru;			//主站发送采集器广播开关阀命令







//主站发送用户阀门控制命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	DevType;			//设备类型
	INT32U	DevID;			//设备编号
	
	INT8U	CtrlDemand;		//请求标志
	INT8U	ForceFlag;			//强制标志
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X0D_Stru;			//主站发送采集器广播开关阀命令





typedef struct
{

	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//设备类型
	INT32U	DevID;			    //设备编号	
	
	INT8U	State;				//反馈结果

	INT8U	Check;			    //校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X0E_Stru;			//主站发送采集器广播开关阀命令






//服务器返回心跳数据
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	Num;			//累加值

	INT8U	Check;		    //校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X11_Stru;	





typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	Num;			//累加值
	
	INT8U	Check;		    //校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X12_Stru;	



typedef struct
{
	FY1000Pro_Head_Stru Head;
	

	INT16U	Year;			//2字节
	INT8U	Month;		    //1字节
	INT8U	Day;			//1字节	
	INT8U	Hour;			//1字节
	INT8U	Minute;		    //1字节		
	INT8U	Second;		    //1字节
	
	INT8U	Check;		    //校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X13_Stru;	



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//反馈结果
	
	INT8U	Check;		    //校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X14_Stru;	





typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CMD;			//命令标志
	
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X15_Stru;	


typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//反馈结果
	
	INT8U	Check;		//校验和
	INT8U	End;			//结束标志
}FY1000_Pack0X16_Stru;	



//主站发送阀门缴费状态切换命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//设备类型
	INT32U	DevID;			//设备编号
	INT8U	CtrlDemand;		//请求标志

	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X17_Stru;			


typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//设备类型
	INT32U	DevID;			//设备编号	
	INT8U	State;				//反馈结果
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志

}FY1000_Pack0X18_Stru;			



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//设备类型
	INT32U	DevID;			//设备编号	
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志

}FY1000_Pack0X19_Stru;			



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//设备类型
	INT32U	DevID;			//设备编号
	INT8U	State;				//控制标志

	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X1A_Stru;	





//采集器发送GPRS模块的主站IP地址配置命令
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT64U	COMFlag;			//命令编码
	
	INT8U	IP1;				//IP地址1段
	INT8U	IP2;				//IP地址2段
	INT8U	IP3;				//IP地址3段
	INT8U	IP4;				//IP地址4段
	INT16U	PortNum;			//端口号
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X40_Stru; 		

typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT64U	COMFlag;			//命令编码
	
	INT8U	IP1;		//IP地址1段
	INT8U	IP2;		//IP地址2段
	INT8U	IP3;		//IP地址3段
	INT8U	IP4;		//IP地址4段
	INT16U	Port;		//端口号
	
	INT8U	Check;	//校验和
	INT8U	End;		//结束标志
}FY1000_Pack0X41_Stru; 		//采集器发送IP地址配置返回命令



//GPRS模块返回通信状态数据

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT64U	COMFlag;			//命令编码
	
	INT8U	IPA1;				//IP地址1段
	INT8U	IPA2;				//IP地址2段
	INT8U	IPA3;				//IP地址3段
	INT8U	IPA4;				//IP地址4段
	INT16U	Port;				//端口号	
	INT8U	IPX;				//隔离符
	INT8U	IPB1;				//IP地址1段
	INT8U	IPB2;				//IP地址2段
	INT8U	IPB3;				//IP地址3段
	INT8U	IPB4;				//IP地址4段
	INT8U	CCID[20];			//手机卡标识

	INT8U 	GPRS_Power_Flg;		//电源标志
	INT8U 	GPRS_ONOFF_Flg;	//开关机标志
	INT8U 	SIMCard_State;		//手机卡状态

	INT8U 	CSQ1; 			//信号强度1
	INT8U 	CSQ2; 			//信号强度2
	
	INT8U	Check;			//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0X43_Stru;






//设备通信失败
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//控制标志
	INT8U	Dev_Type;			//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;			//回馈标志

	INT32U	ComTolNum;			//通信总次数
	INT32U	ComSucNum; 	  		//通信成功次数
	INT32U	ComFauNum;	  		//连续通信失败次数
	
	INT8U	Check;				//校验和
	INT8U	End;				//结束标志
}FY1000_Pack0XB0_F_Stru;



//设备抄收成功或者返回成功  楼栋表设备
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志
	
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度

	INT32U	Instant_Current;			//瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;		//单位

	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;		//单位

	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX	X100
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//累计冷量 表底数据
	INT8U	Total_Code_Unit;			//单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	Work_Time;				//工作时间
	INT8U	STATE1; 				//热表故障状态1
	INT8U	STATE2; 				//热表故障状态1

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0XB0_D1_Stru;


//设备抄收成功或者返回成功  用户表设备
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志
	
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度

	INT32U	Instant_Current;			//瞬时流量(流速)
	INT8U	Instant_Current_Unit;		//单位

	INT32U	Instant_Energy;			//瞬时热量(功率)
	INT8U	Instant_Energy_Unit;		//单位

	INT32U	Total_Current;			//累计流量
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//累计冷量 表底数据
	INT8U	Total_Code_Unit;			//单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1; 				//热表故障状态1
	INT8U	STATE2; 				//热表故障状态1

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0XB0_D2_Stru;

//设备抄收成功或者返回成功  通断控制器1
typedef struct
{
	FY1000Pro_Head_Stru Head;

	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志

	INT16U	Set_Temp;				//面板的设定温度
	INT16U	Cur_Temp;				//当前温度
	INT16U	Ave_Temp;				//平均温度
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度
	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Face_State; 			//面板状态
	INT8U	Valve_State;			//阀门状态

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0XB0_D3_Stru;


//设备抄收成功或者返回成功  通断控制器2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//控制标志
	INT8U	Dev_Type;				//设备类型
	INT32U	Dev_ID;				//设备编号
	INT8U	BackFlag;				//回馈标志

	
	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Valve_State;			//阀门状态	


	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0XB0_D4_Stru;

//设备抄收成功或者返回成功  通断控制器2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				    //控制标志
	INT8U	Dev_Type;				    //设备类型
	INT32U	Dev_ID;				        //设备编号
	INT8U	BackFlag;				    //回馈标志
	
	float	Input_Temp;                 //进水温度
	float	Output_Temp;                //回水温度
    float   EnterWater_Pressure;        //进水压力
    float   ReturnWater_Pressure;       //回水压力
    float   Room_Temp;                  //室温
    float   Current_Valve_Open;         //当前阀门开度值
    float   SetValue_Open;              //设置阀门开度值
    float   Temp_Diff;                  //温差设定值
    float   ReturnTemp_Set;             //回水温度设定值
    float   PressureDiff_Set;           //回水温度设定值
    INT16U  Error;                      //错误代码 0为正常，1为堵转，2为进水温度传感器开路，3.回水温度传感器开路，4.进水压力传感器开路，5回水压力传感器开路
    INT16U  Software_Version;           //软件版本号  100 则为 V1.0 
    INT16U  Run_Mode;                   //运行模式  0为开度模式；1为温差模式2为回温模式3为压差模式4.就地控制模式（电机掉电）5.4-20控制开度模式（需硬件支持）6 TIME
    INT16U  Address;                    //地址 1-247，默认为1
    INT16U  Motor_Steering;             //电机转向 0为正向阀，1为反向阀
    INT16U  Adjust_Switch;              //自动行程校正开关，0关闭，1为打开，值为1时每次上电自动校正行程
    INT16U  Adjust_Tigger;              //写0x5555触发一次
    INT16U  Dc_Motor_Speed;             //直流电机速度

	INT8U	Check;				//校验和
	INT8U	End;					//结束标志
}FY1000_Pack0XB0_D5_Stru;

//	（0XBA）服务器开启下载文件 / 服务器下载文件包 / 服务器文件下载结束
typedef struct
{

	FY1000Pro_Head_Stru Head;
	INT8U	EOH;				//数据包长度
	INT8U	NUM;				//数据包序号
	INT8U	ByteF[512];			//文件流
	INT16U   CRC16;			//文件流校验标志
	INT8U	Check;			//数据校验和
	INT8U	End;				//结束标志		
}FY1000_Pack0XBA_Stru;


//	（0XBB）采集器软件版本号查询
typedef struct
{

	FY1000Pro_Head_Stru Head;

	INT8U	Check;			//数据校验和
	INT8U	End;				//结束标志		
}FY1000_Pack0XBB_Stru;


//	（0XBF）服务器传输采集器在线升级文件
typedef struct
{

	FY1000Pro_Head_Stru Head;
	
	INT8U	NUM;				//服务器下发的序号
	INT8U  	Ack;				//应答标志
	INT8U	Check;			//数据校验和
	INT8U	End;				//结束标志		
}FY1000_Pack0XBF_Stru;

/* 查询软件版本号返回 */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT32U Version;				//版本号（32位int值）
	INT8U Check;				//数据校验和
	INT8U End;					//结束标志		
}FY1000_Pack0XBC_Stru;

/* 文件更新指令下发 */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U CMD;					//文件更新类型（0x01BOOT，0x02应用，0x03参数）
	INT8U Check;				//数据校验和
	INT8U End;					//结束标志		
}FY1000_Pack0XBD_Stru;

/* 文件更新应答 */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U RESULT;				//操作结果（0x01成功，0x02失败）
	INT8U Check;				//数据校验和
	INT8U End;					//结束标志		
}FY1000_Pack0XBE_Stru;


/* 采集器注册服务器 */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U Check;				//数据校验和
	INT8U End;					//结束标志		
}FY1000_Pack0XFE_Stru;


/*服务器 注册返回*/
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U Check;				//数据校验和
	INT8U End;					//结束标志		
}FY1000_Pack0XFF_Stru;




typedef union
{
	INT8U Data[FY1000Pro_PackSize];
	struct
	{
		INT8U	Start;		//起始字符	1字节
		INT8U	Version;	//协议类型	1字节
		INT32U	SN;		//产品序列号	4字节
		INT8U	ConType;	//协议编码	1字节
		INT32U	Lenth;	//数据长度	1字节
		INT8U	Available[FY1000Pro_PackSize-FY1000Pro_HeadSize];//有效数据区
	}DefaultPack;	
	
	FY1000_Pack0X01_Stru		Pack_0X01;
	
	FY1000_Pack0X02_N_Stru	Pack_0X02_N;
	FY1000_Pack0X02_F_Stru	Pack_0X02_F;
	FY1000_Pack0X02_D1_Stru	Pack_0X02_D1;
	FY1000_Pack0X02_D2_Stru	Pack_0X02_D2;
	FY1000_Pack0X02_D3_Stru	Pack_0X02_D3;
	FY1000_Pack0X02_D4_Stru	Pack_0X02_D4;
	
	FY1000_Pack0X03_Stru		Pack_0X03;
	FY1000_Pack0X04_Stru		Pack_0X04;

	FY1000_Pack0X05_Stru		Pack_0X05;
	FY1000_Pack0X06_Stru		Pack_0X06;

	FY1000_Pack0X07_Stru		Pack_0X07;
	FY1000_Pack0X08_Stru		Pack_0X08;

	FY1000_Pack0X40_Stru		Pack_0X40;	
	FY1000_Pack0X41_Stru		Pack_0X41;	

	FY1000_Pack0X43_Stru		Pack_0X43;	

	FY1000_Pack0X09_Stru		Pack_0X09;
	FY1000_Pack0X0A_Stru		Pack_0X0A;

	FY1000_Pack0X0B_Stru		Pack_0X0B;
	FY1000_Pack0X0C_Stru		Pack_0X0C;

	
	FY1000_Pack0X0D_Stru		Pack_0X0D;
	FY1000_Pack0X0E_Stru		Pack_0X0E;

	FY1000_Pack0X11_Stru		Pack_0X11;
	FY1000_Pack0X12_Stru		Pack_0X12;
	
	FY1000_Pack0X13_Stru		Pack_0X13;
	FY1000_Pack0X14_Stru		Pack_0X14;

	FY1000_Pack0X15_Stru		Pack_0X15;
	FY1000_Pack0X16_Stru		Pack_0X16;

	FY1000_Pack0X17_Stru		Pack_0X17;
	FY1000_Pack0X18_Stru		Pack_0X18;

	FY1000_Pack0X19_Stru		Pack_0X19;
	FY1000_Pack0X1A_Stru		Pack_0X1A;

	FY1000_Pack0XB0_F_Stru	Pack_0XB0_F;
	FY1000_Pack0XB0_D1_Stru	Pack_0XB0_D1;
	FY1000_Pack0XB0_D2_Stru	Pack_0XB0_D2;
	FY1000_Pack0XB0_D3_Stru	Pack_0XB0_D3;
	FY1000_Pack0XB0_D4_Stru	Pack_0XB0_D4;
    FY1000_Pack0XB0_D5_Stru	Pack_0XB0_D5;

	FY1000_Pack0XBA_Stru	Pack_0XBA;
	FY1000_Pack0XBF_Stru		Pack_0XBF;
	FY1000_Pack0XBD_Stru	Pack_0XBD;

	FY1000_Pack0XFE_Stru		Pack_0XFE;
	FY1000_Pack0XFF_Stru		Pack_0XFF;

	FY1000_Pack0XBB_Stru		Pack_0XBB;

}FY1000_Pack_Uni;



typedef union
{
	FY1000_Pack0X02_N_Stru		Pack_0X02_N;
	FY1000_Pack0X02_F_Stru		Pack_0X02_F;
	FY1000_Pack0X02_D1_Stru		Pack_0X02_D1;
	FY1000_Pack0X02_D2_Stru		Pack_0X02_D2;
	FY1000_Pack0X02_D3_Stru		Pack_0X02_D3;
	FY1000_Pack0X02_D4_Stru		Pack_0X02_D4;
	FY1000_Pack0X02_D5_Stru		Pack_0X02_D5;
    
	FY1000_Pack0X04_Stru		Pack_0X04;
	
	FY1000_Pack0X06_Stru		Pack_0X06;

	FY1000_Pack0X08_Stru		Pack_0X08;
	
	FY1000_Pack0X0A_Stru		Pack_0X0A;
	
	FY1000_Pack0X0C_Stru		Pack_0X0C;

	FY1000_Pack0X0E_Stru		Pack_0X0E;

	FY1000_Pack0X12_Stru		Pack_0X12;
	FY1000_Pack0X14_Stru		Pack_0X14;	

	FY1000_Pack0X16_Stru		Pack_0X16;	
	FY1000_Pack0X18_Stru		Pack_0X18;	
	FY1000_Pack0X1A_Stru		Pack_0X1A;	
	
	FY1000_Pack0X40_Stru		Pack_0X40;


	FY1000_Pack0XB0_F_Stru		Pack_0XB0_F;
	FY1000_Pack0XB0_D1_Stru		Pack_0XB0_D1;
	FY1000_Pack0XB0_D2_Stru		Pack_0XB0_D2;
	FY1000_Pack0XB0_D3_Stru		Pack_0XB0_D3;
	FY1000_Pack0XB0_D4_Stru		Pack_0XB0_D4;
    FY1000_Pack0XB0_D5_Stru	    Pack_0XB0_D5;

	
	FY1000_Pack0XBF_Stru		Pack_0XBF;
	FY1000_Pack0XBC_Stru 	    Pack_0XBC;
	FY1000_Pack0XBE_Stru		Pack_0XBE;
	FY1000_Pack0XFE_Stru		Pack_0XFE;

}FY1000_Send_Uni;



#pragma pack()		//字节对齐

typedef struct
{
	INT8U PackCreatFlag;				//发送协议创建标志 打包控制参数
	INT8U PackINPort;				//发送协议入口序号 打包控制参数
	FY1000_Send_Uni SendData;			//发送数据区
	
}UART_TO_FY1000_QueueSend_Stru;




#define UART_TO_FY1000_Q_NUM		32					//定义发送消息队列的数量
FY1000PRO_EXT QueueHandle_t UART_TO_FY1000_Msg;				//协议控制器消息队列句柄
FY1000PRO_EXT UART_TO_FY1000_QueueSend_Stru UART_TO_FY1000_OutArray[UART_TO_FY1000_Q_NUM];
FY1000PRO_EXT UART_TO_FY1000_QueueSend_Stru* UART_TO_FY1000_OutArrayP[UART_TO_FY1000_Q_NUM];

FY1000PRO_EXT INT8U UART_TO_FY1000_OutRecord;	//入栈计数器

FY1000PRO_EXT BaseType_t UART_TO_FY1000_CCB_QueueSend(UART_TO_FY1000_QueueSend_Stru *InPut);


#ifdef _FY1000PRO_C_
INT8U FY1000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT32U DataSize);
INT8U FY1000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



UART_TO_FY1000_QueueSend_Stru FY1000_Q_RX_Buffer;		//通信发送队列 接收缓冲器
UART_TO_FY1000_QueueSend_Stru* FY1000_Q_RX_BufferP;		//通信发送队列 接收缓冲器



#endif
 






 
FY1000PRO_EXT void          FY1000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY1000PRO_EXT INT8U         FY1000_Pack_TxServer_S( UART_RBC_Stru* Ctrl_Point );
FY1000PRO_EXT BaseType_t    FY_1000Send_Code_QInput( UART_TO_FY1000_QueueSend_Stru*DataBuffer_P, INT8U PackPort );
FY1000PRO_EXT int           fy1000SendMetexInit(void);




#pragma pack(1)		//字节对齐

typedef struct
{
	INT8U State;	//接收状态
	INT8U EOH;	//数据包长度
	INT8U NUM;	//文件编号
	INT8U ErrorNum;
	INT32U TickCount;
	INT32U PackAddr;	//Flash写入地址

}FileTrans_Stru;
FY1000PRO_EXT	FileTrans_Stru FileTransCrtl;
#pragma pack()		//字节对齐




FY1000PRO_EXT INT16U SerReg_Flg;		//系统注册标记  收不到系统回复命令时 始终发送注册命令

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
