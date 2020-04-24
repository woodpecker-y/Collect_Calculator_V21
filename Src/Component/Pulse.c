/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
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
* @date :2016-10-20 17:49
***************************************************************
*/ 
#define _PULSE_C_
#include "Pulse.h"

/*
* 函数名称：Init_PaulseFunction(void)
* 函数功能：初始化虚拟脉冲发生器，上电后系统根据需要对需要加载的脉冲控制器进行初始化
* 形参含义：void
*/
void Init_PaulseFunction(void)
{
	INT8U i;
	for(i = 0;i < PaulseLeaguer_Num;i ++)
	{
		Pulse_CTRL[i].Enable =0;
	}
	
}

/*
	函数名称:PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
	函数功能:对以创建的定时器进行  启用或者关闭
	启用:TRUE
*/
void PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
{
	Member->Enable = Enable;
}

/*


*/
/*
* 函数名称:	Pulse_Stru*  Pulse_Create(INT16U interval,INT8U Enable,FUNCReCall f_callback)
* 函数功能:	创建脉冲控制成员，并设置相应参数，该函数为对外接口函数
* 形参含义:	Enable：启用标志；CallBack_P:回调函数指针
* 返回值  ：回调函数指针链接
*/
Pulse_Stru*  Pulse_Create(INT8U 	Enable, FUNCReCall f_callback)
{
	if(Leaguer_Limiter >= PaulseLeaguer_Num)
	{
		return 0;
	}
	Pulse_CTRL[Leaguer_Limiter].Enable = Enable;
	Pulse_CTRL[Leaguer_Limiter].F_callback_P = f_callback;
	Leaguer_Limiter ++;
	return &Pulse_CTRL[Leaguer_Limiter - 1];	
}

/*
	函数名称:PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
	函数功能:对以创建的脉冲控制器进行值的设置
	启用:TRUE
*/
void PulseLeaguer_SET(Pulse_Stru *Member,INT8U PulseNum,INT32U	Space,INT16U Edge_Num,INT16U CycleNum,INT16U CycleTick,INT8U	State)
{
	Member->PulseNum = PulseNum;	//脉冲数量  0XFF时数量不进行限制
	Member->Space = Space;			//扫描间隔
	Member->CycleNum = CycleNum;	//周期  间隔数
	Member->Edge_Num = Edge_Num;	//跳变  间隔数
	Member->CycleTick = CycleTick;		//周期计数器
	Member->State = State;			//状态记录器
}





void PulseCtrl_Executing(void)
{
	INT8U LOOP =0;
	for (LOOP =0;LOOP<PaulseLeaguer_Num;LOOP++)
	{
		if (Pulse_CTRL[LOOP].Enable !=0)	//允许
		{
			if (Pulse_CTRL[LOOP].PulseNum !=0)		//脉冲没有发完
			{
				if ( (*Pulse_ClockTick-Pulse_CTRL[LOOP].Ticks)>=Pulse_CTRL[LOOP].Space)//扫描周期到
				{
					Pulse_CTRL[LOOP].Ticks =*Pulse_ClockTick;
					
					if(Pulse_CTRL[LOOP].CycleTick<=Pulse_CTRL[LOOP].Edge_Num)
					{
						Pulse_CTRL[LOOP].State =1;
					}
					else
					{
						Pulse_CTRL[LOOP].State =0;
					}
					Pulse_CTRL[LOOP].CycleTick +=1;
					if( Pulse_CTRL[LOOP].CycleTick >Pulse_CTRL[LOOP].CycleNum)
					{
						Pulse_CTRL[LOOP].CycleTick =0;
						if (Pulse_CTRL[LOOP].PulseNum !=0XFF)
						{
							Pulse_CTRL[LOOP].PulseNum -=1;
						}					
					}
					(*Pulse_CTRL[LOOP].F_callback_P)(Pulse_CTRL[LOOP].State);
				}
			}
		}
	}	
}


/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/





