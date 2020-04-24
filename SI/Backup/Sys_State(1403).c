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
* @date :2017/9/15 14:07
***************************************************************
*/ 
#define _SYS_STATE_C_
#include "Sys_State.h"
#include "main.h"



extern EventBits_t cli_dog;//软件看门狗

void printenv(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U Type =SysPara.DeviceType;
	INT32U ReportMode =SysPara.SendMode;

	cli_printf("   设备编号:       %08X \r\n",SysPara.Device_SN);
	cli_printf("   SystemTick:     %ld \r\n",SystemTick_ms);
	cli_printf("   SystemTick(S):  %ld \r\n",SystemTick_ms/1000);
	cli_printf("   系统时间:       %4d年%2d月%2d日 %2d:%2d:%2d\r\n",RTC_Time.Year,RTC_Time.Month,RTC_Time.Day,RTC_Time.Hour,RTC_Time.Minute,RTC_Time.Second);	
	cli_printf("\r\n");
	
	cli_printf("   上电次数:       %ld \r\n",PowerStateRecord.Times);	
	cli_printf("   启动时间:       %4d年%2d月%2d日 %2d:%2d:%2d \r\n",PowerStateRecord.Year,PowerStateRecord.Month,PowerStateRecord.Day,PowerStateRecord.Hour,PowerStateRecord.Minute,PowerStateRecord.Second);	
	cli_printf("\r\n\r\n");

	switch(Type)
	{
		case Type_Meter:
		{
			cli_printf("   系统类型:  %d    热量表 采集系统\r\n",Type);	
		}break;

		case Type_MeterValve:
		{
			cli_printf("   系统类型:  %d    温控计量一体化 计量系统\r\n",Type);	
		}break;	

		case Type_Valve:
		{
			cli_printf("   系统类型:  %d    通断时间面积法 计量系统\r\n",Type);	

		}break;

		default :
		{
			cli_printf("   系统类型:  %d    未设置\r\n",Type);

		}break;
	}

	cli_printf("   终端重复间隔:   %lu \r\n",SysPara.ReadSpace);		//终端设备重复读取间隔
	cli_printf("   终端循环间隔:   %lu \r\n",SysPara.LoopSpace);		//终端设备循环读取间隔
	cli_printf("\r\n");

	switch(ReportMode)
	{
		case DevSendMode_Auto:
		{
			cli_printf("   上报模式:  %d    自动上报\r\n",ReportMode);

		}break;

		case DevSendMode_Loop:
		{
			cli_printf("   上报模式:  %d    循环上报\r\n",ReportMode);	

		}break;	

		default :
		{
			cli_printf("   上报模式:  %d    未设置\r\n",ReportMode);
			

		}break;
	}
	cli_printf("   终端上报间隔:   %lu \r\n",SysPara.SendSpace);	
	cli_printf("\r\n\r\n");

	
	cli_printf("   供暖开始时间:   %4d年%2d月%2d日 %2d:%2d:%2d  \r\n",SysPara.StartTime.Year,SysPara.StartTime.Month,SysPara.StartTime.Day,SysPara.StartTime.Hour,SysPara.StartTime.Minute,SysPara.StartTime.Second);
	cli_printf("   供暖结束时间:   %4d年%2d月%2d日 %2d:%2d:%2d  \r\n",SysPara.FinalTime.Year,SysPara.FinalTime.Month,SysPara.FinalTime.Day,SysPara.FinalTime.Hour,SysPara.FinalTime.Minute,SysPara.FinalTime.Second);
	cli_printf("   系统供暖时间:   %f    PRD:%f \r\n",(FL32)CalculateProvideTimeCtrler.ProvideTime/3600,(FL32)CalculateProvideTimeCtrler.PassData/3600);
	cli_printf("\r\n");
	cli_printf("   分摊周期:       %lu 分钟 \r\n",SysPara.Apportion_T);	
	cli_printf("\r\n\r\n");

	
	cli_printf("   主站地址:       %3d.%3d.%3d.%3d:%5d \r\n",SysPara.IP1,SysPara.IP2,SysPara.IP3,SysPara.IP4,SysPara.PortNum);

	cli_printf("   系统用户容量:   %3d \r\n",MAXUser_Num);
	cli_printf("   系统用户数量:   %3d \r\n",SysPara.UserNum);

	cli_printf("   系统栋表容量:   %3d \r\n",MAXBuldMeter_Num);
	cli_printf("   系统栋表数量:   %3d \r\n",SysPara.BuldMeterNum);

	cli_printf("   系统设备容量:   %3d \r\n",MAXDevice_Num);
	
	cli_printf("   用户设备数量:   %3d \r\n\r\n",SysPara.DevNum);
	cli_printf("   系统设备总量:   %3d \r\n\r\n",SysPara.DevNum+SysPara.BuldMeterNum);
	

}



void userpara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U userNum =0;
	
	if(argc !=2)
	{
		cli_printf("参数输入错误...\r\n");
		cli_printf("userpa X\r\n");
	}
	else
	{
		userNum= atoi(argv[1]);
		if(userNum<MAXUser_Num)
		{
			cli_printf("用户ID: %08lX\r\n\r\n",SysUserList.User[userNum].User_ID);
			cli_printf("%d号楼 %d单元 %d层 %d室\r\n",SysUserList.User[userNum].Buld,SysUserList.User[userNum].Unit,SysUserList.User[userNum].Floor,SysUserList.User[userNum].Cell);
			cli_printf("房间面积:   %d\r\n",SysUserList.User[userNum].CellArea);
			cli_printf("所属栋表:   %08lX\r\n",SysUserList.User[userNum].BuildMeter_ID);
		}
		else
		{
			cli_printf("用户索引超范围...\r\n");
		}
	}
}






void devicepara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U devNum =0;
	
	if(argc !=2)
	{
		cli_printf("参数输入错误...\r\n");
		cli_printf("devpa X\r\n");
	}
	else
	{
		devNum= atoi(argv[1]);
		if(devNum<MAXDevice_Num)
		{
			INT8U Type =0;
			Type =SysDeviceList.Device[devNum].Type;
			cli_printf("设备类型:  %d  \r\n",Type);
			switch (Type)
			{
				
				case Meter_B:
				{
					cli_printf("大口径热量表 -FY188 \r\n");
				}break;
				case Meter_U:
				{
					cli_printf("小口径热量表 -FY188 \r\n");
				}break;			
				case Valve_U:
				{
					cli_printf("户用通断控制器 -FY2000 \r\n");
				}break;	

				case Valve_UH:
				{
					cli_printf("户用回水通断控制器 -FY2000 \r\n");
				}break; 
#ifdef Meter_H_ENABLE				
				case Meter_H:
				{
					cli_printf("汇中大口径热量表 -CJ188 \r\n");
				}break; 
#endif


#ifdef  Meter_XY_ENABLE					
				case Meter_XY:
				{
					cli_printf("祥源 XY小口径热量表 -CJ188 \r\n");
				}break; 			
#endif


#ifdef  Meter_HT2X_ENABLE					
                case Meter_HT2X:
                {
                    cli_printf("海通HT2X小口径热量表 -CJ188 \r\n");
                }break;             
#endif


#ifdef  Meter_BRC_ENABLE					
                case Meter_BRC:
                {
                    cli_printf("贝特智联 BRC小口径热量表 -CJ188 \r\n");
                }break;             
#endif


#ifdef  Meter_DDF2_ENABLE					
                case Meter_DDF2:
                {
                    cli_printf("海通通断控制器 -DDF2 \r\n");
                }break;             
#endif


				default :
				{
					cli_printf("设备类型查询失败...\r\n");

				}break;

			}

			if(Type !=0)
			{
				INT16U userNum =0;
				INT32U UserKEY =0;
				cli_printf("设备序号:  %d\r\n",SysDeviceList.Device[devNum].Num);
				cli_printf("设备主键:  %08lX\r\n",SysDeviceList.Device[devNum].ID);

				userNum =SysDeviceList.Device[devNum].UserNum;
				UserKEY =SysDeviceList.Device[devNum].UserKEY;
				if( SysUserList.User[userNum].User_ID ==UserKEY)
				{
					cli_printf("所属用户:  %d\r\n",userNum);
					cli_printf("用户主键:  %08lx\r\n",UserKEY);
					cli_printf("%d号楼 %d单元 %d层 %d室\r\n\r\n",SysUserList.User[userNum].Buld,SysUserList.User[userNum].Unit,SysUserList.User[userNum].Floor,SysUserList.User[userNum].Cell);
				}
				else
				{
					cli_printf("公共计量设备...\r\n\r\n",);
				}
			}
		}
		else
		{
			cli_printf("用户索引超范围...\r\n");
		}
	}
	
	
}



void userdata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U userNum =0;
	
	if(argc !=2)
	{
		cli_printf("参数输入错误...\r\n");
		cli_printf("userda X\r\n");
	}
	else
	{
		userNum= atoi(argv[1]);
		if(userNum<MAXUser_Num)
		{
			cli_printf("用户序号:  %d\r\n",userNum);
			cli_printf("用户主键:  %08lX\r\n",SysUserList.User[userNum].User_ID);
			
			cli_printf("剩余热量:  %ld\r\n",UserData[userNum].Remain_Heat);
//			cli_printf("购买热量:  %ld\r\n",UserData[userNum].Total_Heat);
			cli_printf("分摊时间:  %f\r\n",(FL32)UserData[userNum].Total_Time/3600);
			cli_printf("累计热量:  %ld\r\n",UserData[userNum].Apportion_Energy);

		}
		else
		{
			cli_printf("用户索引超范围...\r\n");
		}
	}
	
	
}




void devicedata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U devNum =0;
	INT8U DevType =0;
	
	if(argc !=2)
	{
		cli_printf("参数输入错误...\r\n");
		cli_printf("devda X\r\n");
	}
	else
	{
		devNum= atoi(argv[1]);
		if(devNum<MAXDevice_Num)
		{
			DevType =SysDeviceList.Device[devNum].Type;
			cli_printf("设备序号:%d\r\n",devNum);
			cli_printf("ID:      %08lX\r\n",SysDeviceList.Device[devNum].ID);

			
		switch(DevType)	
		{
			case Meter_B:
			{
				cli_printf("Meter_B      大口径热量表 -FY188 \r\n");
				cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device1.Input_Temp);
				cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device1.Output_Temp);
				cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device1.Instant_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device1.Instant_Current_Unit);
				cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device1.Instant_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device1.Instant_Energy_Unit);
				cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device1.Total_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device1.Total_Current_Unit);
				cli_printf("累计冷量:    %lu\r\n",SysDevData[devNum].Device1.Total_Code);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device1.Total_Code_Unit);
				cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device1.Total_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device1.Total_Energy_Unit);
				cli_printf("周期表底:    %lu\r\n",SysDevData[devNum].Device1.CycBot_Energy);

				cli_printf("周期热量:    %lu\r\n",SysDevData[devNum].Device1.Apportion_Energy);
				cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device1.Work_Time);
				cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device1.STATE1);
				cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device1.STATE2);

				cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device1.ComTolNum);
				cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device1.ComSucNum);
				cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device1.ComFauNum);				
			}break;

		
			case Meter_U:
			{
				cli_printf("Meter_U      小口径热量表 -FY188 \r\n");
				cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device2.Input_Temp);
				cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device2.Output_Temp);
				cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device2.Instant_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device2.Instant_Current_Unit);
				cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device2.Instant_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device2.Instant_Energy_Unit);
				cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device2.Total_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device2.Total_Current_Unit);
				cli_printf("累计冷量:    %lu\r\n",SysDevData[devNum].Device2.Total_Code);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device2.Total_Code_Unit);
				cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device2.Total_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device2.Total_Energy_Unit);
				cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device2.Work_Time);
				cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device2.STATE1);
				cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device2.STATE2);

				cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device2.ComTolNum);
				cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device2.ComSucNum);
				cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device2.ComFauNum);	
			}break;
			
			case Valve_U:
			{
				cli_printf("Valve_U        户用通断控制器 -FY2000 \r\n");
				cli_printf("设定温度标志:  %02X\r\n",SysDevData[devNum].Device3.Set_TCtrlFg);
				cli_printf("设定温度:      %d\r\n",SysDevData[devNum].Device3.Set_Temp);
				
				cli_printf("极限温度标志:  %02X\r\n",SysDevData[devNum].Device3.LimtTE_Flag);
				cli_printf("极限设定温度:  %d\r\n",SysDevData[devNum].Device3.LimtTE_Value);
				
				cli_printf("控制类型:      %02X\r\n",SysDevData[devNum].Device3.ControlType);
				cli_printf("强控标志:      %02X\r\n",SysDevData[devNum].Device3.ForceCtrlFlg);
				
				cli_printf("当前温度:      %d\r\n",SysDevData[devNum].Device3.Cur_Temp);
				cli_printf("平均温度:      %d\r\n",SysDevData[devNum].Device3.Ave_Temp);
				
				cli_printf("进水温度:      %d\r\n",SysDevData[devNum].Device3.Input_Temp);
				cli_printf("出水温度:      %d\r\n",SysDevData[devNum].Device3.Output_Temp);
				
				cli_printf("阀门位置:      %02X\r\n",SysDevData[devNum].Device3.ValvePosition);
				cli_printf("开阀时间:      %lu\r\n",SysDevData[devNum].Device3.Cycle_OpTim);
				
				cli_printf("分摊热量:      %lu\r\n",SysDevData[devNum].Device3.Apportion_Energy);
				cli_printf("面板状态:      %02X\r\n",SysDevData[devNum].Device3.Face_State);
				cli_printf("阀门状态:      %02X\r\n",SysDevData[devNum].Device3.Valve_State);

				cli_printf("通信总数:      %lu\r\n",SysDevStatus[devNum].Device3.ComTolNum);
				cli_printf("通讯成功:      %lu\r\n",SysDevStatus[devNum].Device3.ComSucNum);
				cli_printf("通讯失败:      %lu\r\n",SysDevStatus[devNum].Device3.ComFauNum);	
			}break;
			
			case Valve_UH:
			{
				cli_printf("Valve_UH       户用回水通断控制器 -FY2000 \r\n");
				cli_printf("控制类型:      %02X\r\n",SysDevData[devNum].Device4.ControlType);
				cli_printf("强控标志:      %02X\r\n",SysDevData[devNum].Device4.ForceCtrlFlg);
				cli_printf("阀门位置:      %02X\r\n",SysDevData[devNum].Device4.ValvePosition);
				cli_printf("开阀时间:      %lu\r\n",SysDevData[devNum].Device4.Cycle_OpTim);

				cli_printf("阀门状态:      %02X\r\n",SysDevData[devNum].Device4.Valve_State);

				cli_printf("通信总数:      %lu\r\n",SysDevStatus[devNum].Device4.ComTolNum);
				cli_printf("通讯成功:      %lu\r\n",SysDevStatus[devNum].Device4.ComSucNum);
				cli_printf("通讯失败:      %lu\r\n",SysDevStatus[devNum].Device4.ComFauNum);	

			}break;
			
#ifdef Meter_H_ENABLE
			 case Meter_H:
			{
				cli_printf("Meter_H      汇中大口径热量表 -CJ188 \r\n");
				cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device5.Input_Temp);
				cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device5.Output_Temp);
				
				cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device5.Instant_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device5.Instant_Current_Unit);
				
				cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device5.Instant_Energy);				
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device5.Instant_Energy_Unit);
				
				cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device5.Total_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device5.Total_Current_Unit);
				
				cli_printf("累计冷量:    %lu\r\n",SysDevData[devNum].Device5.Total_Code);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device5.Total_Code_Unit);
				
				cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device5.Total_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device5.Total_Energy_Unit);
				
				cli_printf("周期表底:    %lu\r\n",SysDevData[devNum].Device5.CycBot_Energy);
				cli_printf("周期热量:    %lu\r\n",SysDevData[devNum].Device5.Apportion_Energy);
				
				cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device5.Work_Time);
				
				cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device5.STATE1);
				cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device5.STATE2);

				cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device5.ComTolNum);
				cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device5.ComSucNum);
				cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device5.ComFauNum);					
			}break;
#endif


#ifdef  Meter_XY_ENABLE	
			case Meter_XY:
			{
				cli_printf("Meter_XY     祥源小口径热量表 -XY188 \r\n");
				cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device6.Input_Temp);
				cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device6.Output_Temp);
				
				cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device6.Instant_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device6.Instant_Current_Unit);
				
				cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device6.Instant_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device6.Instant_Energy_Unit);
				
				cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device6.Total_Current);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device6.Instant_Current_Unit);
				
				cli_printf("日累计量:    %lu\r\n",SysDevData[devNum].Device6.Day_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device6.Day_Energy_Unit);
				
				cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device6.Total_Energy);
				cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device6.Total_Energy_Unit);
				
				cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device6.Work_Time);
				
				cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device6.STATE1);
				cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device6.STATE2);

				cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device6.ComTolNum);
				cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device6.ComSucNum);
				cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device6.ComFauNum);	
			}break;
#endif

#ifdef  Meter_HT2X_ENABLE

            case Meter_HT2X:
            {
                cli_printf("Meter_HT2X   海通小口径热量表 -HT2X188 \r\n");
                cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device7.Input_Temp);
                cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device7.Output_Temp);
                
                cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device7.Instant_Current);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device7.Instant_Current_Unit);
                
                cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device7.Instant_Energy);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device7.Instant_Energy_Unit);
                
                cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device7.Total_Current);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device7.Instant_Current_Unit);
                
                cli_printf("累计冷量:    %lu\r\n",SysDevData[devNum].Device7.Total_Code);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device7.Total_Code_Unit);
                
                cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device7.Total_Energy);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device7.Total_Energy_Unit);
                
                cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device7.Work_Time);
                
                cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device7.STATE1);
                cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device7.STATE2);

                cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device7.ComTolNum);
                cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device7.ComSucNum);
                cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device7.ComFauNum);  
            }break;
#endif

#ifdef  Meter_BRC_ENABLE
            
            case Meter_BRC:
            {
                cli_printf("Meter_BRC    贝特智联小口径热量表 -BRC188 \r\n");
                cli_printf("进水温度:    %d\r\n",SysDevData[devNum].Device8.Input_Temp);
                cli_printf("回水温度:    %d\r\n",SysDevData[devNum].Device8.Output_Temp);
                
                cli_printf("瞬时流量:    %lu\r\n",SysDevData[devNum].Device8.Instant_Current);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device8.Instant_Current_Unit);
                
                cli_printf("瞬时热量:    %lu\r\n",SysDevData[devNum].Device8.Instant_Energy);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device8.Instant_Energy_Unit);
                
                cli_printf("累计流量:    %lu\r\n",SysDevData[devNum].Device8.Total_Current);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device8.Instant_Current_Unit);
                
                cli_printf("累计冷量:    %lu\r\n",SysDevData[devNum].Device8.Total_Code);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device8.Total_Code_Unit);
                
                cli_printf("累计热量:    %lu\r\n",SysDevData[devNum].Device8.Total_Energy);
                cli_printf("    单位:    %02X\r\n",SysDevData[devNum].Device8.Total_Energy_Unit);
                
                cli_printf("工作时间:    %lu\r\n",SysDevData[devNum].Device8.Work_Time);
                
                cli_printf("热表状态1:   %02X\r\n",SysDevData[devNum].Device8.STATE1);
                cli_printf("热表状态2:   %02X\r\n",SysDevData[devNum].Device8.STATE2);

                cli_printf("通信总数:    %lu\r\n",SysDevStatus[devNum].Device8.ComTolNum);
                cli_printf("通讯成功:    %lu\r\n",SysDevStatus[devNum].Device8.ComSucNum);
                cli_printf("通讯失败:    %lu\r\n",SysDevStatus[devNum].Device8.ComFauNum);  
            }break;
#endif



#ifdef Meter_DDF2_ENABLE

		case Meter_DDF2:
		{
			cli_printf("Meter_DDF2     海通通断控制器 -DDF2 \r\n");
			cli_printf("阀门位置:      %02X\r\n",SysDevData[devNum].Device9.ValvePosition);

			cli_printf("通信总数:      %lu\r\n",SysDevStatus[devNum].Device9.ComTolNum);
			cli_printf("通讯成功:      %lu\r\n",SysDevStatus[devNum].Device9.ComSucNum);
			cli_printf("通讯失败:      %lu\r\n",SysDevStatus[devNum].Device9.ComFauNum);	

		}break;
#endif
			default:
			{
				cli_printf("设备数据查询失败...\r\n");
				cli_printf("请检查设备参数...\r\n");
			}break;
		
		}
			
			
		}
		else
		{
			cli_printf("用户索引超范围...\r\n");
		}
	}
	
	
}










void devicestatus(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U   DeviceT =0;
	INT32U  COM_T =0;
	INT32U  COM_S =0;
	INT32U  COMBack_CE =0;
	INT32U  DeviceNums =0;

	cli_printf("%-15s%-15s%-15s%-15s%-15s\r\n\r\n","Num","Type","COM_T","COM_S","COMBack_CE");
	for(INT16U i=0; i<MAXDevice_Num;i++)
	{	
		feedIWDG(cli_dog);
		DeviceT =SysDeviceList.Device[i].Type;
		if(DeviceT !=DEFUNULL)
		{
			DeviceNums +=1;
			switch(DeviceT)
			{
				case Meter_B:
				{
					COM_T =SysDevStatus[i].Device1.ComTolNum;
					COM_S =SysDevStatus[i].Device1.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device1.ComFauNum;
				}break;

				case Meter_U:
				{
					COM_T =SysDevStatus[i].Device2.ComTolNum;
					COM_S =SysDevStatus[i].Device2.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device2.ComFauNum;
				}break;				
				case Valve_U:
				{
					COM_T =SysDevStatus[i].Device3.ComTolNum;
					COM_S =SysDevStatus[i].Device3.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device3.ComFauNum;
				}break;
				case Valve_UH:
				{
					COM_T =SysDevStatus[i].Device4.ComTolNum;
					COM_S =SysDevStatus[i].Device4.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device4.ComFauNum;
				}break;
#ifdef Meter_H_ENABLE				
				case Meter_H:
				{
					COM_T =SysDevStatus[i].Device5.ComTolNum;
					COM_S =SysDevStatus[i].Device5.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device5.ComFauNum;
				}break;
#endif
                
#ifdef  Meter_XY_ENABLE	
				case Meter_XY:
				{
					COM_T =SysDevStatus[i].Device6.ComTolNum;
					COM_S =SysDevStatus[i].Device6.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device6.ComFauNum;
				}break;
#endif

#ifdef  Meter_HT2X_ENABLE	
                case Meter_HT2X:
                {
                    COM_T =SysDevStatus[i].Device7.ComTolNum;
                    COM_S =SysDevStatus[i].Device7.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device7.ComFauNum;
                }break;
#endif

#ifdef  Meter_BRC_ENABLE	
                case Meter_BRC:
                {
                    COM_T =SysDevStatus[i].Device8.ComTolNum;
                    COM_S =SysDevStatus[i].Device8.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device8.ComFauNum;
                }break;
#endif

#ifdef  Meter_DDF2_ENABLE	
                case Meter_DDF2:
                {
                    COM_T =SysDevStatus[i].Device9.ComTolNum;
                    COM_S =SysDevStatus[i].Device9.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device9.ComFauNum;
                }break;
#endif




				default :
				{
					COM_T =0;
					COM_S =0;
					COMBack_CE =0;
				}break;
			}
			cli_printf("%-15d%-15d%-15lu%-15lu%-15lu\r\n",i,DeviceT,COM_T,COM_S,COMBack_CE);
		}
	}
	cli_printf("查询设备总数量: %lu\r\n\r\n\r\n",DeviceNums);
	
}



void systemparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL = SysPara_Reset();		//系统参数初始化
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("系统 参数区初始化完成......\r\n");
	}
	else
	{
		cli_printf("系统 参数区初始化失败......\r\n");
	}

		
}

void userparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL = SysUserList_Reset();	//用户参数列表初始化
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("用户 参数区初始化完成......\r\n");		
	}
	else
	{
		cli_printf("用户 参数区初始化失败......\r\n");
	}

}

void deviceparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysDeviceList_Reset();		
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("设备 参数区初始化完成......\r\n");
	}
	else
	{
		cli_printf("设备 参数区初始化失败......\r\n");
	}
}

void userdatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =UserData_ResetALL(MAXUser_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("用户 数据区初始化完成......\r\n");
	}
	else
	{
		cli_printf("用户 数据区初始化失败......\r\n");
	}
}




void devicedatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysDevData_ResetALL(MAXDevice_Num);		//系统设备数据初始化
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("设备 数据区初始化完成......\r\n");
	}
	else
	{
		cli_printf("设备 数据区初始化失败......\r\n");
	}
}



void sysdataresetall(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysPara_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("系统 参数区初始化完成......\r\n");
	}
	else
	{
		cli_printf("系统 参数区初始化失败......\r\n");
	}

	TESTvAL =SysUserList_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("用户 参数区初始化完成......\r\n");		
	}
	else
	{
		cli_printf("用户 参数区初始化失败......\r\n");
	}

	TESTvAL =SysDeviceList_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("设备 参数区初始化完成......\r\n");
	}
	else
	{
		cli_printf("设备 参数区初始化失败......\r\n");
	}

	TESTvAL =UserData_ResetALL(MAXUser_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("用户 数据区初始化完成......\r\n");
	}
	else
	{
		cli_printf("用户 数据区初始化失败......\r\n");
	}	

	TESTvAL =SysDevData_ResetALL(MAXDevice_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("设备 数据区初始化完成......\r\n");
	}
	else
	{
		cli_printf("设备 数据区初始化失败......\r\n");
	}


}



int updatetime(char **Parm)
{


	RealClock_Str Time;
	Time.Year =atoi(Parm[1]);
	Time.Month=atoi(Parm[2]);
	Time.Day=atoi(Parm[3]);
	Time.Hour=atoi(Parm[4]);
	Time.Minute=atoi(Parm[5]);
	Time.Second=atoi(Parm[6]);
	Time.Week=atoi(Parm[7]);

	/* 更新服务器地址 */
	if(PCF8563_Set(&Time) ==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void settime(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* 判断参数数量是否合法 */
	if(argc != 8)
	{
		cmd_printf("Set systemtime YYYY MM DD HH MM SS W");
		return;
	}
  
	/* 设置系统时间*/
	if (0 != updatetime(argv))
	{
		cmd_printf("Set system time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");

	}
	else
	{
		cmd_printf("Set system time success...");
	}
}


int updatetimes(char **Parm)
{


	SysPara.StartTime.Year =atoi(Parm[1]);
	SysPara.StartTime.Month=atoi(Parm[2]);
	SysPara.StartTime.Day=atoi(Parm[3]);
	SysPara.StartTime.Hour=atoi(Parm[4]);
	SysPara.StartTime.Minute=atoi(Parm[5]);
	SysPara.StartTime.Second=atoi(Parm[6]);

	/* 更新服务器地址 */
	if(SysPara_Update()==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int updatetimef(char **Parm)
{

	
	SysPara.FinalTime.Year =atoi(Parm[1]);
	SysPara.FinalTime.Month=atoi(Parm[2]);
	SysPara.FinalTime.Day=atoi(Parm[3]);
	SysPara.FinalTime.Hour=atoi(Parm[4]);
	SysPara.FinalTime.Minute=atoi(Parm[5]);
	SysPara.FinalTime.Second=atoi(Parm[6]);

	/* 更新服务器地址 */
	if(SysPara_Update()==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




void settime_s(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* 判断参数数量是否合法 */
	if(argc != 7)
	{
		cmd_printf("Set start time YYYY MM DD HH MM SS");
		return;
	}
  
	/* 设置时间*/
	if (0 != updatetimes(argv))
	{
		cmd_printf("Set start time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");

	}
	else
	{
		cmd_printf("Set start time success...");
	}
}
void settime_f(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* 判断参数数量是否合法 */
	if(argc != 7)
	{
		cmd_printf("Set final time YYYY MM DD HH MM SS");
		return;
	}
  
	/* 设置时间*/
	if (0 != updatetimef(argv))
	{
		cmd_printf("Set final time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");
	}
	else
	{
		cmd_printf("Set final time success...");
	}
}


void setsystype(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U Type =0;
	
	if(argc != 2)		//判断输入参数的合法性
	{
		cmd_printf("systype [X] \r\n");
		return;
	}
	Type =atoi(argv[1]);
	/*判断值的合法性 并进行保存 */
	if((Type ==0)||(Type>3))		
	{
		cmd_printf("systype [X] \r\n");
		cmd_printf("The System type num is error Please once again.. \r\n");
		cmd_printf("The System type num is [1]/[2]/[3] \r\n");
	}
	/*有效输入值*/
	else						
	{

		SysPara.DeviceType =Type;
		if(SysPara_Update() ==HAL_OK)
		{
			cmd_printf("The System type is Seting OK ..  System Type NUM: %d\r\n",SysPara.DeviceType);
			switch(SysPara.DeviceType)
			{
				case Type_Meter:
				{
					cli_printf("   系统类型:  %d    热量表 采集系统\r\n",Type);	
				}break;

				case Type_MeterValve:
				{
					cli_printf("   系统类型:  %d    温控计量一体化 计量系统\r\n",Type);	
				}break;	

				case Type_Valve:
				{
					cli_printf("   系统类型:  %d    通断时间面积法 计量系统\r\n",Type);	

				}break;

				default :
				{
					cli_printf("   系统类型:  %d    未设置\r\n",Type);

				}break;
			}
			
			
		}
	}
	
}


void Updatedebug(INT32U enable, INT32U level)
{
	SysPara.DebugEnable =enable;
	SysPara.DebugLevel =level;
	SysPara_Update();
}







/*


*/
void devchange(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U DevNum =0;
	INT32U DevID =0;
	INT32U DevID1 =0;
	INT32U DevID2 =0;
	
	if(argc != 3)		//判断输入参数的合法性
	{
		cmd_printf("devchange [X] [Y]\r\n");
		return;
	}
	DevID = atoi(argv[1]);
	DevID1 = HexToBcd4(&DevID);
	if(Getdevice_Num(DevID1,&DevNum) ==HAL_OK)
	{
		DevID = atoi(argv[2]);
		DevID2 = HexToBcd4(&DevID);

		SysDeviceList.Device[DevNum].ID =DevID2;
		if(SysDeviceList_Update() ==HAL_OK)
		{
			cmd_printf("数据更新成功...\r\n");

		}
		else
		{
			cmd_printf("数据更新失败...\r\n");
		}
	}
	else
	{
		cmd_printf("数据查询失败...\r\n");
	}
	
	

}


void changeDeviceNum(INT16U num)
{
	if( num >= MAXDevice_Num)
	{
		os_printf("Device num is too big...\r\n");
		return;
	}
	ClientReadCtrler.Num = num;
	os_printf("Device num change to %u\r\n",num);
}

	



/*


*/
void setsn(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U DevSN =0;
	INT32U DevSN1 =0;

	
	if(argc != 2)		//判断输入参数的合法性
	{
		cmd_printf("setsn [12345678]\r\n");
		return;
	}
	DevSN  = atoi(argv[1]);
	DevSN1 = HexToBcd4(&DevSN);
	SysPara.Device_SN =DevSN1;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("设备编号设置成功...\r\n");
		cli_printf("设备编号:       %08X \r\n",SysPara.Device_SN);
	}
	else
	{
		cmd_printf("设备编号设置失败...\r\n");
	}
	
	

}






	



/*

设置终端读取间隔
*/
void setread(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Num =0;

	if(argc != 3)		//判断输入参数的合法性
	{
		cmd_printf("setread [Repeat space] [Loop space]\r\n");
		return;
	}
	Num  = atoi(argv[1]);
	if(( Num<2000)||(Num>1000*60*10))
	{
		cmd_printf("setread [Repeat space] 2000<->600000 ms\r\n");
		return;
	}
	SysPara.ReadSpace =Num;
	
	Num  = atoi(argv[2]);
	if(( Num<2000)||(Num>1000*60*10))
	{
		cmd_printf("setread [Loop space] 2000<->600000 ms\r\n");
		return;
	}
	SysPara.LoopSpace =Num;
	
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("终端读取间隔设置成功...\r\n");
		cli_printf("重复间隔:       %lu ms \r\n",SysPara.ReadSpace);
		cli_printf("循环间隔:       %lu ms \r\n",SysPara.LoopSpace);
	}
	else
	{
		cmd_printf("设置失败...\r\n");
	}
}









	



/*

设置终端上报模式 及间隔
*/
void setsend(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Mode =0;
	INT32U Num =0;

	if(argc != 3)		//判断输入参数的合法性
	{
		cmd_printf("setsend [ModeID] [XXXXX]\r\n");
		return;
	}

	

	Mode  = atoi(argv[1]);
	{
		if(Mode >2)
		{
			cmd_printf("ModeID  0:无效 1:Auto 2:Loop \r\n");
			return;
		}

	}
	Num  = atoi(argv[2]);
	if(( Num<5000)||(Num>1000*60*10))
	{
		cmd_printf("setsend [5000]<->[600000] ms\r\n");
		return;
	}

	SysPara.SendMode =Mode;
	SysPara.SendSpace =Num;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("终端上报间隔设置成功...\r\n");
		cli_printf("上报模式:       %lu\r\n",SysPara.SendMode);
		cli_printf("上报间隔:       %lu ms \r\n",SysPara.SendSpace);
	}
	else
	{
		cmd_printf("设置失败...\r\n");
	}
}










	



/*

设置系统的分摊间隔
*/
void setshare(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Num =0;

	if(argc != 2)		//判断输入参数的合法性
	{
		cmd_printf("setshare [XXXXX]\r\n");
		return;
	}
	Num  = atoi(argv[1]);
	if(( Num<10)||(Num>60*12))
	{
		cmd_printf("ShareSpace [10]<->[720] Minutes\r\n");
		return;
	}
	SysPara.Apportion_T =Num;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("分摊周期设置成功...\r\n");
		cli_printf("分摊周期:       %lu Minutes \r\n",SysPara.Apportion_T);
	}
	else
	{
		cmd_printf("设置失败...\r\n");
	}
}



void powrelayctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
    
    
	INT16U CMD=0;
    CMD =CMD;
	if(argc != 2)		//判断输入参数的合法性
	{
		cmd_printf("relay [X] X=on/off\r\n");
		return;
	}


#if (USE_POWRELAY==0) //判断项目是否启用了远程断送电功能   
	cmd_printf("该项目未添加该功能...\r\n");
	return;
#endif
    
#if (USE_POWRELAY==1) //判断项目是否启用了远程断送电功能       
	if (!strcasecmp(argv[1], "on")) 
	{
		CMD =0X0A0A;
		
	} 
	else if (!strcasecmp(argv[1], "off")) 
	{
		CMD =0XA0A0;
	}
	
	if(SysPara.RelayRecord !=CMD)
	{
		SysPara.RelayRecord =CMD;
		PowerRelay_SET(CMD);			//主回路继电器动作控制
		if( SysPara_Update()==HAL_OK)
		{			
			cmd_printf("手动操作成功，设备参数记录成功...\r\n");
		}
	}
#endif

}










void ddf2ctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

    INT32U DevID =0;
    INT32U DevID1 =0;
    INT32U flag =0;
    INT16U DevNum =0;
    ClientCH1_Queue_Stru SendBuffer_DDF2;
    

    if(argc != 3)       //判断输入参数的合法性
    {
        cmd_printf("ddf2ctrl [12345678] [0/1]\r\n");
        return;
    }
    DevID = atoi(argv[1]);
    DevID1 = HexToBcd4(&DevID);

    flag =atoi(argv[2]);
    if(GetMeters_Num(DevID1,Meter_DDF2 ,&DevNum) ==HAL_OK) //成功找到用户设备
    {
        if(0==flag)
        {
            dbg_printf(DEBUG_INFO,"手动控制 开启 %08X",DevID1);//MBUS端口数据发送
            SendBuffer_DDF2.Device.Num=SysDeviceList.Device[DevNum].Num;
            SendBuffer_DDF2.Device.Type=SysDeviceList.Device[DevNum].Type;
            SendBuffer_DDF2.Device.ID=SysDeviceList.Device[DevNum].ID;
            SendBuffer_DDF2.Device.COM_Type=SysDeviceList.Device[DevNum].COM_Type;
            SendBuffer_DDF2.SignleCom =SET;
            SendBuffer_DDF2.UaComFlg =0XAAAA;                               //传递命回复记录
            SendBuffer_DDF2.Uapack=0X0D;
            SendBuffer_DDF2.SendData.DDF2Data.Pack_03.OUT =0X55;   
            DDF2_Send_Code_QInput(&SendBuffer_DDF2,0x03);
            dbg_printf(DEBUG_INFO,"设备开启...");
        }
        else
        {
            dbg_printf(DEBUG_INFO,"手动控制  关闭 %08X",DevID1);
            SendBuffer_DDF2.Device.Num=SysDeviceList.Device[DevNum].Num;
            SendBuffer_DDF2.Device.Type=SysDeviceList.Device[DevNum].Type;
            SendBuffer_DDF2.Device.ID=SysDeviceList.Device[DevNum].ID;
            SendBuffer_DDF2.Device.COM_Type=SysDeviceList.Device[DevNum].COM_Type;
            SendBuffer_DDF2.SignleCom =SET;
            SendBuffer_DDF2.UaComFlg =0XAAAA;                               //传递命回复记录
            SendBuffer_DDF2.Uapack=0X0D;
            SendBuffer_DDF2.SendData.DDF2Data.Pack_03.OUT =0XBB; 
            
            DDF2_Send_Code_QInput(&SendBuffer_DDF2,0x03);
            dbg_printf(DEBUG_INFO,"设备关闭...");

        }
    }
    else
    {

        dbg_printf(DEBUG_INFO,"设备查询失败...");

    }

}






void ClirateSet(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

    INT32U rate =0;

    if(argc != 2)       //判断输入参数的合法性
    {
        dbg_printf(DEBUG_INFO,"clirate [xxxxxxxx]");
        return;
    }
    rate = atoi(argv[1]);


    if((rate <1200)||(rate >921600))
    {

        dbg_printf(DEBUG_INFO,"clirate Set the value error  1200<= x <= 921600");
        return;
    }

    dbg_printf(DEBUG_INFO,"clirate The rate value set success :  %d\r\n",rate);
    
    dbg_printf(DEBUG_INFO,"Please reset the serial communication rate and turn it back on..");
    dbg_printf(DEBUG_INFO,"If you want to restore the default settings[115200], please restart the device again.\r\n");
    dbg_printf(DEBUG_INFO,"THANK YOU, GOOD LUCK\r\n");


//    HAL_UART1_MspDeInit(&huart1);
    
    HAL_Delay(2500);
    
    huart1.Init.BaudRate =rate;		
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Parity =UART_PARITY_NONE;		
    MX_USART1_UART_Init();  //通用异步端口1初始化

    



}










 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
