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
* @brief :该文件用于管理采集器所辖通信设备的参数/状态数据
* 
* 
* 
*
* @author :许伟
* @date :2017/8/29 14:52
***************************************************************
*/ 
#define _DEVPARA_C_
#include "DevPara.h"
#include "main.h"



/*
	系统设备列表初始化
	用于系统上电后从Flash更新到内存区域
*/
HAL_StatusTypeDef SysDeviceList_Init(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = ReadData_SPIFlash(SysDeviceList_Addr,(INT8U*)&SysDeviceList,sizeof(SysDeviceList_Stru));
	for( INT16U i=0;i<MAXDevice_Num;i++)
	{
		SysDeviceList.Device[i].Num =i;
	}
	return Errstate;
}
 



 /*
	系统设备列表更新
	用于当系统参数发生变化后 将内存数据更新至存储器
*/
HAL_StatusTypeDef SysDeviceList_Update(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = WriteData_SPIFlash(SysDeviceList_Addr,(INT8U*)&SysDeviceList,sizeof(SysDeviceList_Stru));
	return Errstate;
}



 /*
	系统设备列表默认设置
	将系统参数回复默认设置，并且更新至存储器
*/
HAL_StatusTypeDef SysDeviceList_Reset(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	for( INT16U i=0;i<MAXDevice_Num;i++)
	{
		SysDeviceList.Device[i].Num =i;
		SysDeviceList.Device[i].Type =DEFUNULL;
		SysDeviceList.Device[i].ID=0;
		SysDeviceList.Device[i].UserNum=0X00;
		SysDeviceList.Device[i].UserKEY=0;
		SysDeviceList.Device[i].COM_Type=0;
		

	}
	Errstate = SysDeviceList_Update();
	return Errstate;
	
}










/*

函数功能:从存储器读取单一设备数据
*/
HAL_StatusTypeDef SysDevData_Read(INT16U ListNum,SysDevData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U Mem_Addr =ListNum*(sizeof(SysDevData_Stru))+DevData_Addr;   //存储器地址运算
	INT16U Data_Size =sizeof(SysDevData_Stru);//设备数据传递
	SysDevData_Stru Data;
	
	if(ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(ReadData_FRAM(Mem_Addr,(INT8U*)&Data,Data_Size) ==0)
	{
		memcpy((INT8U*)Value,  (INT8U*)&Data,Data_Size);//将参数数据传递给参数指针
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;

}



/*
函数功能:向存储器写入单一用户的数据

*/

HAL_StatusTypeDef SysDevData_Update(INT16U ListNum,SysDevData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//错误标志声明
	INT16U Mem_Addr =ListNum*(sizeof(SysDevData_Stru))+DevData_Addr;   //存储器地址运算
	INT16U Data_Size =sizeof(SysDevData_Stru);//用户参数数据传递

	if(ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(WriteData_FRAM(Mem_Addr, (INT8U*)Value, Data_Size)==0)//写入参数数据
	{
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;
}


/*

	函数功能将内存数据更新到存储器 
	在更新之前请保证内存数据的正确
*/

HAL_StatusTypeDef SysDevData_Save(INT16U ListNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//错误标志声明

	SysDevData_Stru UserPara_WriteBuf;
	if (ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	UserPara_WriteBuf =SysDevData[ListNum];
	ErrFlg =SysDevData_Update( ListNum,&UserPara_WriteBuf);
	return ErrFlg;
}



/*
函数名称:UserDara_InitALL(INT16U UserNum)
函数功能:对系统参数进行上电初始化 (从存储器的指定位置读取参数,并将数据填充入设备数据)
参数:空
返回值:  正常0X00;其他值  异常
*/

HAL_StatusTypeDef SysDevData_InitALL(INT16U Num)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U i =0;	//循环控制变量
	SysDevData_Stru UserDataB;

	if (Num>MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}

	for (i =0; i<Num;i++)
	{
		ErrFlg=SysDevData_Read(i,&UserDataB);
		if (ErrFlg ==HAL_OK )
		{
			SysDevData[i] =UserDataB;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			break;
		}
	}
	return ErrFlg;
	
}




/*
函数功能:将用户数据回复出厂设置
*/

HAL_StatusTypeDef SysDevData_ResetALL(INT16U DevNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	Dev1Data_Stru DataBuffer1;
	Dev2Data_Stru DataBuffer2;
	Dev3Data_Stru DataBuffer3;
	Dev4Data_Stru DataBuffer4;
    
#ifdef Meter_H_ENABLE
	Dev5Data_Stru DataBuffer5;
#endif
#ifdef Valve_NWK_ENABLE
	Dev11Data_Stru DataBuffer11;
#endif
	SysDevData_Stru DevData;
	INT16U i =0;

	//设备类型1
	DataBuffer1.Input_Temp=0;
	DataBuffer1.Output_Temp=0;
	DataBuffer1.Instant_Current =0;
	DataBuffer1.Instant_Current_Unit =m3PreH;
	DataBuffer1.Instant_Energy =0;
	DataBuffer1.Instant_Energy_Unit =MW;
	DataBuffer1.Total_Current =0;
	DataBuffer1.Total_Current_Unit =m3;
	DataBuffer1.Total_Code =0;
	DataBuffer1.Total_Code_Unit =MW_h;
	DataBuffer1.Total_Energy =0;
	DataBuffer1.Total_Energy_Unit =MW_h;
	DataBuffer1.CycBot_Energy =0;		//周期表底，用于记录周期开始时的热量值
	DataBuffer1.Apportion_Energy =0;		//分摊热量(供暖季内的分摊热量)

	DataBuffer1.Work_Time =0;
	DataBuffer1.STATE1 =0;
	DataBuffer1.STATE2 =0;



	//设备类型2
	DataBuffer2.Input_Temp=0;
	DataBuffer2.Output_Temp=0;
	DataBuffer2.Instant_Current =0;
	DataBuffer2.Instant_Current_Unit =m3PreH;
	DataBuffer2.Instant_Energy =0;
	DataBuffer2.Instant_Energy_Unit =MW;
	DataBuffer2.Total_Current =0;
	DataBuffer2.Total_Current_Unit =m3;
	DataBuffer2.Total_Code =0;
	DataBuffer2.Total_Code_Unit =MW_h;
	DataBuffer2.Total_Energy =0;
	DataBuffer2.Total_Energy_Unit =MW_h;
	DataBuffer2.Work_Time =0;
	DataBuffer2.STATE1 =0;			//热表故障状态 =0;	
	DataBuffer2.STATE2 =0;			//热表故障状态 =0;	


	//设备类型3
	DataBuffer3.Set_TCtrlFg =TCFlag_OFF;
	DataBuffer3.Set_Temp =2000;
	
	DataBuffer3.LimtTE_Flag =TCFlag_OFF;
	DataBuffer3.LimtTE_Value =3000;
	
	DataBuffer3.ControlType =0X00;
	DataBuffer3.ForceCtrlFlg =Force_Nor;
	DataBuffer3.Cur_Temp =0;
	DataBuffer3.Ave_Temp =0;
	DataBuffer3.Input_Temp =0;
	DataBuffer3.Output_Temp =0;
	DataBuffer3.ValvePosition =Valve_Close;
	DataBuffer3.Cycle_OpTim =0;
	DataBuffer3.Cycle_OpRat =0;
	DataBuffer3.Apportion_Energy =0;	//分摊热量
	DataBuffer3.Face_State =0;
	DataBuffer3.Valve_State =0;





	//设备类型4
	DataBuffer4.ControlType =0;
	DataBuffer4.ForceCtrlFlg =Force_Nor;
	DataBuffer4.ValvePosition =Valve_Open;
	DataBuffer4.Cycle_OpTim =0;
	DataBuffer4.Cycle_OpRat =0;
	DataBuffer4.Apportion_Energy =0;	//分摊热量
	DataBuffer4.Valve_State =0;

#ifdef Meter_H_ENABLE
	//设备类型5
	DataBuffer5.Input_Temp=0;
	DataBuffer5.Output_Temp=0;
	DataBuffer5.Instant_Current =0;
	DataBuffer5.Instant_Current_Unit =m3PreH;
	DataBuffer5.Instant_Energy =0;
	DataBuffer5.Instant_Energy_Unit =MW;
	DataBuffer5.Total_Current =0;
	DataBuffer5.Total_Current_Unit =m3;
	DataBuffer5.Total_Code =0;
	DataBuffer5.Total_Code_Unit =MW_h;
	DataBuffer5.Total_Energy =0;
	DataBuffer5.Total_Energy_Unit =MW_h;
	DataBuffer5.CycBot_Energy=0;			//周期表底，用于记录周期开始时的热量值
	DataBuffer5.Apportion_Energy=0;		    //周期内分摊热量   当前表底-周期表底
	DataBuffer5.Work_Time =0;
	DataBuffer5.STATE1 =0;
	DataBuffer5.STATE2 =0;
#endif

#ifdef Meter_H_ENABLE
	//设备类型11
	DataBuffer11.Input_Temp             = 0;    //进水温度
	DataBuffer11.Output_Temp            = 0;    //回水温度
	DataBuffer11.EnterWater_Pressure    = 0;    //进水压力
	DataBuffer11.ReturnWater_Pressure   = 0;    //回水压力
	DataBuffer11.Room_Temp              = 0;    //室温
	DataBuffer11.Current_Valve_Open     = 0;    //当前阀门开度值
	DataBuffer11.SetValue_Open          = 0;    //设置阀门开度值
	DataBuffer11.Temp_Diff              = 0;    //温差设定值
	DataBuffer11.ReturnTemp_Set         = 0;    //回水温度设定值
	DataBuffer11.PressureDiff_Set       = 0;    //压差设定值
	DataBuffer11.Error                  = 0;    //错误代码 0为正常，1为堵转，2为进水温度传感器开路，3.回水温度传感器开路，4.进水压力传感器开路，5回水压力传感器开路
	DataBuffer11.Software_Version       = 0;    //软件版本号  100 则为 V1.0 
	DataBuffer11.Run_Mode               = 0;    //运行模式  0为开度模式；1为温差模式2为回温模式3为压差模式4.就地控制模式（电机掉电）5.4-20控制开度模式（需硬件支持）6 TIME
	DataBuffer11.Address                = 0;    //地址 1-247，默认为1
	DataBuffer11.Motor_Steering         = 0;    //电机转向 0为正向阀，1为反向阀
	DataBuffer11.Adjust_Switch          = 0;    //自动行程校正开关，0关闭，1为打开，值为1时每次上电自动校正行程
	DataBuffer11.Adjust_Tigger          = 0;    //写0x5555触发一次
    DataBuffer11.Dc_Motor_Speed         = 0;    //直流电机速度
#endif

	for(i =0; i<DevNum;i++)
	{
        SysDEV_Type DEVT =SysDeviceList.Device[i].Type;
        switch(DEVT)
        {
            case Meter_B:
            {
				DevData.Device1 =SysDevData[i].Device1 =DataBuffer1;
				ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            case Meter_U:
            {
                 DevData.Device2=SysDevData[i].Device2 =DataBuffer2;
                 ErrFlg=SysDevData_Update(i,&DevData);
            } break; 
            case Valve_U:
            {
                DevData.Device3=SysDevData[i].Device3 =DataBuffer3;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            
            case Valve_UH:
#ifdef Meter_DDF2_ENABLE            
            case Meter_DDF2:
#endif            
            {
                DevData.Device4=SysDevData[i].Device4 =DataBuffer4;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            
#ifdef Meter_H_ENABLE
            case Meter_H:
            {
                DevData.Device5=SysDevData[i].Device5 =DataBuffer5;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
#endif	
            
#ifdef Valve_NWK_ENABLE //NWK 耐威科楼栋单元调节阀modbus协议
            case Valve_NWK:
            {
                DevData.Device11=SysDevData[i].Device11 =DataBuffer11;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
#endif		
            default :
            {
                DevData.Device2=SysDevData[i].Device2 =DataBuffer2;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;

        }
		if ( ErrFlg==HAL_OK)
		{
			continue;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			return ErrFlg;
		}
	}
	return ErrFlg;
	
}







/*
	
获取栋表信息
	重建栋表信息表

*/
HAL_StatusTypeDef GetbuildMeterMessage(void)
{
	HAL_StatusTypeDef ErrState =HAL_OK;
	
    INT16U 	Num =0;	
	INT32U	ID =0;		


	INT16U 	Meters =0;
	

	for( INT16U i=0;i<MAXBuldMeter_Num;i++)		//遍历设备之栋表参数表 获取栋表的ID和下标
	{
		if(
            (SysDeviceList.Device[i].Type ==Meter_B)
#ifdef Meter_H_ENABLE
        ||(SysDeviceList.Device[i].Type ==Meter_H)
#endif
        
        )	//判断设备类型
		{
			Num =i;
			ID =SysDeviceList.Device[i].ID;		//设备编号传递
			
			BuildMeters[Meters].ID =ID;
			BuildMeters[Meters].Num =Num;
			
			Meters +=1;
			if(Meters >MAXBuldMeter_Num)
			{
				ErrState =HAL_ERROR;
				return ErrState;
			}
		}
	}

	for(INT16U A=0;A<MAXBuldMeter_Num;A++ )	//对所用栋表进行遍历 并对其所辖用户数量清零
	{
		BuildMeters[A].Users=0;
	}
	
	for( INT16U i=0;i<MAXUser_Num;i++)					//遍历整个用户参数表 查询所属
	{
		for(INT16U A=0;A<SysPara.BuldMeterNum;A++ )		//遍历栋表数据表
		{
			if( SysUserList.User[i].BuildMeter_ID ==BuildMeters[A].ID)
			{
				BuildMeters[A].Users +=1;
			}
		}	
	}
	ErrState =HAL_OK;
	return ErrState;
}










/*
	
	获取系统实际用户数量
*/
void GetSystemUserNum(void)
{
	INT16U UserNum =0;

	for( INT16U L=0;L<MAXUser_Num;L++)		//遍历用户List
	{
		if(SysUserList.User[L].User_ID !=0)
		{
			UserNum +=1;
		}
	}
	SysPara.UserNum =UserNum;			//用户数量传递
}



/*
	
	获取系统实际设备数量

	运行该函数 会更新 栋表数量  用户设备数量  系统设备总数量
*/
void GetSystemDevMessage(void)
{

	INT16U DeviceNum =0;
	for( INT16U L=0;L<MAXDevice_Num;L++)		//遍历设备List
	{
		if(SysDeviceList.Device[L].UserKEY !=0)
		{
			DeviceNum +=1;
		}
	}
	SysPara.DevNum =DeviceNum;				//用户设备数量传递


	DeviceNum =0;
	for( INT16U i=0;i<MAXBuldMeter_Num;i++)		//遍历设备之栋表参数表 获取栋表的ID和下标
	{
		if(
            (SysDeviceList.Device[i].Type ==Meter_B)
#ifdef Meter_H_ENABLE
        ||(SysDeviceList.Device[i].Type ==Meter_H)
#endif
        )	//判断设备类型
		{
			DeviceNum +=1;
		}
	}
	SysPara.BuldMeterNum =DeviceNum;			//楼栋表数量
	
	SysPara.DevNum_T =SysPara.BuldMeterNum +SysPara.DevNum;	//系统设备总数量计算
}




/*
	根据设备ID 获取设备的下标
*/
HAL_StatusTypeDef GetMeters_Num_Build(INT32U ID,SysDEV_Type Type,INT16U* Num)
{
	for( INT16U A=0;A<MAXBuldMeter_Num;A++)
	{
		if(SysDeviceList.Device[A].Type ==Type)
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}







/*
	根据设备ID 获取设备的下标
*/
HAL_StatusTypeDef GetMeters_Num(INT32U ID,SysDEV_Type Type,INT16U* Num)
{
	for( INT16U A=0;A<MAXDevice_Num;A++)
	{
		if(SysDeviceList.Device[A].Type ==Type)
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}




/*
	根据设备ID 获取设备的下标
*/
HAL_StatusTypeDef Getdevice_Num(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXDevice_Num;A++)
	{
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}




/*
	根据用户的ID获取第一个匹配设备 在设备列表里边
*/
HAL_StatusTypeDef GetMeters_Num_FromUserID(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXUser_Num;A++)
	{
		if(SysDeviceList.Device[A].UserKEY ==ID)
		{
			*Num =A;
			return HAL_OK;
		}
	}
	return HAL_ERROR;
}



void UpDateSysDevStatusErr(void)
{
	INT8U Type=0;
	for(INT16U i =0;i<MAXDevice_Num;i++)
	{
		Type =SysDeviceList.Device[i].Type;
		switch(Type)
		{
			case Meter_B :	//大口径热量表 丰源协议188
			{
				if( SysDevStatus[i].Device1.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;

			case Meter_U://户用热量表 丰源协议188
			{
				if( SysDevStatus[i].Device2.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;		

			case Valve_U://通断控制器 FY2000
			{
				if( SysDevStatus[i].Device3.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;	

			case Valve_UH://回水通断控制器 FY2000
			{
				if( SysDevStatus[i].Device4.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;			
#ifdef Meter_H_ENABLE
			case Meter_H://大口径热量表 汇中188
			{
				if( SysDevStatus[i].Device5.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
#ifdef  Meter_XY_ENABLE	
			case Meter_XY://小口径热量表 XY-188
			{
				if( SysDevStatus[i].Device6.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
#ifdef  Valve_NWK_ENABLE	
			case Valve_NWK://NWK耐威科modbus协议
			{
				if( SysDevStatus[i].Device11.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
			default :break;
		}

	}
}




/*
	获取系统设备通信状态 总报警标志
*/
HAL_StatusTypeDef GetDev_ComStatus(void)
{
	for(INT16U loop =0;loop<MAXDevice_Num;loop++)
	{
		if(SysDevStatusErr[loop] !=0X00)
		{
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}


 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
