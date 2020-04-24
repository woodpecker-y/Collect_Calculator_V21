#define _NWKmodbus_C_

#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#include "NWKmodbus.h"
#include "main.h"


UART_TO_NWK_QueueSend_Stru      NWK_Q_RX_Buffer;		//通信发送队列 接收缓冲器
UART_TO_NWK_QueueSend_Stru*     NWK_Q_RX_BuffeP;	    //通信发送队列 接收缓冲器P



/*
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
函数功能:协议预处理包，描述  将接收队列缓冲器的数据进行解析并进入解析包
*/
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U  Bufer;
    INT8U  CMD;
	INT32U DataBdry =0;	//有效数据区边界
	NWK_Pack_Uni* NWK_RXPack =(NWK_Pack_Uni*)(Ctrl_Point->InputPack);
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
			case 0:	//接收modbus从机地址
			{
				if (Bufer != 0)
				{
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//收到数据间隔时间清零
					Ctrl_Point->RecPackState=1;						//开始接收数据包
					DataBdry =0;
					
				}
			}break;
			
			case 1:	//接收modbus 功能码
			{	    
                    if ( Bufer == NWKPro_ACKProtocolCode03 )
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零 
                        Ctrl_Point->RecPackState=2;//开始接收数据包	
                    }
                    else if( Bufer == NWKPro_ACKProtocolCode06 )
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零 
                        Ctrl_Point->RecPackState=3;//开始接收数据包	
                        
                        NWK_RXPack.Lenth = 4;
                    }
			}break;
			
			case 2://接收功能码 03
			{

                    if ( Bufer == NWKPro_ACKProtocolSize)//读取数据长度为 0x38 = (2*0x1C)
                    {
                        NWK_RXPack.Lenth = Bufer;//接收数据长度
                        
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
                        Ctrl_Point->RecPackState=3;//开始接收数据包	
                    }
		
			}break;
			
			case 3://06 数据域接收区
			{
                if(NWK_RXPack.Lenth)
                {
                    Ctrl_Point->RecPackState=3;			            //开始接收数据包
                }
                else
                {
                    Ctrl_Point->RecPackState=4;			            //开始接收数据包
                }
                Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                Ctrl_Point->RecPackPoint +=1;
                Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零

			}break;
            
			case 4://CRC16_H
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //收到数据间隔时间清零
                Ctrl_Point->RecPackState=5;			            //开始接收数据包

			}break;
            
			case 5:	//CRC16_L
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
INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
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

INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
函数功能:丰源智控协议接收服务函数
Ctrl_Point:接收控制器
Protocol: 协议编号
返回值: 0X00 协议正常 0X01 协议处理出现问题 0XFF 协议不存在
*/
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	NWK_Pack_Uni* PackData =(NWK_Pack_Uni*)(Ctrl_Point->InputPack);		   	//输入指针交接
	INT8U Proto_RX =Protocol;

	
	switch (Proto_RX)
	{
		case 0X02:
        {
            ErrorFlg =NWK_Pack_0X02_S(Ctrl_Point);
            if(  ErrorFlg ==0X00)
            {
                
                INT8U DevType =ClientCH1Ctrler.Device.Type;
                INT16U DESN =ClientCH1Ctrler.Device.Num;
                
                
                if(DevType ==Meter_NWK )           
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
			
			ErrorFlg =NWK_Pack_0X04_S(Ctrl_Point);
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
NWK耐威科采集器发送给楼栋单元调节阀modbus协议 01 03 00 00 00 1C 44 03
*/
void NWK_Pack_S(UART_RBC_Stru* PORT)
{

	NWK_Pack_Uni* PackData =(NWK_Pack_Uni*)(PORT->OutputPack);	//指针变换
	//INT8U PackSize =0;
    //INT8U TYPE =0;

		
	PackData->Pack.Head.Addr 				= NWK_Q_RX_Buffer.ID;			//NWK_Q_RX_Buffer.ID;
	PackData->Pack.Head.CMD  				= 0X03;
	
	PackData->Pack.Register_Addr_H 	        = 0X00;
	PackData->Pack.Register_Addr_L          = 0X00;
	
	PackData->Pack.Register_Num_H 	        = 0X00;
	PackData->Pack.Register_Num_L  	        = 0X1C;
	
	PackData->Pack.CRC16_H 					= 0x44;
	PackData->Pack.CRC16_L 					= 0x03;
	
	//TYPE = 0x0B;                            //NWK_Q_RX_Buffer.COM_Type;
	
    //if(0==TYPE)
    //{
    //    TYPE =0X15;
    //}

	PORT->OutputPackSize = sizeof(NWK_Pack_Stru);
	//PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag =ENABLE;
}




/*
NWK_打包服务函数
*/
INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* 总线空闲状态检查 */

	/* 接收队列数据 */
	Err =xQueueReceive(UART_TO_NWK_Msg, &NWK_Q_RX_BuffeP,5);
	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* 复制待发送数据并打包 */
	NWK_Q_RX_Buffer =*NWK_Q_RX_BuffeP;
	Ctrl_Point->PackCreatFlag =NWK_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =NWK_Q_RX_Buffer.PackINPort;

	
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
			NWK_Pack_S(Ctrl_Point);

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



