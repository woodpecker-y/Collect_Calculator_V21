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
* @date :2017/9/4 12:00
***************************************************************
*/ 
#ifndef _APP_UI_H_
#define _APP_UI_H_
 

#include "TypeDef.h"
#include "UC1698.h"
#include "String.h"



 
#ifdef _APP_UI_C_
#define APP_UI_EXT
#else
#define APP_UI_EXT extern
#endif
 


//终端状态查询结构体

typedef struct
{
	char Data[2];
	INT8U Type;
}TerminalSTA_Stru;




//屏幕值记录器
struct  SHOWMG
{
    INT8U    ra0;
    INT8U    ra1;
    INT8U    ra2;
    INT8U    ra3;
    INT8U    ra4;      //3
    INT8U    ra5;
    
};
APP_UI_EXT struct  SHOWMG ScreenRecord;

struct  PressIN_S
{
	unsigned	correct:8;		//密码验证通过标志
	unsigned	PSWErr:8;		//密码输入错误标志
	unsigned	password:16;   //密码验证中间变量
	unsigned	PSW1:16;		//密码修改1
	unsigned	PSW2:16;		//密码修改2

	unsigned	PSG1:4;       //按键记录中间变量
	unsigned	PSG2:4;

	unsigned	PSG3:4;
	unsigned	PSG4:4;

	unsigned	PSG5:4;
	unsigned	PSG6:4;

	unsigned	PSG7:4;
	unsigned	PSG8:4;

	unsigned	PSG9:4;
	unsigned	PSG10:4;

	unsigned	PSG11:4;
	unsigned	PSG12:4;

	unsigned	PSG13:4;
	unsigned	PSG14:4;

	unsigned	PSG15:4;
	unsigned	PSG16:4;

	unsigned	PSG17:4;
	unsigned	PSG18:4;	

	unsigned	PSG19:4;
	unsigned	PSG20:4;

	unsigned	PSG21:4;
	unsigned	PSG22:4;

	unsigned	PSG23:4;
	unsigned	PSG24:4;

	unsigned	PSG25:4;
	unsigned	PSG26:4;

	unsigned	PSG27:4;
	unsigned	PSG28:4;	

	unsigned	PSG29:4;
	unsigned	PSG30:4;	

	unsigned	PSG31:4;
	unsigned	PSG32:4;

	unsigned	PSG33:4;
	unsigned	PSG34:4;

	unsigned	PSG35:4;
	unsigned	PSG36:4;	

	unsigned	PSG37:4;
	unsigned	PSG38:4;

	unsigned	PSG39:4;
	unsigned	PSG40:4;	

	
	unsigned	C_Year:16;
	unsigned	C_Month:8;
	unsigned	C_Day:8;
	unsigned	C_Hour:8;
	unsigned	C_Minute:8;
	unsigned	C_Second:8;
	unsigned	C_Week:8;

	unsigned	S_Year:16;
	unsigned	S_Month:8;
	unsigned	S_Day:8;

	unsigned	F_Year:16;
	unsigned	F_Month:8;
	unsigned	F_Day:8;


	unsigned	Num_BuldMeter:16;	//栋表序号 	系统管理使用
	unsigned	Num_User:16;		//用户序号 	系统管理使用
	unsigned	Num_Dev:16;		//设备序号 	系统管理使用
	
	unsigned	User_ID:32;			//用户索引号	采集器唯一识别标志
	unsigned	Meter_ID:32;		//产品序列号	热量表出厂编号
	unsigned	Valve_ID:32;		//产品序列号	温控阀出产编号

	unsigned	Buld:8;			//楼栋号
	unsigned	Unit:8;			//单元号
	unsigned	Floor:8;			//楼层号
	unsigned	Cell:8;			//房间号
	unsigned	CellArea:16;		//房间面积

	INT32U	Device_SN;	  		//设备编码
	unsigned	DeviceType:8;		//设备类型
	
	unsigned	ControlType:8;		//费控方式
	unsigned	COM_Ctrl:8; 		//通信控制
	unsigned	IP1:8;				//IP
	unsigned	IP2:8;				//IP   
	unsigned	IP3:8;				//IP   
	unsigned	IP4:8;				//IP
	unsigned	PORT:32;//端口号

	unsigned	UserNum:16;		//用户数量
	unsigned	UserNum_Pre:8;		//系统用户数量暂存器
	unsigned	ChannelUserNum:8;	//通道用户数量
	unsigned	MeterNum:8;		//热表数量
	unsigned	MeterNum_Pre:8;		//系统热表数量暂存器


	INT16U	Input_Temp;	//进水温度
	INT16U	Output_Temp;	//回水温度
	INT32U	Instant_Current;	//瞬时流量
	INT32U	Instant_Energy;	//瞬时热量
	INT32U	Total_Current;	//累计流量
	INT32U	Total_Energy;	//累计热量
	INT32U	Apportion_Energy;//分摊热量
	INT32U	Working_Time;  //工作时间
	
	unsigned	FirstInFlag:8;//首次进入标志，设及参数配置等需要读取参数的设置界面
	unsigned	E2RomErr:8;//EERom错误标志
	unsigned	FilterErr:8;//用户检索失败标志
	
};
APP_UI_EXT struct  PressIN_S PressInData;


//光标记录器

APP_UI_EXT INT16S  CursorRecord;     //屏幕光标暂存器
APP_UI_EXT INT16U  CursorPRecord1;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord2;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord3;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord4;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord5;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord6;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord7;   //屏幕光标记录器
APP_UI_EXT INT16U  CursorPRecord8;   //屏幕光标记录器

 
 struct KEYMG
 {
	 unsigned	 flg; 	 //应用按键处理标志
	 unsigned	 value;	 //应用按键值
	 unsigned	 resp;	 //应用按键防越位变量
 };
 APP_UI_EXT struct KEYMG Keyvalue;




 
#ifdef _APP_UI_C_




#endif
 



APP_UI_EXT void Menu_KeyManager(void);
APP_UI_EXT void DisplayManager(void);
APP_UI_EXT int setServerIP( uint8_t IP1, uint8_t IP2, uint8_t IP3, uint8_t IP4, uint16_t PORT );
APP_UI_EXT void getServerIP( uint8_t *IP1, uint8_t *IP2, uint8_t *IP3, uint8_t *IP4, uint16_t *PORT );


APP_UI_EXT INT32U LCD_light_Ct;			//LCD背光控制 用于息屏

 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
