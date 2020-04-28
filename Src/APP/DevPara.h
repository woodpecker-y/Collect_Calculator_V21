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
* @brief :该文件用于管理采集器所辖通信设备的参数/状态数据

* 
* 
* 
*
* @author :许伟
* @date :2017/8/29 14:52
***************************************************************
*/ 
#ifndef _DEVPARA_H_
#define _DEVPARA_H_
 

#include "TypeDef.h"
#include "PubDef.h"

#include "W25QXX.H"
#include "FRAM.H"


 
#ifdef _DEVPARA_C_
#define DEVPARA_EXT
#else
#define DEVPARA_EXT extern
#endif


/* 系统通信终端设备参数 结构

用于管理采集器下属所用通信终端设备
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
    INT16U		Num;				//数组下标，用于快速检索
	SysDEV_Type	Type;				//设备类型
	INT32U		ID;                 //设备ID
	INT16U		UserNum;			//用户列表下标 ，用于快速检索
	INT32U		UserKEY;			//用户主键，用于标志采集器管理范围内的唯一识别对象
	INT8U		COM_Type;			//通信类型 该参数定义为通信接口
	
}SysDevPara;


typedef struct
{
	SysDevPara		Device[MAXDevice_Num];
	INT16U          CRC16;		//校验值
	
}SysDeviceList_Stru;
DEVPARA_EXT SysDeviceList_Stru SysDeviceList;	//系统设备列表


#pragma pack()		//字节对齐模式 节省存储空间


/*设备类型1数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;		//瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;	//单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;		//单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;		//单位 表底数据
	
	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态1
	
	INT16U	CRC16;				    //校验码
}Dev1Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间




/*
	设备类型1状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev1State_Stru;








/*设备类型2数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;        //瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;   //单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;    //单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;        //单位 表底数据
	
	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态2
	INT16U	CRC16;				    //校验码
}Dev2Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型2状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//通信总次数
	INT32U		ComSucNum; 	  	//通信成功次数
	INT32U		ComFauNum;	  	//通信连续失败次数

}Dev2State_Stru;






/*设备类型3数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间

typedef struct
{

	INT8U	Set_TCtrlFg;		//系统设定温度强制标志
	INT16U	Set_Temp;		//设定温度

	INT8U	LimtTE_Flag;	//系统极限温度强制标志
	INT16U	LimtTE_Value;	//极限设定温度

	INT8U	ControlType;	//控制类型
	
	INT8U	ForceCtrlFlg;	//强制控制标志	
						//Force_NOR 	     =(INT8U)0X00,	//非强制状态		
						//Force_Close		=(INT8U)0XAA,	//强制关阀
						//Force_Open		=(INT8U)0X55,	//强制开阀

	INT16U	Cur_Temp;			//当前温度
	INT16U	Ave_Temp;			//平均温度
	INT16U	Input_Temp;		//进水温度
	INT16U	Output_Temp;		//回水温度
	INT8U	ValvePosition;		//阀门位置
	INT32U	Cycle_OpTim;		//周期开阀时间
	INT16U	Cycle_OpRat;		//周期开阀比例
	INT32U	Apportion_Energy; 	//当前(分摊)热量	
	INT8U	Face_State; 		//面板状态
	INT8U	Valve_State;		//阀门状态

	INT16U	CRC16;		//校验码
}Dev3Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间


/*
	设备类型3状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//通信总次数
	INT32U		ComSucNum; 	  	//通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev3State_Stru;










/*设备类型4数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间

typedef struct
{

	INT8U	ControlType;	//控制类型
	
	INT8U	ForceCtrlFlg;	//强制控制标志	
						//Force_NOR 	     =(INT8U)0X00,	//非强制状态		
						//Force_Close		=(INT8U)0XAA,	//强制关阀
						//Force_Open		=(INT8U)0X55,	//强制开阀

	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Valve_State;			//阀门状态	

	INT16U	CRC16;				//校验码
}Dev4Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间


/*
	设备类型4状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//通信总次数
	INT32U		ComSucNum; 	  	//通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev4State_Stru;




/*设备类型5数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			//进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;			//瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;		//单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;		//单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;			//单位 表底数据
	
	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				//热表故障状态1
	INT8U	STATE2;				//热表故障状态1
	
	INT16U	CRC16;				//校验码
}Dev5Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型5状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev5State_Stru;




/*设备类型6数据结构
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;        //瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;   //单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;    //单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Day_Energy; 			//当前日热量4字节
	INT8U	Day_Energy_Unit;        //当前日热量单位1字节

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据-

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态1
	
	INT16U	CRC16;				    //校验码
}Dev6Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型5状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev6State_Stru;




/*设备类型7数据结构   海通超声波热量表
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;        //瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;   //单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;    //单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;        //单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态1
	
	INT16U	CRC16;				    //校验码
}Dev7Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型7状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev7State_Stru;






/*设备类型8数据结构    贝特智联
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;        //瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;   //单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;    //单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;        //单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态1
	
	INT16U	CRC16;				    //校验码
}Dev8Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型5状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev8State_Stru;



/*设备类型9数据结构 海通通断控制器 DDF2
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间

typedef struct
{

	INT8U	ControlType;	//控制类型
	
	INT8U	ForceCtrlFlg;	//强制控制标志	
						//Force_NOR 	     =(INT8U)0X00,	//非强制状态		
						//Force_Close		=(INT8U)0XAA,	//强制关阀
						//Force_Open		=(INT8U)0X55,	//强制开阀

	INT8U	ValvePosition;			//阀门位置
	INT32U	Cycle_OpTim;			//周期开阀时间
	INT16U	Cycle_OpRat;			//周期开阀比例
	INT32U	Apportion_Energy;		//当前(分摊)热量	
	INT8U	Valve_State;			//阀门状态	

	INT16U	CRC16;				//校验码
}Dev9Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间


/*
	设备类型4状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//通信总次数
	INT32U		ComSucNum; 	  	//通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev9State_Stru;



/*设备类型10数据结构   海通超声波热量表
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	INT16U	Input_Temp;			    //进水温度
	INT16U	Output_Temp;			//回水温度
	
	INT32U	Instant_Current;        //瞬时流量(流速)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Current_Unit;   //单位
	
	INT32U	Instant_Energy;			//瞬时热量(功率)4 编码格式 编码格式  HEX  X100
	INT8U	Instant_Energy_Unit;    //单位
	
	INT32U	Total_Current;			//累计流量4 编码格式 BCD 编码格式  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//累计冷量 表底数据
	INT8U	Total_Code_Unit;        //单位 表底数据

	INT32U	Total_Energy;			//累计热量 表底数据
	INT8U	Total_Energy_Unit;		//单位 表底数据

	INT32U	CycBot_Energy;			//周期表底，用于记录周期开始时的热量值

	INT32U	Apportion_Energy;		//周期内分摊热量   当前表底-周期表底
	
	INT32U	Work_Time;				//工作时间
	INT8U	STATE1;				    //热表故障状态1
	INT8U	STATE2;				    //热表故障状态1
	
	INT16U	CRC16;				    //校验码
}Dev10Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型7状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev10State_Stru;



/*设备类型11数据结构   耐威科楼栋单元调节阀NWKmodbus协议
该数据变动较大存储于FRAM
*/
#pragma pack(1)		//字节对齐模式 节省存储空间
typedef struct
{
	float	Input_Temp;                 //进水温度
	float	Output_Temp;                //回水温度
    float   EnterWater_Pressure;        //进水压力
    float   ReturnWater_Pressure;       //回水压力
    float   Room_Temp;                  //室温
    float   Current_Valve_Open;         //当前阀门开度值
    float   SetValue_Open;              //设置阀门开度值
    float   Temp_Diff;                  //温差设定值
    float   ReturnTemp_Set;             //回水温度设定值
    float   PressureDiff_Set;           //压差设定值
    INT8U   Error;                      //错误代码 0为正常，1为堵转，2为进水温度传感器开路，3.回水温度传感器开路，4.进水压力传感器开路，5回水压力传感器开路
    INT8U   Software_Version;           //软件版本号  100 则为 V1.0 
    INT8U   Run_Mode;                   //运行模式  0为开度模式；1为温差模式2为回温模式3为压差模式4.就地控制模式（电机掉电）5.4-20控制开度模式（需硬件支持）6 TIME
    INT8U   Address;                    //地址 1-247，默认为1
    INT8U   Motor_Steering;             //电机转向 0为正向阀，1为反向阀
    INT8U   Adjust_Switch;              //自动行程校正开关，0关闭，1为打开，值为1时每次上电自动校正行程
    INT8U   Adjust_Tigger;              //写0x5555触发一次
    INT8U   Dc_Motor_Speed;             //直流电机速度
    
	//INT16U	CRC16;				    //校验码
    
}Dev11Data_Stru;
#pragma pack()		//字节对齐模式 节省存储空间

/*
	设备类型11状态数据结构
*/
typedef struct
{

	INT32U		ComTolNum;		//热表通信总次数
	INT32U		ComSucNum; 	  	//热表通信成功次数
	INT32U		ComFauNum;	  	//连续通信失败次数

}Dev11State_Stru;






#pragma pack(1)		//字节对齐模式 节省存储空间
typedef union
{

    Dev1Data_Stru Device1;	//FY-188 大口径热表
    Dev2Data_Stru Device2;	//FY-188 小口径热表
    Dev3Data_Stru Device3;	//FY-2000通断控制器
    Dev4Data_Stru Device4;	//FY-2000通断控制器 回水用
	Dev5Data_Stru Device5;	//汇中CJ-T188 大口径热表
	Dev6Data_Stru Device6;	//祥源超声户用超声波热量表 XY-188
	Dev7Data_Stru Device7;	//海通超声波热量表 -188
    Dev8Data_Stru Device8;  //山东贝特智联超声波热量表 -188
    Dev9Data_Stru Device9;  //海通通断控制器 DDF2
    Dev10Data_Stru Device10;	//海通超声波热量表 -188
    Dev11Data_Stru Device11;	//耐威科楼栋单元调节阀NWKmodbus协议
    
}SysDevData_Stru;
#pragma pack()		//字节对齐模式 节省存储空间







typedef union
{
    Dev1State_Stru Device1;	//FY-188 大口径热表
    Dev2State_Stru Device2;	//FY-188 小口径热表
    Dev3State_Stru Device3;	//FY-2000通断控制器
    Dev4State_Stru Device4;	//FY-2000通断控制器 回水用
	Dev5State_Stru Device5;	//汇中CJ-T188 大口径热表
	Dev6State_Stru Device6;	//祥源超声户用超声波热量表 XY-188

    Dev7State_Stru Device7;	//海通超声波热量表 -188
    Dev8State_Stru Device8;	//山东贝特智联超声波热量表 -188
    Dev9State_Stru Device9;  //海通通断控制器 DDF2
    Dev10State_Stru Device10;  //海通超声波热量表 -188
    Dev11State_Stru Device11;  //耐威科楼栋单元调节阀NWKmodbus协议
    
}SysDevState_Stru;






DEVPARA_EXT SysDevData_Stru  SysDevData[MAXDevice_Num];	//系统设备实时数据区
DEVPARA_EXT SysDevState_Stru  SysDevStatus[MAXDevice_Num];	//系统设备状态数据区
DEVPARA_EXT INT8U	SysDevStatusErr[MAXDevice_Num];			//系统设备错误状态数据区


#ifdef _DEVPARA_C_




#endif
 


HAL_StatusTypeDef SysDeviceList_Init(void);
HAL_StatusTypeDef SysDeviceList_Update(void);
HAL_StatusTypeDef SysDeviceList_Reset(void);

HAL_StatusTypeDef SysDevData_Read(INT16U ListNum,SysDevData_Stru* Value);
HAL_StatusTypeDef SysDevData_Update(INT16U ListNum,SysDevData_Stru* Value);
HAL_StatusTypeDef SysDevData_Save(INT16U ListNum);
HAL_StatusTypeDef SysDevData_InitALL(INT16U UserNum);
HAL_StatusTypeDef SysDevData_ResetALL(INT16U DevNum);


/*

*/
typedef struct
{

    INT16U 	Num;				//设备列表下标用于快速检索
	INT32U	ID;				    //设备编号
	INT16U   Users;         	//栋表管理用户数量

}BuildMeter_Stru;


DEVPARA_EXT BuildMeter_Stru BuildMeters[MAXBuldMeter_Num];
DEVPARA_EXT HAL_StatusTypeDef GetbuildMeterMessage(void);
DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num(INT32U ID,SysDEV_Type Type,INT16U* Num);
DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num_Build(INT32U ID,SysDEV_Type Type,INT16U* Num);


DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num_FromUserID(INT32U ID,INT16U* Num);

DEVPARA_EXT void UpDateSysDevStatusErr(void);

DEVPARA_EXT void GetSystemUserNum(void);

DEVPARA_EXT void GetSystemDevMessage(void);
DEVPARA_EXT HAL_StatusTypeDef Getdevice_Num(INT32U ID,INT16U* Num);
DEVPARA_EXT HAL_StatusTypeDef GetDev_ComStatus(void);





#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
