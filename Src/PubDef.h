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
* @date :2017/8/30 8:56
***************************************************************
*/ 
#ifndef _PUBDEF_H_
#define _PUBDEF_H_
 


#include "TypeDef.h"
 
#ifdef _PUBDEF_C_
#define PUBDEF_EXT
#else
#define PUBDEF_EXT extern
#endif
 

/*
系统默认参数数据初始化
*/
#define SYSTEM_BulidTime            0X20191020			//系统编译日期
#define SYSTEM_VERSION              20191020            //采集器软件版本号（32位无符号整数）



#define Valve_U_TempChange          0					//通断控制器温度修正  "0":不修正  "1":修正



/**/
#define MAXUser_Num                 (320)				//系统最大用户容量
#define MAXBuldMeter_Num			(20)                 //系统最大楼栋热表容量
#define MAXUserMeter_Num			(MAXUser_Num)		//系统最大用户热表容量
#define MAXUserValve_Num			(0)	//系统最大用户通断控制器容量
#define MAXDevice_Num				(MAXBuldMeter_Num+MAXUserMeter_Num+MAXUserValve_Num)




#define RemoRebotCont			    10ul                    //定义远程重启延时 单位秒
#define USE_POWRELAY			    0                     	//定义是否启用主回路控制继电器  "1":启用  "0":不启用

#define FileTransOUT                90000ul                 //文件传输超时退出时间 毫秒




/*系统设备启用选项宏定义*/
/*屏蔽该宏定义，系统中将不在为该设备分配资源*/


#define Meter_B_ENABLE          //大口径楼栋热量表 FY-188
#define Meter_U_ENABLE          //小口径用户热量表 FY-188
#define Valve_U_ENABLE          //户用通断控制器   FY-2000
#define Valve_UH_ENABLE         //户用通断控制器(回水控制阀) FY-2000


#define Meter_H_ENABLE          //汇中楼栋热量表 HZ-188
//#define Meter_XY_ENABLE         //祥源小口径热量表XY-188

//#define Meter_HT2X_ENABLE       //海通小口径热量表HT2X
//#define Meter_BRC_ENABLE        //山东贝特智联小口径热量表BRC
#define Meter_DDF2_ENABLE       //海通通断控制器 DDF2

#define Valve_NWK_ENABLE        //耐威科楼栋单元调节阀modbus协议



/*END*/



/*系统设备类型枚举*/

typedef enum
{
	/* 设备类型 */

	DEFUNULL =0X00,		    //无效
	
#ifdef Meter_B_ENABLE
	Meter_B =0X01,			//大口径楼栋热量表 FY-188
#endif	

#ifdef Meter_U_ENABLE
	Meter_U =0X02,          //小口径用户热量表 FY-188
#endif

#ifdef Valve_U_ENABLE
	Valve_U =0X03,			//户用通断控制器   FY-2000
#endif

#ifdef Valve_UH_ENABLE
	Valve_UH =0X04,		    //户用通断控制器(回水控制阀) FY-2000
#endif

#ifdef Meter_H_ENABLE
	Meter_H =0x05,		    //汇中楼栋热量表 HZ-188
#endif

#ifdef Meter_XY_ENABLE
	Meter_XY =0x06,		    //祥源小口径热量表XY-188
#endif	

#ifdef Meter_HT2X_ENABLE
    Meter_HT2X =0x07,	    //海通小口径热量表HT2X
    Meter_HT3X =0x0A,	    //海通小口径热量表HT3X     ，该设备类型和HT2X只差附加代码和控制字的区别
#endif

#ifdef Meter_BRC_ENABLE
    Meter_BRC =0x08,	    //山东贝特智联小口径热量表BRC
#endif

#ifdef Meter_DDF2_ENABLE
    Meter_DDF2 =0x09,	    //海通通断控制器 DDF2
#endif

#ifdef Valve_NWK_ENABLE
    Valve_NWK =0x0B,	    //耐威科楼栋单元调节阀modbus协议
#endif

}SysDEV_Type;


#define MAXDevTypeNum 11



typedef enum
{
	kW =0X17,               //功率单位	千瓦
	kW_h =0X05,             //能量单位 	千瓦.时
	MW=0X1A,                //功率单位	兆瓦
	MW_h=0X08,              //能量单位	兆瓦.时	
	m3PreH =0X35,           //流量单位	立方米每小时
	m3 =0X2C,               //容量单位	立方米
	GJ=0X11                 //能量单位	G焦耳
	
}MeterUnit_Type;



typedef enum
{
	Type_NotSet=0X00,			//计量类型未设置
	Type_Meter=0X01,			//热量表计量系统
	Type_MeterValve=0X02,		//温控计量  含表含阀
	Type_Valve=0X03             //通断时间面积法 只有阀 没有表

}DeviceType;


typedef enum
{
	DevSendMode_Nor=0,          //不自动上报
	DevSendMode_Auto=1,         //自动跟随上报
	DevSendMode_Loop=2,         //定时循环上报
}DeviceSendType;                //设备数据上报类型






typedef enum
{

	TCFlag_OFF  =0XFF,
	TCFlag_ON   =0XAA,

	Valve_Open	=(INT8U)0X0A,	//开阀	请求开启标志
	Valve_Mid	=(INT8U)0X55,	//中间状态
	Valve_Close	=(INT8U)0XA0,	//关阀	请求开启标志

}Flag_Type;

typedef enum
{
	Force_Nor 	=(INT8U)0X00,	//非强制状态		
	Force_Close	=(INT8U)0XAA,	//强制关阀
	Force_Open	=(INT8U)0X55,	//强制开阀
}ValveForce_Type;



#include "UserPara.h"
#include "DevPara.h"


/* SPI Flash存储区地址宏定义*/
#define	SysPara_Addr                100UL                   //系统参数存储起始地址
#define	SysUserList_Addr            4096UL*16ul             //用户参数记录列表起始地址
#define	SysUserList_Size            (SysDeviceList_Addr - SysUserList_Addr)
#define	SysDeviceList_Addr			4096UL*32ul             //系统设备记录列表起始地址
#define	SysDeviceList_Size			(SysOTAPara_Addr   -SysDeviceList_Addr)
#define	SysOTAPara_Addr				4096UL*64ul
#define	SysOTAPara_Size				(SysDownload_Temp_Addr -SysOTAPara_Addr)

#define	SysDownload_Temp_Addr       (4096UL*68ul)           //文件下载缓存区起始地址
#define	SysDownload_Temp_Size       (4096UL*256ul)          //文件下载缓存区大小



/*  铁电存储区地址宏定义   */
#define	PowerState_Addr             (0)                     //用户数据列表地址
#define	UserData_Addr               (16ul)                  //用户数据列表地址
#define	DevData_Addr                (UserData_Addr+MAXUser_Num*sizeof(UserData_Stru)+32ul)  //设备类数据列表起始地址
#define	FRAM_USED                   (DevData_Addr+MAXDevice_Num*sizeof(SysDevData_Stru))


#define	LCD_OFF_TICKS               (120*1000ul)                                                         //定义LCD息屏 延时间隔



#ifdef _PUBDEF_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
