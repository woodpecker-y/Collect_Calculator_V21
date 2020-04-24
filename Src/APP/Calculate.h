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
* @date :2017/10/15 17:04
***************************************************************
*/ 
#ifndef _CALCULATE_H_
#define _CALCULATE_H_
 


#include "TypeDef.h"
#include "stm32f4xx_hal_msp.h"


#ifdef _CALCULATE_C_
#define CALCULATE_EXT
#else
#define CALCULATE_EXT extern
#endif
 

#define BuldMeterMaxVal	100000000UL	//8位表底  最大计量数据是1 0000 0000		用于楼栋表自动归零的运算




typedef  struct
{
	INT32U  i;
	INT32U  j;
}TimCon;
CALCULATE_EXT TimCon TimConver;




typedef struct
{
	FunctionalState	LoopWorkFlg;	//供暖启动控制标志
	INT32S	ProvideTime;		//供暖时间
	INT32S	PassData;			//供暖季超时时间
	
}CalculateProvideTimeCtrl_Stru;

CALCULATE_EXT CalculateProvideTimeCtrl_Stru CalculateProvideTimeCtrler;

 
 
typedef struct
{
	INT32U 	TotalCellArea;			//系统总供暖面积
	FL32 	SUM_Denom;			//分母累加和
}Calcu_Data_Stru;

CALCULATE_EXT Calcu_Data_Stru SystemCal_DATA;






 
#ifdef _CALCULATE_C_




#endif
 




 
CALCULATE_EXT INT32S CalculateProvideTimeServer(void);
CALCULATE_EXT void SystemEnergyValue_Cal(void);





 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
