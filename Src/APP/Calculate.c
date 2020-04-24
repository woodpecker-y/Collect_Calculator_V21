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
* @author :许伟
* @date :2017/10/15 17:04
***************************************************************
*/ 
#define _CALCULATE_C_
#include "Calculate.h"
#include "Main.h"




/*判断平年闰年函数*/
INT8U LeapYear(INT16U year )
{
	for(TimConver.i=0;TimConver.i<year;TimConver.i++)
	{
	   if (((TimConver.i%400==0)||(TimConver.i%100!=0))&&((TimConver.i%4)==0))
	   {
			TimConver.j=TimConver.j+1;
	   }
	}
	if (((year%400==0)||(year%100!=0))&&((year%4)==0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




/*

函数名称:Con_Second (ShareTime_Str *TIME1,ShareTime_Str *TIME2)
函数功能: 计算两个时间点的间隔(S)
TIME1:现在时间
TIME2:之前时间

TIME1-TIME2  >0说明 TIME2时间在前  反之在后

*/
INT32S Con_Second (RealClock_Str *TIME1,RealClock_Str *TIME2)
{

	INT32S second =0;//定义秒数变量
	time_t T1;
	time_t T2;
	
	getTimeTick(&T1, TIME1);
	getTimeTick(&T2, TIME2);

	if(T1 >=T2)
	{
		second =T1-T2;
	}
	else
	{
		second =-(T2-T1);
	}
	return second;         //返回秒数
}






/*

	计算供暖时间长度
	@Pra  TimeSpace 间隔
	@TimeTicks  时钟源
	@ret 返回的时间 单位是秒
*/
INT32S CalculateProvideTimeServer(void)
{	
	INT32S TimeCord_Start;
	INT32S TimeCord_Final;
	INT32S TimeTotal =0;
	RealClock_Str DevsoftTime;

	DevsoftTime.Year =RTC_Time.Year;
	DevsoftTime.Month =RTC_Time.Month;
	DevsoftTime.Day =RTC_Time.Day;
	DevsoftTime.Hour =RTC_Time.Hour;
	DevsoftTime.Minute =RTC_Time.Minute;
	DevsoftTime.Second =RTC_Time.Second;

	TimeCord_Start =Con_Second (&DevsoftTime,&SysPara.StartTime);			//当前时间和供暖开始时间比较 
	if(TimeCord_Start >=0)	//当前时间在供暖开始时间之后  
	{
	
		TimeCord_Final =Con_Second (&DevsoftTime,&SysPara.FinalTime);		//当前时间和供暖结束时间比较
		
		if( TimeCord_Final >=0) //当前时间在供暖结束时间之后
		{
			TimeTotal =Con_Second (&SysPara.FinalTime,&SysPara.StartTime);
			CalculateProvideTimeCtrler.PassData =TimeCord_Final;			//供暖季之后时间
		}
		else		//当前时间在供暖季内
		{
			TimeTotal=TimeCord_Start;
			CalculateProvideTimeCtrler.PassData =0;					        //供暖季之后时间
		}
	}
	else		//当前时间在供暖开始时间之前
	{
		CalculateProvideTimeCtrler.PassData= TimeCord_Start;				//供暖季之前时间
		TimeTotal =0;
		
	}
	CalculateProvideTimeCtrler.ProvideTime =TimeTotal;
	return TimeTotal;	
	
}






/*

	用户能量消耗计算
*/



void SystemEnergyValue_Cal(void)
{

	INT32U BuildMeterID=0;			//楼栋表ID	
	INT64U BuldMeterEnergyValue =0;	//栋表 热量值
	FL32 e =0;					//运算因子
	INT32U Q =0;					//公式运算因子
	FL32 SUM =0;					//分母计算和
	
	if( SysPara.DeviceType ==Type_Valve)	//通断时间面积法计量系统
	{
	

		for( INT16U LoopBM =0;LoopBM<SysPara.BuldMeterNum;LoopBM++)	//按栋表进行计算
		{
			BuildMeterID =SysDeviceList.Device[LoopBM].ID;	//记录栋表ID
            
			if( SysDeviceList.Device[LoopBM].Type ==Meter_B)	//设备为大口径热量表表 丰源188
			{
			
				BuldMeterEnergyValue = SysDevData[LoopBM].Device1.Apportion_Energy;					//周期热量传递
				/* 表底单位切换*/
				if( SysDevData[LoopBM].Device1.Total_Energy_Unit ==MW_h)
				{
					BuldMeterEnergyValue = BuldMeterEnergyValue*1000UL;							//计算分摊热量为Mwh 转化为KWH					
				}
				
			}
#ifdef Meter_H_ENABLE
			else if( SysDeviceList.Device[LoopBM].Type ==Meter_H)								//设备为大口径热恋表 汇中188
			{

				BuldMeterEnergyValue = SysDevData[LoopBM].Device5.Apportion_Energy;					//周期热量值传递
				/* 表底单位切换*/
				if( SysDevData[LoopBM].Device5.Total_Energy_Unit ==MW_h)
				{
					BuldMeterEnergyValue = BuldMeterEnergyValue*1000UL;		//计算分摊热量为Mwh 转化为KWH					
				}
			}
#endif
			Q =BuldMeterEnergyValue;
			SUM =0;
			
			//计算积分分母	
			for( INT16U LoopUser=0;LoopUser<MAXUser_Num;LoopUser++)
			{
				if(SysUserList.User[LoopUser].BuildMeter_ID ==BuildMeterID)	//验证所属栋表的合法性
				{
					UserData[LoopUser].Total_Heat =0XAAAA;			//强制分摊  计量院用
					if(0XAAAA ==UserData[LoopUser].Total_Heat)		//验证分摊用户控制标志有效性
					{
						e=((float)UserData[LoopUser].Total_Time)/((float)CalculateProvideTimeCtrler.ProvideTime);
						SUM =SUM+(e*SysUserList.User[LoopUser].CellArea);	
					}
				}				
			}
			
			SystemCal_DATA.SUM_Denom =SUM;	

			//分摊热量计算
			for( INT16U LoopUser=0;LoopUser<MAXUser_Num;LoopUser++)
			{
				if(SysUserList.User[LoopUser].BuildMeter_ID ==BuildMeterID)
				{
					 
					if(0XAAAA ==UserData[LoopUser].Total_Heat)		//验证分摊用户控制标志有效性
					{
						e=((float)UserData[LoopUser].Total_Time)/((float)CalculateProvideTimeCtrler.ProvideTime);
						UserData[LoopUser].Apportion_Energy = (INT32U)(e*(FL32)SysUserList.User[LoopUser].CellArea*(FL32)Q/SystemCal_DATA.SUM_Denom);
					}
					else		//该用户没有交费  分摊热量清零
					{
						UserData[LoopUser].Apportion_Energy = 0;
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
