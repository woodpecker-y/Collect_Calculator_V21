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
* @brief :该文件用于FY-2000系列产品的主机侧通信协议
* 
* 
* 
*
* @author :许伟
* @date :2017/9/5 16:30
***************************************************************
*/ 
#define _FY2000PRO_C_
#include "FY2000Pro.h"
#include "main.h"


UART_TO_FY2000_QueueSend_Stru FY2000_Q_RX_Buffer;		//通信发送队列 接收缓冲器
UART_TO_FY2000_QueueSend_Stru* FY2000_Q_RX_BufferP;	//通信发送队列 接收缓冲器



/*
函数名称:FY2000_Pack_RxServer_S
函数功能:协议预处理包，描述  将接收队列缓冲器的数据进行解析并进入解析包
*/

void FY2000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//有效数据区边界
	FY2000_Pack_Uni* FY2000_RXPack =(FY2000_Pack_Uni*)(Ctrl_Point->InputPack);
	while (Ctrl_Point->Rx_Rear !=Ctrl_Point->Rx_Front) 
	{
	
		Bufer=Ctrl_Point->InputBuffer[Ctrl_Point->Rx_Rear]; //从接收缓冲区读取一个字节的数据
		
		if (*(Ctrl_Point->Ticks)- Ctrl_Point->RecPackTimeOut > Ctrl_Point->TimeOut)//帧间隔没有收到新的数据，即将接收下一帧完整数据
		{
			Ctrl_Point->RecPackState=0; //清除正在处理接收包数据标志
			Ctrl_Point->RecPackPoint=0; //包指针
		}		
		switch(Ctrl_Point->RecPackState)
		{
			case 0: //接收起始码
			{
				if (Bufer == FY2000Pro_StartCode) 
				{ 
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
					Ctrl_Point->RecPackState=1; 					//开始接收数据包
					DataBdry =0;
					
				}
			}break;
			
			case 1: //接收协议类型
			{		
				if ( Bufer == FY2000Pro_ProtocolCode)
				{

					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
					Ctrl_Point->RecPackState=2;//开始接收数据包 
				}
			}break;
			
			case 2://接收SN 第1字节
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=3;//开始接收数据包 
						
			}break;
			
			case 3://接收SN 第2字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=4;//开始接收数据包 


			}break;
	
			case 4: //接收SN 第3字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=5;//开始接收数据包 

			}break;
			case 5: //接收SN 第4字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=6;//开始接收数据包 

			}break; 		

			case 6: //接收DESN第1字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=7;//开始接收数据包 

					
			}break; 
			
			case 7://接收DESN第2字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=8;//开始接收数据包 			
			}break;
			
			case 8://接收GN第1字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=9;//开始接收数据包 	


			}break;

			case 9://接收GN第2字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=10;//开始接收数据包 	


			}break;			

			case 10://接收ConType
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=11;//开始接收数据包	
				
			}break;

			case 11:	//数据长度
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零

				if(FY2000_RXPack->DefaultPack.Lenth )	//判断数据内容是否存在
				{
					Ctrl_Point->RecPackState=12;			//开始接收数据包
				}
				else
				{
					Ctrl_Point->RecPackState=13;			//开始接收数据包
				}
				DataBdry =FY2000_RXPack->DefaultPack.Lenth;
			}break;
		
			case 12:	//有效数据区
			{		


				
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
				Ctrl_Point->RecPackState=12;					//开始接收数据包

				DataBdry -=1;
				if(DataBdry ==0)
			//	if ( (FY2000_RXPack->DefaultPack.Lenth + FY2000Pro_HeadSize)==Ctrl_Point->RecPackPoint)
				{
					Ctrl_Point->RecPackState=13;
				}


				
			}break;

			case 13:	//校验和
			{
				
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
				Ctrl_Point->RecPackState=14;					//开始接收数据包
				
			}break;
			
			case 14:	//结束标志
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackState=0; 
				
				if (Bufer ==FY2000Pro_EndCode)
				{
					FY2000_Pack_RxAnalyze_S(Ctrl_Point,FY2000_RXPack->DefaultPack.Lenth+FY2000Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
			}break; 
			
			default:	//错误状态,恢复状态为0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_FY2000BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}
/* 无操作系统环境下使用   ，操作系统环境下建议 创建单独任务 		*/
//	FY2000_Pack_TxServer_S(Ctrl_Point);		//打包服务函数
}



 
/*

函数名称:void  RXPack_AnalyzeForyonV10(INT8U PortNum,INT16U DataNum)
函数功能:通信解析并处理子函数
*/
INT8U FY2000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
{
	INT8U CheckFlg =0;	//错误标志
	INT16U ProtoNO =0;	//协议编号
	FY2000_Pack_Uni* Packin =(FY2000_Pack_Uni*)Ctrl_Point->InputPack;	//指针变换
	
	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//校验错误，退出函数
	{
		return	CheckFlg;
	}
	else
	{
		ProtoNO =Packin->DefaultPack.ConType;//传递协议编码
		CheckFlg =FY2000_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}




/*
50组包子函数
*/
void FY2000_Pack_50(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT8U PackSize =0;
	
	PackData->Pack_50.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_50.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_50.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_50.Head.DESN =0;
	PackData->Pack_50.Head.GN =0;
	PackData->Pack_50.Head.ConType =50;

	PackData->Pack_50.Head.Lenth =sizeof(FY2000_Pack50_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack50_Stru)-2;	//校验数据长度计算

	if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	{
		PackData->Pack_50.Year =RTC_Time.Year;
		PackData->Pack_50.Month =RTC_Time.Month;
		PackData->Pack_50.Day =RTC_Time.Day;
		PackData->Pack_50.Hour =RTC_Time.Hour;
		PackData->Pack_50.Minute =RTC_Time.Minute;
		PackData->Pack_50.Second =RTC_Time.Second;
		PackData->Pack_50.Week =RTC_Time.Week;
		
		PackData->Pack_50.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_50.End =FY2000Pro_EndCode;
		
		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE;
	}
}



/*
51组包子函数
*/
void FY2000_Pack_51(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;

	PackData->Pack_51.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_51.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_51.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_51.Head.DESN =0;
	PackData->Pack_51.Head.GN =0;
	PackData->Pack_51.Head.ConType =51;
	
	PackData->Pack_51.Head.Lenth =sizeof(FY2000_Pack51_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack51_Stru)-2; //校验数据长度计算


	PackData->Pack_51.Delay =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_51.Delay;	

	PackData->Pack_51.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_51.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;

}




/*
	52组包子函数
	主机发送全部关阀命令
*/
void FY2000_Pack_52(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;
	{

		PackData->Pack_52.Head.Start =FY2000Pro_StartCode;
		PackData->Pack_52.Head.Version =FY2000Pro_ProtocolCode;
		PackData->Pack_52.Head.SN =FY2000Pro_BroadcastAddr;
		PackData->Pack_52.Head.DESN =0;
		PackData->Pack_52.Head.GN =0;
		PackData->Pack_52.Head.ConType =52;
		PackData->Pack_52.Head.Lenth =2;
		
		PackData->Pack_52.Head.Lenth =sizeof(FY2000_Pack52_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
		PackSize =sizeof(FY2000_Pack52_Stru)-2; //校验数据长度计算

		PackData->Pack_52.Delay =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_52.Delay;

		PackData->Pack_52.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_52.End =FY2000Pro_EndCode;

		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE;	
	}
	
}






/*
53组包子函数
主机发送广播开关阀命令

*/
void FY2000_Pack_53(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;



	PackData->Pack_53.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_53.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_53.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_53.Head.DESN =0X0000;
	PackData->Pack_53.Head.GN =0X0000;
	PackData->Pack_53.Head.ConType =53;

	PackData->Pack_53.Head.Lenth =sizeof(FY2000_Pack53_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack53_Stru)-2; //校验数据长度计算

	PackData->Pack_53.ValveCtrlDemandFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_53.ValveCtrlDemandFlg;
	PackData->Pack_53.CtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_53.CtrlFlg;
	
	PackData->Pack_53.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_53.End =FY2000Pro_EndCode;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


	
}







/*
54组包子函数
主机发送开阀、关阀、强制锁定等动作命令


*/
void FY2000_Pack_54(UART_RBC_Stru* PORT)
{

	
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;

	PackData->Pack_54.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_54.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_54.Head.SN =FY2000_Q_RX_Buffer.ID;	
	PackData->Pack_54.Head.DESN =0;	
	PackData->Pack_54.Head.GN =0;
	PackData->Pack_54.Head.ConType =54;
	PackData->Pack_54.Head.Lenth =2;

	PackData->Pack_54.Head.Lenth =sizeof(FY2000_Pack54_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack54_Stru)-2; //校验数据长度计算

	PackData->Pack_54.ValveCtrlDemandFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_54.ValveCtrlDemandFlg;	
	PackData->Pack_54.CtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_54.CtrlFlg;	

	PackData->Pack_54.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_54.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 



}

 
 
 /*
 55组包子函数
 主机发送终端时间校准命令
 */
 void FY2000_Pack_55(UART_RBC_Stru* PORT)
 {
	 FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	 //指针变换
	 INT16U PackSize =0;


	 PackData->Pack_55.Head.Start =FY2000Pro_StartCode;
	 PackData->Pack_55.Head.Version =FY2000Pro_ProtocolCode;
	 PackData->Pack_55.Head.SN =FY2000_Q_RX_Buffer.ID;	
	 PackData->Pack_55.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_55.Head.DESN;	
	 PackData->Pack_55.Head.GN =0;
	 PackData->Pack_55.Head.ConType =55;

	 PackData->Pack_55.Head.Lenth =sizeof(FY2000_Pack55_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	 PackSize =sizeof(FY2000_Pack55_Stru)-2; //校验数据长度计算


	 if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	 {
		 PackData->Pack_55.Year =RTC_Time.Year;
		 PackData->Pack_55.Month =RTC_Time.Month;
		 PackData->Pack_55.Day =RTC_Time.Day;
		 PackData->Pack_55.Hour =RTC_Time.Hour;
		 PackData->Pack_55.Minute =RTC_Time.Minute;
		 PackData->Pack_55.Second =RTC_Time.Second;
		 PackData->Pack_55.Week =RTC_Time.Week;
		 
		 PackData->Pack_55.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		 PackData->Pack_55.End =FY2000Pro_EndCode;
		 
		 PackSize+=2;
		 PORT->OutputPackSize =PackSize;
		 PORT->PackSendFlag =ENABLE; 

	 }

 }






/*
59组包子函数
主机发送数据采集命令

*/
void FY2000_Pack_59(UART_RBC_Stru* PORT )
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;
	{
		
		PackData->Pack_59.Head.Start =FY2000Pro_StartCode;
		PackData->Pack_59.Head.Version =FY2000Pro_ProtocolCode;
		PackData->Pack_59.Head.SN =FY2000_Q_RX_Buffer.ID;	
		PackData->Pack_59.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Head.DESN;
		PackData->Pack_59.Head.GN =0;
		PackData->Pack_59.Head.ConType =59;

		PackData->Pack_59.Head.Lenth =sizeof(FY2000_Pack59_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
		PackSize =sizeof(FY2000_Pack59_Stru)-2; //校验数据长度计算

		
		PackData->Pack_59.DATA =0XAAAA;
		PackData->Pack_59.LoopTime =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LoopTime;
		
		PackData->Pack_59.Apportion_Energy =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Apportion_Energy;
		PackData->Pack_59.Remain_Heat =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Remain_Heat;
		PackData->Pack_59.Total_Heat =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Total_Heat;
		
		PackData->Pack_59.ControlType =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ControlType;

		if((FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg ==0X55)||(FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg ==0XAA))
		{
			PackData->Pack_59.ForceCtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg;
		}
		else
		{
			PackData->Pack_59.ForceCtrlFlg =0XFF;
		}

		if( FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg ==0XAA)
		{
			PackData->Pack_59.Set_TCtrlFg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg;
		}
		else
		{
			PackData->Pack_59.Set_TCtrlFg =0X00;
		}
		
		PackData->Pack_59.Set_Temp =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_Temp;


		if( FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag ==0XAA)
		{
			PackData->Pack_59.LimtTE_Flag =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag;
		}
		else
		{
			PackData->Pack_59.LimtTE_Flag =0XFF;
		}		
		PackData->Pack_59.LimtTE_Value =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Value;
		
		PackData->Pack_59.Year_S =SysPara.StartTime.Year;
		PackData->Pack_59.Month_S =SysPara.StartTime.Month;
		PackData->Pack_59.Day_S =SysPara.StartTime.Day;
		PackData->Pack_59.Hour_S =SysPara.StartTime.Hour;
		PackData->Pack_59.Minute_S =SysPara.StartTime.Minute;
		PackData->Pack_59.Second_S =SysPara.StartTime.Second;

		PackData->Pack_59.Year_F =SysPara.FinalTime.Year;
		PackData->Pack_59.Month_F =SysPara.FinalTime.Month;
		PackData->Pack_59.Day_F =SysPara.FinalTime.Day;
		PackData->Pack_59.Hour_F =SysPara.FinalTime.Hour;
		PackData->Pack_59.Minute_F =SysPara.FinalTime.Minute;
		PackData->Pack_59.Second_F =SysPara.FinalTime.Second;

		PackData->Pack_59.Buld =1;
		PackData->Pack_59.Unit=1;
		PackData->Pack_59.Floor=1;
		PackData->Pack_59.Cell=1;

		PackData->Pack_59.CellArea=10000;
		PackData->Pack_59.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_59.End =FY2000Pro_EndCode;
		
		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE; 
		
	}
	
}




/*
60组包子函数
主机发送终端通信测试命令
*/
void FY2000_Pack_60(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;



	PackData->Pack_60.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_60.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_60.Head.SN =FY2000_Q_RX_Buffer.ID;
	PackData->Pack_60.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_60.Head.DESN;
	PackData->Pack_60.Head.GN =0;
	PackData->Pack_60.Head.ConType =60;

	PackData->Pack_60.Head.Lenth =sizeof(FY2000_Pack60_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack60_Stru)-2; //校验数据长度计算


	if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	{
		PackData->Pack_60.Year =RTC_Time.Year;
		PackData->Pack_60.Month =RTC_Time.Month;
		PackData->Pack_60.Day =RTC_Time.Day;
		PackData->Pack_60.Hour =RTC_Time.Hour;
		PackData->Pack_60.Minute =RTC_Time.Minute;
		PackData->Pack_60.Second =RTC_Time.Second;
		PackData->Pack_60.Week =RTC_Time.Week;

		PackData->Pack_60.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_60.End =FY2000Pro_EndCode;

		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE; 
	}
}


/*
61组包子函数
主机广播发送供暖开始命令

*/
void FY2000_Pack_61(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;

	PackData->Pack_61.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_61.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_61.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_61.Head.DESN =0;
	PackData->Pack_61.Head.GN =0;
	PackData->Pack_61.Head.ConType =61;

	PackData->Pack_61.Head.Lenth =sizeof(FY2000_Pack61_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack61_Stru)-2; //校验数据长度计算



		
	PackData->Pack_61.Year_S =SysPara.StartTime.Year;
	PackData->Pack_61.Month_S =SysPara.StartTime.Month;
	PackData->Pack_61.Day_S =SysPara.StartTime.Day;
	PackData->Pack_61.Hour_S =SysPara.StartTime.Hour;
	PackData->Pack_61.Minute_S =SysPara.StartTime.Minute;
	PackData->Pack_61.Second_S =SysPara.StartTime.Second;

	PackData->Pack_61.Year_F =SysPara.FinalTime.Year;
	PackData->Pack_61.Month_F =SysPara.FinalTime.Month;
	PackData->Pack_61.Day_F =SysPara.FinalTime.Day;
	PackData->Pack_61.Hour_F =SysPara.FinalTime.Hour;
	PackData->Pack_61.Minute_F =SysPara.FinalTime.Minute;
	PackData->Pack_61.Second_F =SysPara.FinalTime.Second;
	
	PackData->Pack_61.TimeSetFlag =0XAA;
	
	PackData->Pack_61.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_61.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 

	
}




/*
62组包子函数
主机广播发送供暖季通断控制器清除计量数据命令

*/
void FY2000_Pack_62(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT16U PackSize =0;

	PackData->Pack_62.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_62.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_62.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_62.Head.DESN =0;
	PackData->Pack_62.Head.GN =0;
	PackData->Pack_62.Head.ConType =62;

	PackData->Pack_62.Head.Lenth =sizeof(FY2000_Pack62_Stru)-FY2000Pro_HeadSize-2;//实际有效数据区长度
	PackSize =sizeof(FY2000_Pack62_Stru)-2; //校验数据长度计算

	
	PackData->Pack_62.DATA =0XAAAA;
	
	PackData->Pack_62.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_62.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 
}



/*
128组包子函数

*/
INT8U  FY2000_Pack_128(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;
	
	if ( PackData->Pack_128.CtrlFlg ==0XAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
129组包子函数

*/
INT8U  FY2000_Pack_129(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;

	if ( PackData->Pack_129.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}





/*
131组包子函数

*/
INT8U  FY2000_Pack_131(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;

	if ( PackData->Pack_131.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
132解析子函数

*/
INT8U  FY2000_Pack_132(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT16U DESN =PackData->Pack_132.Head.DESN;
	INT8U BackVal =0X01;
	INT32U MeterID =PackData->Pack_132.Head.SN;
	if ( MeterID !=0)
	{
		if(ClientCH1Ctrler.Device.ID ==MeterID)
		{
			if(SysDeviceList.Device[DESN].ID ==MeterID) //设备类型和产品ID均进行匹配验证
			{
				BackVal =0X00;
			}
		}
	}
	return BackVal;
}



/*
133组包子函数

*/

INT8U  FY2000_Pack_133(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;
	
	if ( PackData->Pack_133.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
134组包子函数
*/
INT8U  FY2000_Pack_134(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;

	if( PackData->Pack_134.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}







/*

函数名称: INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
函数功能:丰源智控协议接收服务函数
Ctrl_Point:接收控制器
Protocol: 协议编号
返回值: 0X00 协议正常 0X01 协议处理出现问题 0XFF 协议不存在
*/
INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(Ctrl_Point->InputPack);		   	//输入指针交接
	FY2000_Pack_Uni* PackOUTData =(FY2000_Pack_Uni*)(Ctrl_Point->OutputPack);	    //输出指针交接
	INT8U Proto_RX =Protocol;
	
	PackData =PackData;
	PackOUTData =PackOUTData;
	switch (Proto_RX)
	{
		case 128:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			ClientCH1Ctrler.SignleCom =RESET;
			
			ErrorFlg =FY2000_Pack_128(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_OK;
				dbg_printf(DEBUG_INFO,"阀门动作执行成功...，类型:%d  编号%08lX",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			else
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_FT;
				dbg_printf(DEBUG_INFO,"阀门动作执行失败...，类型:%d  编号%08lX",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			FY_1000Send_Code_QInput(&SendBuffer,0X0E);
			

			
		}break;
		case 129:
		{
			ErrorFlg =FY2000_Pack_129(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}			 
		}break;
		
		case 131:
		{
			ErrorFlg =FY2000_Pack_131(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}				 
		}break;

		case 132:
		{
			ErrorFlg =FY2000_Pack_132(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				INT16U DESN =PackData->Pack_132.Head.DESN;
				INT16U UserNum =0;		//用户编号
				INT8U DevType =ClientCH1Ctrler.Device.Type;
				if( DevType ==Valve_U)
				{
					
					SysDevData[DESN].Device3.Cur_Temp =PackData->Pack_132.Cur_Temp;		//当前温度
					SysDevData[DESN].Device3.Ave_Temp =PackData->Pack_132.Ave_Temp;		//平均温度
					SysDevData[DESN].Device3.Input_Temp =PackData->Pack_132.Input_Temp;		//入口温度
					SysDevData[DESN].Device3.Output_Temp =PackData->Pack_132.Output_Temp;	//出口温度
					SysDevData[DESN].Device3.ValvePosition =PackData->Pack_132.Valve_POS;		//阀门位置
					SysDevData[DESN].Device3.Cycle_OpTim =PackData->Pack_132.Cycle_OpTim;	//周期开阀时间/供暖期内累计开阀时间
					SysDevData[DESN].Device3.Cycle_OpRat =PackData->Pack_132.Cycle_OpRat;	//周期开阀比例

					SysDevData[DESN].Device3.Face_State =PackData->Pack_132.Face_State;		//面板状态
					SysDevData[DESN].Device3.Valve_State =PackData->Pack_132.Valve_STate; 	//阀门状态

					if( SysDevData[DESN].Device3.Set_TCtrlFg !=0XAA)						//用户面板温度不是系统设置
					{
						SysDevData[DESN].Device3.Set_Temp =PackData->Pack_132.Set_Temp;
					}
					
					SysDevStatus[DESN].Device3.ComSucNum +=1;
					SysDevStatus[DESN].Device3.ComFauNum =0;

					/*通断时间面积法计量方案设备数据和用户数据匹配*/
					if( SysPara.DeviceType ==Type_Valve)	//通断时间面积法热计量系统
					{
						INT32U UserID =ClientCH1Ctrler.Device.UserKEY;
						
						if(GetUser_Num(UserID,&UserNum ) ==HAL_OK) //用户查询成功
						{
							UserData[UserNum].Total_Time =SysDevData[DESN].Device3.Cycle_OpTim;	//将阀门开阀数据传递给用户
							SysDevData[DESN].Device3.Apportion_Energy =UserData[UserNum].Apportion_Energy;		//将用户的分摊热量回传给通断控制器
							
							 if(UserData_Save(UserNum) ==HAL_OK)
							 {
								dbg_printf(DEBUG_DEBUG,"用户数据保存  编号: %d \r\n ",UserNum);
							 }
						}						
					}


					if( SysDevData_Save(DESN) ==HAL_OK)
					{
						dbg_printf(DEBUG_DEBUG,"设备数据保存  编号: %d \r\n ",DESN);
					}


					
/*
通断控制器出入口温度的调整
目前只有用于唐山热计量项目	2017 11
**********************************************************************************/
#if (1== Valve_U_TempChange)
					/*根据用户查询栋表的的实时数据*/
					INT16U Temp_IN =SysDevData[DESN].Device3.Input_Temp;
					INT16U Temp_OUT =SysDevData[DESN].Device3.Output_Temp;
					
					INT16U Temp_IN_B =0;
					INT16U Temp_OUT_B =0;

					if((Temp_IN >3500)||(Temp_OUT >3500))
					{
						INT32U BuildMeterID =0;	
						INT16U DevNum =0;
						BuildMeterID =SysUserList.User[UserNum].BuildMeter_ID;
						
						if( GetMeters_Num(BuildMeterID, Meter_H,&DevNum)==HAL_OK)
						{
							Temp_IN_B =SysDevData[DevNum].Device5.Input_Temp;
							Temp_OUT_B =SysDevData[DevNum].Device5.Output_Temp;
							
							if( (Temp_IN_B >1000)&&(Temp_OUT_B>1000)&&(SysDevStatusErr[DevNum]==0x00))	//楼栋表温度数据有效  通信正常
							{
								time_t seed =RTC_TimeTicks;
								INT32U cal =0;
								INT16S cal0 =0;	
								
								srand(seed);
								cal = rand();
								cal0 =cal%99;
								
								cal0=cal0-50;
								if(cal0 >0)
								{
									Temp_IN =Temp_IN_B+cal0;
									Temp_OUT =Temp_OUT_B+cal0;
								}
								else
								{
									Temp_IN =Temp_IN_B-(0-cal0);
									Temp_OUT =Temp_OUT_B-(0-cal0);
								}
								
							}
						}
					}
					SysDevData[DESN].Device3.Input_Temp =Temp_IN;
					SysDevData[DESN].Device3.Output_Temp =Temp_OUT;
					
#endif

/*END********************************************************************** */


					/* 后台实时数据转发   自动抄收*/
						//if( SysPara.SendMode ==DevSendMode_Auto )//数据上报类型为自动跟踪	或者外部触发数据超收 
						if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//数据上报类型为自动跟踪	或者外部触发数据超收 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_Type=Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Set_Temp =SysDevData[DESN].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cur_Temp =SysDevData[DESN].Device3.Cur_Temp;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Ave_Temp =SysDevData[DESN].Device3.Ave_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Input_Temp =SysDevData[DESN].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Output_Temp =SysDevData[DESN].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ValvePosition =SysDevData[DESN].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpTim =SysDevData[DESN].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Apportion_Energy =SysDevData[DESN].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Face_State =SysDevData[DESN].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Valve_State =SysDevData[DESN].Device3.Valve_State;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备自动抄收数据转发至服务器  编号: %d SN:%08lX\r\n ",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID);
							}
						}
					/* 后台实时数据转发 自动抄收END*/

					/* 后台实时数据转发   自动抄收*/
						if( ClientCH1Ctrler.UaComFlg !=0 )//数据上报类型为自动跟踪	或者外部触发数据超收 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_Type=Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Set_Temp =SysDevData[DESN].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cur_Temp =SysDevData[DESN].Device3.Cur_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Ave_Temp =SysDevData[DESN].Device3.Ave_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Input_Temp =SysDevData[DESN].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Output_Temp =SysDevData[DESN].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.ValvePosition =SysDevData[DESN].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cycle_OpTim =SysDevData[DESN].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Apportion_Energy =SysDevData[DESN].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Face_State =SysDevData[DESN].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Valve_State =SysDevData[DESN].Device3.Valve_State;
							


							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备远程抄收数据转发至服务器  编号: %d SN:%08lX\r\n ",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_ID);
							}
						}
					/* 后台实时数据转发 自动抄收END*/

					
					ClientCH1Ctrler.SignleCom =RESET;

				}
				
				else if(DevType ==Valve_UH )			//回水通断控制器   设备类型4
				{

					SysDevData[DESN].Device4.ValvePosition =PackData->Pack_132.Valve_POS;		//阀门位置
					
					SysDevData[DESN].Device4.Cycle_OpTim =PackData->Pack_132.Cycle_OpTim;	//周期开阀时间/供暖期内累计开阀时间
					SysDevData[DESN].Device4.Cycle_OpRat =PackData->Pack_132.Cycle_OpRat;	//周期开阀比例

					SysDevData[DESN].Device4.Valve_State =PackData->Pack_132.Valve_STate; 	//阀门状态

				
					SysDevStatus[DESN].Device4.ComSucNum +=1;
					SysDevStatus[DESN].Device4.ComFauNum =0;
					
					if( SysDevData_Save(DESN) ==HAL_OK)
					{
						dbg_printf(DEBUG_DEBUG,"设备数据保存  编号: %d \r\n ",DESN);
					}

					/* 后台实时数据转发  自动抄收 */
						//if( SysPara.SendMode ==DevSendMode_Auto )//数据上报类型为自动跟踪	或者外部触发数据超收 
						if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//数据上报类型为自动跟踪	或者外部触发数据超收 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0XAA;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type=Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DESN].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =SysDevData[DESN].Device4.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DESN].Device4.Valve_State;
							
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备自动抄收数据转发至服务器  编号: %d SN:%08lX",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}
						}
					/* 后台实时数据转发 自动抄收END*/		

					/* 后台实时数据转发  远程抄收 */
						if( ClientCH1Ctrler.UaComFlg !=0 )//数据上报类型为自动跟踪	或者外部触发数据超收 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.CtrlFlag=0XAA;							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_Type=Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.ValvePosition =SysDevData[DESN].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim =SysDevData[DESN].Device4.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Valve_State =SysDevData[DESN].Device4.Valve_State;
							
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备远程抄收数据转发至服务器  编号: %d SN:%08lX",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID);
							}
						}
					/* 后台实时数据转发 远程抄收END*/						
					
					ClientCH1Ctrler.SignleCom =RESET;
				}
			}				 
		}break;
		
		case 133:
		{
			ErrorFlg =FY2000_Pack_133(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}				 
		}break;
		default :ErrorFlg =0XFF; break;
	}
	return ErrorFlg;
}




 


/*
FY188_打包服务函数

*/
INT8U FY2000_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err;

	
	/* 总线空闲状态检查 */
//	if(*(Ctrl_Point->SendBusy) != HAL_OK)		//总线空闲状态检查
//	{
//		return HAL_ERROR;
//	}

	/* 接收队列数据 */
	Err =xQueueReceive(UART_TO_FY2000_Msg,&FY2000_Q_RX_BufferP,5);

	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* 复制待发送数据并打包 */
	FY2000_Q_RX_Buffer =*FY2000_Q_RX_BufferP;
	Ctrl_Point->PackCreatFlag =FY2000_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =FY2000_Q_RX_Buffer.PackINPort;

	/* 创建启动标志检查 总线空闲状态检查 */
	if(Ctrl_Point->PackCreatFlag != ENABLE)
	{
		return HAL_ERROR;
	}

	Ctrl_Point->PackCreatFlag =DISABLE;

	/* 打包协议编号识别 */
	switch(Ctrl_Point->PackINPort)
	{
		case 50:
		{
			
			FY2000_Pack_50(Ctrl_Point);
			
		}break;
		
		case 51:
		{
			FY2000_Pack_51(Ctrl_Point);

		}break;

		case 52:
		{
			FY2000_Pack_52(Ctrl_Point);
		}break;		

		case 53:
		{
			FY2000_Pack_53(Ctrl_Point);
		}break;	
		
		case 54:
		{

			FY2000_Pack_54(Ctrl_Point);
			
		}break;
		
		case 55:
		{
			FY2000_Pack_55(Ctrl_Point);
		}break;	

		case 59:
		{
			FY2000_Pack_59(Ctrl_Point);
		}break;	

		case 60:
		{
			FY2000_Pack_60(Ctrl_Point);
			
		}break;	

		case 61:
		{
			FY2000_Pack_61(Ctrl_Point);
			
		}break;
        
        case 62:
		{
			FY2000_Pack_62(Ctrl_Point);
			
		}break;
        
        default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}

	return HAL_OK;
}






/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
