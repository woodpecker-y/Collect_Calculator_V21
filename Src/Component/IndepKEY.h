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
* @date :2016-12-10 15:23
***************************************************************
*/ 
#ifndef _INDEPKEY_H_
#define _INDEPKEY_H_

#include "stdio.h"
#include "stm32f4xx.h"
#include "TypeDef.h"
#include "Keyboard.h"


#ifdef _INDEPKEY_C_
#define INDEPKEY_EXT
#else
#define INDEPKEY_EXT extern
#endif
 
#define IndepKEY_Num			6	//定义成员数量

#define IndepKEY_ExtInitHOOK		1	//宏定义是否允许挂接外部初始化函数



typedef void (*VOIDP)(void); 	//回调函数类型声明


typedef enum
{
	/* 按键触发条件 */
	DEFNULL =0x00,		//无效
	FallEdge =0x01,		//下降沿
	LowLevel =0x02,		//低电平
	UpEdge =0x04,		//上升沿
	/* end*/
	
	/* 按键读取状态 */
	ReadStateON =0XAA,	//读回状态 "按键被按下"
	ReadStateOFF =0X00	//读回状态 "按键未触发"
	/* end*/
}IndepKEY_State;



typedef struct
{
	IndepKEY_State	TrigCondition;		//触发条件
	INT32U	FallEdge_Num;		    //滤波触发参数
	INT32U	LowLevel_NumFirst;		//首次延时触发参数
	INT32U	LowLevel_Num;		    //延时触发参数
	INT32U	UpEdge_Num;		    //滤波触发参数

}
IndepKEYPara_Stru;

typedef struct
{
	FunctionalState	Enable;		    	//成员控制启用标志位
	IndepKEYPara_Stru TrigPara;			//触发参数

	IndepKEY_State (*GetKeyStatus)(void);		//获取按键状态 钩子
	
	IndepKEY_State PreStatus;			    //按键比较状态
	IndepKEY_State CurStatus;			    //按键当前状态
	
	IndepKEY_State TrigStatus;				//触发状态  用于引导键值

	INT32U	FallEdge_Count;				//滤波触发计数器
	INT32U	LowLevel_CountFirst;			//延时触发计数器 首次
	INT32U	LowLevel_Count;			    //延时触发计数器
	INT32U	UpEdge_Count;			    //滤波触发计数器
	void (*TrigOUT)(void);			    //触发函数

}IndepKEY_Stru;


#ifdef _INDEPKEY_C_

INT8U IndepKEY_Limiter;



	#if IndepKEY_ExtInitHOOK==1	//使能外部初始化钩子函数 并挂接

	VOIDP IndepKEY_ExtInitHooks =Keyboard_GPIO_Init;

	#endif


#endif

 //全局变量声明
INDEPKEY_EXT  IndepKEY_Stru IndepKEY_Ctrler[IndepKEY_Num];    //成员控制器


INDEPKEY_EXT void IndepKEYFunction_Init(void);
INDEPKEY_EXT IndepKEY_Stru*  IndepKEY_Create(FunctionalState Enable, IndepKEYPara_Stru ParaS, IndepKEY_State (*InputHooks)(void),void (*OutPutHooks)(void));
INDEPKEY_EXT void IndepKEY_Enable(IndepKEY_Stru *Member,FunctionalState Enable);
INDEPKEY_EXT void IndepKEY_ScanServer(void)  ;


#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
