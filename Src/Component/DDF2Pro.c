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
* @date :2018/8/19 11:10
***************************************************************
*/ 
#define _DDF2PRO_C_
#include "DDF2Pro.h"
#include "main.h"

#ifdef  Meter_DDF2_ENABLE	

UART_TO_DDF2_QueueSend_Stru DDF2_Q_RX_Buffer;		//通信发送队列 接收缓冲器
UART_TO_DDF2_QueueSend_Stru* DDF2_Q_RX_BuffeP;	//通信发送队列 接收缓冲器P






/*
void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
函数功能:协议预处理包，描述  将接收队列缓冲器的数据进行解析并进入解析包

*/
void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//有效数据区边界
	DDF2_Pack_Uni* DDF2_RXPack =(DDF2_Pack_Uni*)(Ctrl_Point->InputPack);
	while (Ctrl_Point->Rx_Rear !=Ctrl_Point->Rx_Front) 
	{
	
		Bufer=Ctrl_Point->InputBuffer[Ctrl_Point->Rx_Rear];	//从接收缓冲区读取一个字节的数据
		
		if (*(Ctrl_Point->Ticks)- Ctrl_Point->RecPackTimeOut > Ctrl_Point->TimeOut)//帧间隔没有收到新的数据，即将接收下一帧完整数据
		{
			Ctrl_Point->RecPackState=0;	//清除正在处理接收包数据标志
			Ctrl_Point->RecPackPoint=0;	//包指针
		}		
		switch(Ctrl_Point->RecPackState)
		{
			case 0:	//接收起始码
			{
				if (Bufer == DDF2Pro_StartCode) 
				{ 
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
					Ctrl_Point->RecPackState=1;						//开始接收数据包
					DataBdry =0;
					
				}
			}break;
			
			case 1:	//接收版本号/设备类型符
			{		
				if ( Bufer == DDF2Pro_ProtocolCode)
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
	
			case 4:	//接收SN 第3字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=5;//开始接收数据包	

			}break;
			case 5:	//接收SN 第4字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=6;//开始接收数据包 

			}break;			

			case 6:	//接收SNRE 第1字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=7;//开始接收数据包 

					
			}break;	
			
			case 7://接收SNRE 第2字节
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=8;//开始接收数据包 			
			}break;
			
			case 8://接收接收FAdd2
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=9;//开始接收数据包 	


			}break;

			case 9://接收ConType
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
				Ctrl_Point->RecPackState=10;//开始接收数据包 	
				
			}break;

			case 10:	//数据长度
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零

				if(DDF2_RXPack->DefaultPack.Head.Lenth)	                //判断数据内容是否存在
				{
					Ctrl_Point->RecPackState=11;			            //开始接收数据包
				}
				else
				{
					Ctrl_Point->RecPackState=12;			            //开始接收数据包
				}
				DataBdry =DDF2_RXPack->DefaultPack.Head.Lenth;
			}break;
		
			case 11:	//有效数据区
			{		


				Ctrl_Point->RecPackState=11;					//开始接收数据包
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零

				DataBdry -=1;
				if(DataBdry ==0)
				{
					Ctrl_Point->RecPackState=12;
				}
				
			}break;

			case 12:	//校验和
			{
				Ctrl_Point->RecPackState=13;					//开始接收数据包
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
				
			}break;
			
			case 13:	//结束标志
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackState=0; 
				
				if (Bufer ==DDF2Pro_EndCode)
				{
					DDF2_Pack_RxAnalyze_S(Ctrl_Point,DDF2_RXPack->DefaultPack.Head.Lenth+DDF2Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
			}break;	
			
			default:	//错误状态,恢复状态为0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_DDF2BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}

}




/*
INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
函数功能:通信解析并处理子函数
*/
INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
{
	INT8U CheckFlg =0;	//错误标志
	INT8U ProtoNO =0;	//协议编号
	DDF2_Pack_Uni* Packin =(DDF2_Pack_Uni*)Ctrl_Point->InputPack;	//指针变换
	
	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//校验错误，退出函数
	{
		return	CheckFlg;
	}
	else
	{

		ProtoNO =Packin->DefaultPack.Head.Lenth;
		if(0x05 ==ProtoNO)
		{
            ProtoNO =0x04;
		}
		else if (0x24 ==ProtoNO)
		{
            ProtoNO =0x02;

		}
		CheckFlg =DDF2_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}







/*
	主机/服务端召测实时数据命令
*/
void DDF2_Pack_0X01_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT8U PackSize =0;
    INT8U TYPE =0;
	

	PackData->Pack_01.Lead1=0XFE;			//同步码	
	PackData->Pack_01.Lead2=0XFE;			//同步码	
	PackData->Pack_01.Lead3=0XFE;			//同步码	
	PackData->Pack_01.Lead4=0XFE;			//同步码	
		
	PackData->Pack_01.Head.Start =0X68;
	PackData->Pack_01.Head.Type =0X41;

	PackData->Pack_01.Head.SN =DDF2_Q_RX_Buffer.ID;
	TYPE =DDF2_Q_RX_Buffer.COM_Type;
	if(0==TYPE)
	{
	    TYPE =0X15;
	}

	
	PackData->Pack_01.Head.SNRE =0X2000+TYPE;

	PackData->Pack_01.Head.FAdd2=0X10;
	PackData->Pack_01.Head.ConType =0X01;

	PackData->Pack_01.Head.Lenth =sizeof(DDF2Pro_Pack01_Stru)-DDF2Pro_HeadSize-2-4;//实际有效数据区长度
	PackSize =sizeof(DDF2Pro_Pack01_Stru)-2;	//校验数据长度计算
	


	PackData->Pack_01.Flag =0X902D;
	PackData->Pack_01.SER =0X01;
	
	PackData->Pack_01.Check =SUMCheck_Input((INT8U*)PackData+4,PackSize-4);
	PackData->Pack_01.End =0X16;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;
}



/*
	主机/服务端发送控制命令
*/
void DDF2_Pack_0X03_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->OutputPack);	//指针变换
	INT8U PackSize =0;

	INT8U TYPE =0;
	

	PackData->Pack_03.Lead1=0XFE;			//同步码	
	PackData->Pack_03.Lead2=0XFE;			//同步码	
	PackData->Pack_03.Lead3=0XFE;			//同步码	
	PackData->Pack_03.Lead4=0XFE;			//同步码	
		
	PackData->Pack_03.Head.Start =0X68;
	PackData->Pack_03.Head.Type =0X41;

	PackData->Pack_03.Head.SN =DDF2_Q_RX_Buffer.ID;
	TYPE =DDF2_Q_RX_Buffer.COM_Type;
	if(0==TYPE)
	{
	    TYPE =0X15;
	}
	
	PackData->Pack_03.Head.SNRE =0X2000+TYPE;

	PackData->Pack_03.Head.FAdd2=0X10;
	PackData->Pack_03.Head.ConType =0X04;

	PackData->Pack_03.Head.Lenth =sizeof(DDF2Pro_Pack03_Stru)-DDF2Pro_HeadSize-2-4;//实际有效数据区长度
	PackSize =sizeof(DDF2Pro_Pack03_Stru)-2;	//校验数据长度计算
	


	PackData->Pack_03.Flag =0XA017;
	PackData->Pack_03.SER =0X01;
	PackData->Pack_03.OUT =DDF2_Q_RX_Buffer.SendData.DDF2Data.Pack_03.OUT;
	
	PackData->Pack_03.Check =SUMCheck_Input((INT8U*)PackData+4,PackSize-4);
	PackData->Pack_03.End =0X16;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;
}




/*
	主机/服务端接收仪表返回实时数据
*/
INT8U DDF2_Pack_0X02_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;
	
	if ((PackData->Pack_02.Head.Start==0X68)&&(PackData->Pack_02.Head.Type ==0X41))	//在此判断帧头的合法性
	{
		if ((PackData->Pack_02.Head.SNRE==0x2015))
		{
			BackVal =0X00;
		}
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}




/*
	主机/服务端接收仪表返回实时数据
*/
INT8U DDF2_Pack_0X04_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->InputPack);	//指针变换
	INT8U BackVal =0X00;
	
	if ((PackData->Pack_02.Head.Start==0X68)&&(PackData->Pack_02.Head.Type ==0X41))	//在此判断帧头的合法性
	{
		if ((PackData->Pack_02.Head.SNRE==0x2015))
		{
			BackVal =0X00;
		}
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}

















/*

INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
函数功能:丰源智控协议接收服务函数
Ctrl_Point:接收控制器
Protocol: 协议编号
返回值: 0X00 协议正常 0X01 协议处理出现问题 0XFF 协议不存在
*/
INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(Ctrl_Point->InputPack);		   	//输入指针交接
	INT8U Proto_RX =Protocol;

	
	switch (Proto_RX)
	{
		case 0X02:
        {
            ErrorFlg =DDF2_Pack_0X02_S(Ctrl_Point);
            if(  ErrorFlg ==0X00)
            {
                
                INT8U DevType =ClientCH1Ctrler.Device.Type;
                INT16U DESN =ClientCH1Ctrler.Device.Num;
                
                
                if(DevType ==Meter_DDF2 )           
                {
                    if(0x01==PackData->Pack_02.IN)
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Close;   //阀门位置
                    }
                    else if(0x00==PackData->Pack_02.IN)
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Open;     //阀门位置
                    } 
                    else
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Mid;      //阀门位置
                    }
                    
                    SysDevData[DESN].Device9.Cycle_OpTim =0;
                    SysDevData[DESN].Device9.Cycle_OpRat =0;

                    SysDevData[DESN].Device9.Valve_State =0;   //阀门状态

                
                    SysDevStatus[DESN].Device9.ComSucNum +=1;
                    SysDevStatus[DESN].Device9.ComFauNum =0;
                    
                    if( SysDevData_Save(DESN) ==HAL_OK)
                    {
                        dbg_printf(DEBUG_DEBUG,"设备数据保存  编号: %d \r\n ",DESN);
                    }

                    /* 后台实时数据转发  自动抄收 */
                        //if( SysPara.SendMode ==DevSendMode_Auto )//数据上报类型为自动跟踪  或者外部触发数据超收 
                        if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//数据上报类型为自动跟踪  或者外部触发数据超收 
                        {
                            UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0XAA;                         
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type=Meter_DDF2;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag=COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DESN].Device9.ValvePosition;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =SysDevData[DESN].Device9.Cycle_OpTim;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DESN].Device9.Valve_State;
                            
                            
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"设备自动抄收数据转发  编号: %d SN:%08X",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
                            }
                        }
                    /* 后台实时数据转发 自动抄收END*/       

                    /* 后台实时数据转发  远程抄收 */
                        if( ClientCH1Ctrler.UaComFlg !=0 )//数据上报类型为自动跟踪   或者外部触发数据超收 
                        {
                            UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.CtrlFlag=0XAA;                         
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_Type=Meter_DDF2;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.ValvePosition =SysDevData[DESN].Device9.ValvePosition;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim =SysDevData[DESN].Device9.Cycle_OpTim;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Valve_State =SysDevData[DESN].Device9.Valve_State;
                            
                            
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"设备远程抄收数据转发  编号: %d SN:%08X",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID);
                            }
                        }
                    /* 后台实时数据转发 远程抄收END*/                       
                    
                    ClientCH1Ctrler.SignleCom =RESET;
                }
            }


        }break;
		case 0X04:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			
			ClientCH1Ctrler.SignleCom =RESET;
			
			ErrorFlg =DDF2_Pack_0X04_S(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_OK;
				dbg_printf(DEBUG_INFO,"阀门动作执行成功...，类型:%d  编号%08X",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			FY_1000Send_Code_QInput(&SendBuffer,0X0E);


		}break;		
		
		default :
		{
		   ErrorFlg =0XFF; 
		}break;

	}
	return ErrorFlg;
}






/*
DDF2_打包服务函数

*/
INT8U DDF2_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* 总线空闲状态检查 */

	/* 接收队列数据 */
	Err =xQueueReceive(UART_TO_DDF2_Msg,&DDF2_Q_RX_BuffeP,5);
	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* 复制待发送数据并打包 */
	DDF2_Q_RX_Buffer =*DDF2_Q_RX_BuffeP;
	Ctrl_Point->PackCreatFlag =DDF2_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =DDF2_Q_RX_Buffer.PackINPort;

	
	/* 创建启动标志检查 总线空闲状态检查 */
	if(Ctrl_Point->PackCreatFlag != ENABLE)
	{
		return HAL_ERROR;
	}
	Ctrl_Point->PackCreatFlag =DISABLE;

	/* 打包协议编号识别 */
	switch(Ctrl_Point->PackINPort)
	{
		case 0X01:
		{
			DDF2_Pack_0X01_S(Ctrl_Point);

		}break;

		case 0X03:
		{
			DDF2_Pack_0X03_S(Ctrl_Point);

		}break;

		default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}
	return HAL_OK;
}











#endif
 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
