


/*
***********************************************************************************
*			
*功能：使用系统时钟作为基准源实现简单的PWM控制 LED 蜂鸣器等均匀闪烁的器件
*
*
*
*说明：	1.可以实现闪烁次数控制
*    		2.可以设置周期的长度
*     		3.可以匹配边沿前后的电平状态 state
		4.可以设置跳变沿的长度
*
*
*By			:许伟
*Contact	:511328030@qq.com
*History	:2015/5/18 9:14:21
***********************************************************************************
*/
#ifndef _PULSE_H_
#define _PULSE_H_

#include "stm32f4xx_hal.h"
#include "TypeDef.h"
#include "stm32f4xx_hal_msp.h"


#ifdef _PULSE_C_
#define PULSE_EXT
#else 
#define PULSE_EXT extern
#endif 

#define PaulseLeaguer_Num	4		//定义成员数量  数组长度
typedef void (*FUNCReCall)(INT8U ); 	//回调函数类型声明

typedef struct
{
    INT8U	Enable;				//脉宽控制启用标志
    INT32U	Ticks;					//时钟跟踪器，用于记录系统的时钟
    INT8U	PulseNum;				//发送脉冲的数量
    INT32U	Space;				//间隔扫描器，系统时钟会以此间隔时间处理服务函数
    INT16U	CycleNum;				//周期
    INT16U	Edge_Num;				//边沿跳变宽度
    INT16U	CycleTick;				//单周期记录器
    INT8U	State;					//状态记录器  1说明当前处于周期的第一阶段 0说明处于周期的第二阶段

 //   void (*F_callback_P) (INT8U );
    FUNCReCall	F_callback_P; 			//回调函数指针
}Pulse_Stru;

//静态局部变量声明
#ifdef _PULSE_C_

INT8U Leaguer_Limiter;
//系统时钟源挂接
INT32U* Pulse_ClockTick= &SystemTick_ms;





#endif 

//全局变量声明
PULSE_EXT Pulse_Stru Pulse_CTRL[PaulseLeaguer_Num];

PULSE_EXT void Init_PaulseFunction(void);	//模块功能初始化
PULSE_EXT Pulse_Stru*  Pulse_Create(INT8U Enable,FUNCReCall f_callback);//创建一个脉冲控制
PULSE_EXT void PulseLeaguer_SET(Pulse_Stru *Member,INT8U PulseNum,INT32U	Space,INT16U Edge_Num,INT16U CycleNum,INT16U CycleTick,INT8U	State);//修改某个脉冲控制的参数和数据
PULSE_EXT void PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable);//使能某个脉冲控制模块

PULSE_EXT void PulseCtrl_Executing(void);//脉冲控制功能执行

#endif



