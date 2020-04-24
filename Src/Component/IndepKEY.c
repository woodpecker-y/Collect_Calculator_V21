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
* @date :2016-12-10 15:23
***************************************************************
*/ 
#define _INDEPKEY_C_
#include "IndepKEY.h"
 
/*
    函数名称: void IndepKEYFunction_Init(void)
    函数功能:  独立按键功能初始化
    
*/

void IndepKEYFunction_Init(void)
{
	INT8U i;
	IndepKEYPara_Stru Para;

	#if IndepKEY_ExtInitHOOK==1

	 (*IndepKEY_ExtInitHooks)();

	#endif

	Para.TrigCondition =DEFNULL;
	Para.FallEdge_Num =100;
	Para.LowLevel_Num =1000;
	Para.LowLevel_NumFirst =2000;
	Para.UpEdge_Num =100;

	for(i = 0;i < IndepKEY_Num;i ++)
	{
		IndepKEY_Ctrler[i].Enable =DISABLE;
		IndepKEY_Ctrler[i].TrigPara =Para;
		IndepKEY_Ctrler[i].PreStatus =DEFNULL;
		IndepKEY_Ctrler[i].CurStatus =DEFNULL;
		IndepKEY_Ctrler[i].TrigStatus =DEFNULL;

		IndepKEY_Ctrler[i].FallEdge_Count =0;
		IndepKEY_Ctrler[i].LowLevel_CountFirst =0;
		IndepKEY_Ctrler[i].LowLevel_Count =0;
		IndepKEY_Ctrler[i].UpEdge_Count =0;
		IndepKEY_Ctrler[i].TrigOUT =NULL;
	}
}



/*
    函数功能: 创建并挂接独立按键
    @para  Enable: 使能标志
    @para    ParaS: 触发参数
                    InputHooks:入口函数，返回按键值 
                    OutPutHooks :出口函数，当按键满足触发条件后执行
    @return   : 独立按键指针              
*/
IndepKEY_Stru*  IndepKEY_Create(FunctionalState Enable, IndepKEYPara_Stru ParaS, IndepKEY_State (*InputHooks)(void),void (*OutPutHooks)(void))
{

	
	if(IndepKEY_Limiter >= IndepKEY_Num)
	{
		return 0;
	}
	
	IndepKEY_Ctrler[IndepKEY_Limiter].Enable = Enable;
	IndepKEY_Ctrler[IndepKEY_Limiter].TrigPara= ParaS;
	IndepKEY_Ctrler[IndepKEY_Limiter].GetKeyStatus= InputHooks;
	IndepKEY_Ctrler[IndepKEY_Limiter].TrigOUT= OutPutHooks;
	IndepKEY_Ctrler[IndepKEY_Limiter].PreStatus =(*IndepKEY_Ctrler[IndepKEY_Limiter].GetKeyStatus)();//键值获取
	IndepKEY_Limiter +=1;	
	return &IndepKEY_Ctrler[IndepKEY_Limiter - 1];
	
	
}


/*
     函数功能: 修改/设置 按键触发参数
    @para      Member: 按键指针
                    ParaS     : 参数数据

*/

void IndepKEY_ParaSet(IndepKEY_Stru* Member,IndepKEYPara_Stru ParaS)
{
    FunctionalState  EnaFlag;

    EnaFlag =Member->Enable;
	Member->Enable = DISABLE;
	Member->TrigPara =ParaS;
	Member->Enable = EnaFlag;
}


/*  
    使能独立按键
    @ para  Member   
    @ Enable 使能标志
*/
void IndepKEY_Enable(IndepKEY_Stru *Member,FunctionalState Enable)
{
	Member->Enable = Enable;
}



/*
    独立按键扫描服务函数
    @para:       null
    @return :   null

    注意事项: 独立按键自服务 应定周期扫描  滤波 比较 以及键值识别的相关操作和扫描周期密切相关
   
*/
void IndepKEY_ScanServer(void)  
{
	INT8U i =0;

	IndepKEY_State Status =ReadStateOFF;
	for ( i =0;i<IndepKEY_Num;i++)
	{
		if( IndepKEY_Ctrler[i].Enable ==ENABLE)	//成员使能
		{
			Status =(*IndepKEY_Ctrler[i].GetKeyStatus)();
			if ( IndepKEY_Ctrler[i].PreStatus!=Status)		//监测到发生边沿跳变
			{
				IndepKEY_Ctrler[i].LowLevel_CountFirst =0;		//电平触发计数器清零
				IndepKEY_Ctrler[i].LowLevel_Count =0;		//电平触发计数器清零

		        if( Status ==ReadStateON)	//下降沿的触发条件成立
				{
					IndepKEY_Ctrler[i].FallEdge_Count +=1;	//下降沿滤波器数值累加
					if(IndepKEY_Ctrler[i].FallEdge_Count >=IndepKEY_Ctrler[i].TrigPara.FallEdge_Num)
					{
						if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&FallEdge)//触发允许
						{
							IndepKEY_Ctrler[i].TrigStatus =FallEdge;
						    (*IndepKEY_Ctrler[i].TrigOUT)();		//出口函数调用
						}
						IndepKEY_Ctrler[i].PreStatus=Status;	//状态记录
						IndepKEY_Ctrler[i].FallEdge_Count =0;	//下降沿滤波器数值清零
					}
				}

				if(Status ==ReadStateOFF) //上升沿的触发条件成立
				{
					IndepKEY_Ctrler[i].UpEdge_Count +=1;	//上升沿滤波器数值累加
					if(IndepKEY_Ctrler[i].UpEdge_Count >=IndepKEY_Ctrler[i].TrigPara.UpEdge_Num)
					{
						if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&UpEdge)//触发允许
						{
							IndepKEY_Ctrler[i].TrigStatus =UpEdge;
                            (*IndepKEY_Ctrler[i].TrigOUT)();		//出口函数调用
						}
						IndepKEY_Ctrler[i].PreStatus=Status;	//状态记录
						IndepKEY_Ctrler[i].UpEdge_Count =0;	//上升沿滤波器数值清零
					}
				}
			}
			
			else 	//没有检测到电平翻转   说明按键为持续电平
			{
				IndepKEY_Ctrler[i].UpEdge_Count =0;	//边沿触发计数器清零
				IndepKEY_Ctrler[i].FallEdge_Count =0;
				if((Status ==ReadStateON))    //低电平的触发允许和条件成立
				{

					IndepKEY_Ctrler[i].LowLevel_CountFirst +=1;
					IndepKEY_Ctrler[i].LowLevel_Count +=1;	//上升沿滤波器数值累加
					if( IndepKEY_Ctrler[i].LowLevel_CountFirst >=IndepKEY_Ctrler[i].TrigPara.LowLevel_NumFirst)//首次下降沿滤波处理
					{
						if(IndepKEY_Ctrler[i].LowLevel_Count >=IndepKEY_Ctrler[i].TrigPara.LowLevel_Num)
						{
							IndepKEY_Ctrler[i].UpEdge_Count =0;	//上升沿滤波器数值清零
							if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&LowLevel)
							{
								IndepKEY_Ctrler[i].TrigStatus =LowLevel;
							    (*IndepKEY_Ctrler[i].TrigOUT)();		//出口函数调用
							}
							IndepKEY_Ctrler[i].LowLevel_Count =0;	//上升沿滤波器数值清零						
						}
					}
				}
			}
		}
	}

}




















 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
