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
* @brief :主函数
* 
* 
* 
*
* @author :许伟
* @date :2017/8/23 17:24
***************************************************************
*/ 
#define _MAIN_C_

#include "main.h"
#include "stm32f4xx_hal.h"


extern int os_debug_enabled;		
extern int os_debug_level;



/*
	Task01
	实时时钟服务函数
*/
#define Task01_Prio				2			//任务优先级
#define Task01_StkSize 			2048 		//任务堆栈大小	
TaskHandle_t Task01_Handle;					//任务句柄
void Task01_F(void const * argument);		//任务函数
/*END */



/*
	Task02
*/
#define Task02_Prio				3			//任务优先级
#define Task02_StkSize 			128  		//任务堆栈大小	
TaskHandle_t Task02_Handle;					//任务句柄
void Task02_F(void const * argument);		//任务函数
/*END */



/*
	Task03
	设备按键响应服务函数
	
*/
#define Task03_Prio				4			//任务优先级
#define Task03_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task03_Handle;					//任务句柄
void Task03_F(void const * argument);		//任务函数
/*END */





/*
	Task04
	设备显示服务
*/
#define Task04_Prio				5			//任务优先级
#define Task04_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task04_Handle;					//任务句柄
void Task04_F(void const * argument);		//任务函数
/*END */




/*
	Task05
	异步串行通信接收服务
*/
#define Task05_Prio				12			//任务优先级
#define Task05_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task05_Handle;					//任务句柄
void Task05_F(void const * argument);		//任务函数
/*END */


/*
	Task06
	异步串行通信发送服务
*/
#define Task06_Prio				11			//任务优先级
#define Task06_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task06_Handle;					//任务句柄
void Task06_F(void const * argument);		//任务函数
/*END */


/*
	Task07
	异步串行通信打包服务
*/
#define Task07_Prio				6			//任务优先级
#define Task07_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task07_Handle;					//任务句柄
void Task07_F(void const * argument);		//任务函数
/*END */



/*
	Task08
	Client 通信通道发送服务
*/
#define Task08_Prio				4			//任务优先级
#define Task08_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task08_Handle;					//任务句柄
void Task08_F(void const * argument);		//任务函数
/*END */


/*
	Task09
	Client通信通道总线控制服务
*/
#define Task09_Prio				4			//任务优先级
#define Task09_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task09_Handle;					//任务句柄
void Task09_F(void const * argument);		//任务函数
/*END */


/*
	Task10
	Client 通信通道1 设备广播对时触发控制
*/
#define Task10_Prio				2			//任务优先级
#define Task10_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task10_Handle;					//任务句柄
void Task10_F(void const * argument);		//任务函数


/*
	Task11
	采集器上行通信服务 测试

#define Task11_Prio				3			//任务优先级
#define Task11_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task11_Handle;					//任务句柄
void Task11_F(void const * argument);		//任务函数
*/

/*
	TaskCli
	超级终端任务
*/
#define TaskCli_Prio            1			//任务优先级
#define TaskCli_StkSize         2048  		//任务堆栈大小	
TaskHandle_t TaskCli_Handle;                //任务句柄
void TaskCli(void const * argument);        //任务函数



/*
	Task12
	用户定时数据上传任务
*/
#define Task12_Prio				3			//任务优先级
#define Task12_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task12_Handle;					//任务句柄
void Task12_F(void const * argument);       //任务函数




/*
	Task13
	用户定时数据上传任务
*/
#define Task13_Prio				2			//任务优先级
#define Task13_StkSize 			256  		//任务堆栈大小	
TaskHandle_t Task13_Handle;					//任务句柄
void Task13_F(void const * argument);       //任务函数








osTimerId Timer01Handle;						//定时器1句柄
SemaphoreHandle_t Display_Semaphore;			//计数型信号量 用于LCD刷新
SemaphoreHandle_t UseSend_Semaphore;			//计数型信号量 用户数据 发送数据
SemaphoreHandle_t EneryShare_Semaphore;			//计数型信号量 用于系统热量分摊
SemaphoreHandle_t DataSave_Semaphore;			//设备历史数据保存



/*系统定时服务相关服务声明 */
RealClock_Str  AlarmTime;						//定义闹铃触发定时时间 全局

/* 历史数据保存闹铃 */
AlarmClk_Stru* Alarm_DataSave;					//定义历史数据保存闹铃
void Alarm_DataSave_CallBack(void); 			//定义历史数据保存闹铃触发回调函数


/* 用户热量定时分摊 */
AlarmClk_Stru* Alarm_UserShare;					//定义用户数据定时分摊闹铃
void Alarm_UserShare_CallBack(void); 			//定义用户数据定时分摊闹铃触发回调函数

EventBits_t Iwdg_T1;
EventBits_t Iwdg_T2;
EventBits_t Iwdg_T5;
EventBits_t Iwdg_T6;
EventBits_t Iwdg_T7;

EventBits_t Iwdg_T8;
EventBits_t Iwdg_T9;
EventBits_t Iwdg_T10;





#define APP_VECT_TAB_OFFSET    0x20000	//中断向量表偏移
int main(void)
{


	/* 增加BootLoader后，要更新中断向量地址 */
//	SCB->VTOR = FLASH_BASE | APP_VECT_TAB_OFFSET;
	 
    HAL_Init();							//HAL组件初始化
    SystemClock_Config();				//系统时钟初始化

	SysLed_Cfg();						//系统工作指示灯初始化
	SP706_Cfg();						//外部复位芯片SP706初始化
	dogInit();							//守护看门狗任务初始化
	SysBeep_Cfg();						//系统蜂鸣器功能初始化

	huart1.Init.BaudRate =115200;		
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Parity =UART_PARITY_NONE;
	UART1_Cfg();						//通用异步端口1初始化

	int cli_res = cli_init();			//超级终端及调试模块初始化
	
	huart2.Init.BaudRate =9600;
	huart2.Init.WordLength = UART_WORDLENGTH_9B;
	huart2.Init.Parity =UART_PARITY_EVEN;
	UART2_Cfg();						//通用异步端口2初始化

	
	huart3.Init.BaudRate =2400;
	huart3.Init.WordLength = UART_WORDLENGTH_9B;
	huart3.Init.Parity =UART_PARITY_EVEN;	
	UART3_Cfg();						//通用异步端口3初始化

	
	M4_CRC_PHY_Init();					//硬件CRC初始化


	IIC1_Cfg();							//IIC1硬件接口初始化
	FRAM_Init();						//铁电存储器初始化
	IIC2_Cfg();							//IIC2硬件接口初始化


	MX_FATFS_Init();                    //FATFS文件系统初始化
    
    


	/* 系统闹铃组件初始化*/
	AlarmClk_Init();		

	/*
		数据保存闹铃触发事件
		闹铃创建 
		@使能 禁止   
		@回调函数   
		@周期触发使能
		@循环时间  XX(分钟)
	*/
	Alarm_DataSave = AlarmClk_CreatOne( AlarmClk_Disable,Alarm_DataSave_CallBack,AlarmClk_Enable,60*24);
	AlarmTime.Year =2017;
	AlarmTime.Month =10;
	AlarmTime.Day =27;
	AlarmTime.Hour =23;
	AlarmTime.Minute = 55;
	AlarmTime.Second = 00;
	AlarmClk_ParaSet(Alarm_DataSave,&AlarmTime);
	AlarmClk_EnableCtrl(Alarm_DataSave,AlarmClk_Enable);





/*异步穿行收发器通信组件初始化*/
	UART_RBC_ControlerInit();
	
	UART_TO_FY1000_CCB_Init_S();											//FY1000通信组件服务端初始化
	UART_TO_FY2000_CCB_Init_S();											//FY2000通信组件服务端初始化
	UART_TO_FY188_CCB_Init_S();											    //FY188通信组件服务端初始化

#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_CCB_Init_S();											    //HZ188通信组件服务端初始化
#endif

#ifdef  Meter_XY_ENABLE	    
	UART_TO_XY188_CCB_Init_S();											    //XY188通信组件服务端初始化
#endif    
	
#ifdef  Meter_HT2X_ENABLE	    
        UART_TO_HT2X188_CCB_Init_S();                                       //HT2X188通信组件服务端初始化
#endif  

#ifdef  Meter_BRC_ENABLE	    
        UART_TO_BRC188_CCB_Init_S();                                        //BRC188通信组件服务端初始化
#endif    

#ifdef  Meter_DDF2_ENABLE	    
        UART_TO_DDF2_CCB_Init_S();                                          //DDF2通信组件服务端初始化
#endif  

#ifdef  Valve_NWK_ENABLE	    
        UART_TO_NWK_CCB_Init_S();                                          //NWK通信组件服务端初始化
#endif  

/*END*/





	W25QXX_Init();					                                        //片外Flash初始化
	FlashID =W25QXX_ReadID();		                                        //读取FlashID


	PowerRelay_Init();				                                        //主供电回路控制继电器初始化

	dbg_printf(DEBUG_INFO,"系统正在初始化......欢迎使用......\r\n\r\n");

	/*   系统参数初始化......*/
	if( SysPara_Init() ==HAL_OK )
	{
		os_debug_enabled    = SysPara.DebugEnable;
		os_debug_level      = SysPara.DebugLevel;

		dbg_printf(DEBUG_INFO, "系统参数区初始化完成......\r\n");
		dbg_printf(DEBUG_DEBUG, "系统参数区地址:   %ld", SysPara_Addr);
		dbg_printf(DEBUG_DEBUG, "系统参数区容量:   %d", sizeof(SysPara_Stru));	
		
	}
	else
	{
		dbg_printf(DEBUG_ERR,"系统参数初始化失败......\r\n");
		SysPara_Reset();
	}

	dbg_printf(DEBUG_INFO,"调试端口UART1 %d  %c  %d  %d...", huart1.Init.BaudRate, 'N', 8, huart1.Init.StopBits);
	dbg_printf(DEBUG_DEBUG,"STM32F407VGT6...\r\n");


	if(FRAM_USED > FRAM_Size)
	{
		while(1)
		{
			dbg_printf(DEBUG_ERR,"FRAM 容量受限...\r\n");
			HAL_Delay(2000);
		}
	}


	switch(FlashID)
	{
		case 0XEF13 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q80,容量 1M Byte\r\n");
		}break;
		
		case 0XEF14 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q16,容量 2M Byte\r\n");
		}break;	
		
		case 0XEF15 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q32,容量 4M Byte\r\n");
		}break;	

		case 0XEF16 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q64,容量 8M Byte\r\n");
		}break;	

		case 0XEF17 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q128,容量 16M Byte\r\n");
		}break;	
		
		case 0XEF18 :
		{
			dbg_printf(DEBUG_INFO,"板载Flash型号: W25Q256,容量 32M Byte\r\n");
		}break;	
		default :
		{
			dbg_printf(DEBUG_INFO,"板载Flash初始化失败\r\n");

		}break;
	}




	/*	 用户参数初始化......*/
	if( SysUserList_Init() ==HAL_OK)
	{
		GetSystemUserNum();
		dbg_printf(DEBUG_INFO,"用户参数区初始化完成......");
		dbg_printf(DEBUG_DEBUG,"用户参数地址:   %ld",SysUserList_Addr);
		dbg_printf(DEBUG_DEBUG,"用户参数容量:   %d\r\n",sizeof(SysUserList_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"用户参数区初始化失败......\r\n\r\n");
	}
	




	/*	 设备参数初始化......*/
	if( SysDeviceList_Init() ==HAL_OK)
	{
		GetSystemDevMessage();
		dbg_printf(DEBUG_INFO,"设备参数区初始化完成......");
		dbg_printf(DEBUG_DEBUG,"设备参数地址:   %ld",SysDeviceList_Addr);
		dbg_printf(DEBUG_DEBUG,"设备参数容量:   %d\r\n",sizeof(SysDeviceList_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"设备参数区初始化失败......\r\n\r\n");
	}
	



	/*  用户数据初始化 */
	if( UserData_InitALL(MAXUser_Num) ==HAL_OK )
	{
		dbg_printf(DEBUG_INFO,"用户数据区初始化完成......");
		dbg_printf(DEBUG_DEBUG,"用户容量:       %d",MAXUser_Num);
		dbg_printf(DEBUG_DEBUG,"用户数据地址:   %ld",UserData_Addr);
		dbg_printf(DEBUG_DEBUG,"用户数据容量:   %d\r\n",sizeof(UserData_Stru)*MAXUser_Num);

	}
	else
	{
		dbg_printf(DEBUG_ERR,"用户数据区初始化失败......\r\n");
	}



	
	
	/* 设备数据初始化*/
	if( SysDevData_InitALL(MAXDevice_Num) ==HAL_OK )
	{
		dbg_printf(DEBUG_INFO,"设备数据区初始化完成......");
		dbg_printf(DEBUG_DEBUG,"设备容量:       %d",MAXDevice_Num);
		dbg_printf(DEBUG_DEBUG,"设备数据地址:   %ld",DevData_Addr);
		dbg_printf(DEBUG_DEBUG,"设备数据容量:   %d\r\n",MAXDevice_Num*sizeof(SysDevData_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"设备数据区初始化失败......\r\n\r\n");
	}	



	dbg_printf(DEBUG_INFO,"设备数据区全部初始化完成...");
	dbg_printf(DEBUG_INFO,"DEBUG_DEBUG:       %ld....\r\n",FRAM_USED);



	ID =HAL_GetREVID();
	dbg_printf(DEBUG_DEBUG,"HAL_GetREVID:%ld",ID);
	
	ID =HAL_GetDEVID();
	dbg_printf(DEBUG_DEBUG,"HAL_GetDEVID:%ld",ID);
	
	Get_ChipID( &ChipID);
	dbg_printf(DEBUG_DEBUG,"MCUchipID:%d %d %d \r\n\r\n",ChipID.Fourdata.ChipUniqueID[0],ChipID.Fourdata.ChipUniqueID[1],ChipID.Fourdata.ChipUniqueID[2]);

	
	Init_PaulseFunction();										//虚拟脉冲控制功能初始化
    Beep_Ctrler=Pulse_Create(0,BeepWork_RebackFun);				//创建一个脉冲控制   使能位   回调函数
	PulseLeaguer_SET(Beep_Ctrler, 1, 100, 3, 20, 0, 0);         //功能指针  脉冲数量  扫描间隔(tick*X) 边沿宽度   周期    周期计数器  当前状态
	PulseLeaguer_Enalbe(Beep_Ctrler, 1);                        //使能某个脉冲控制模块	


    LedBR_Ctrler=Pulse_Create(0,LEDBR_RebackFun);               //创建一个脉冲控制   使能位   回调函数
	PulseLeaguer_SET(LedBR_Ctrler, 2, 10, 8, 16, 0, 0);         //功能指针  脉冲数量  扫描间隔(tick*X) 边沿宽度   周期    周期计数器  当前状态
	PulseLeaguer_Enalbe(LedBR_Ctrler, 1);                       //使能某个脉冲控制模块	


	if(PCF8563_Read(&RTC_Time) ==HAL_OK)						//实时时钟读取
	{
		dbg_printf(DEBUG_INFO,"实时时钟初始化完成...\r\n");
	}
	else
	{
		dbg_printf(DEBUG_ERR,"实时时钟初始化错误...\r\n\r\n");
	}
	
	PowerStateRecord_Init();									//上电记录参数初始化
	PowerStateRecord_Update();								    //上电记录参数更新



	/*操作系统初始化部分*/

	portENTER_CRITICAL();	                                    //进入临界区
	dbg_printf(DEBUG_INFO,"系统硬初始化完成，操作系统加载中...\r\n");
	fy1000SendMetexInit();                                      //FY1000Send互斥锁初始化
	ClientCH1SendMetexInit();	                                //终端通信通道互斥锁初始化
	
	KEY_OUT_Msg =xQueueCreate(BUTTONMSG_Q_NUM, sizeof(KEY_OUT_Stru));							            //创建应用于按键的消息队列
    
	UART_TO_FY188_Msg =xQueueCreate(UART_TO_FY188_Q_NUM, sizeof(UART_TO_FY188_QueueSend_Stru*));	        //创建应用于UARTRBC的消息队列
	UART_TO_FY2000_Msg =xQueueCreate(UART_TO_FY2000_Q_NUM, sizeof(UART_TO_FY2000_QueueSend_Stru*));	        //创建应用于UARTRBC的消息队列
	UART_TO_FY1000_Msg =xQueueCreate(UART_TO_FY1000_Q_NUM, sizeof(UART_TO_FY1000_QueueSend_Stru*));	        //创建应用于UARTRBC的消息队列

    
#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_Msg =xQueueCreate(UART_TO_HZCRL_Q_NUM, sizeof(UART_TO_HZCRL_QueueSend_Stru*));	        //创建应用于UARTRBC的消息队列
#endif

#ifdef Meter_XY_ENABLE
	UART_TO_XY188_Msg =xQueueCreate(UART_TO_XY188_Q_NUM, sizeof(UART_TO_XY188_QueueSend_Stru*));	        //创建应用于UARTRBC的消息队列
#endif

#ifdef Meter_HT2X_ENABLE
        UART_TO_HT2X188_Msg =xQueueCreate(UART_TO_HT2X188_Q_NUM, sizeof(UART_TO_HT2X188_QueueSend_Stru*));   //创建应用于UARTRBC的消息队列
#endif

#ifdef Meter_BRC_ENABLE
        UART_TO_BRC188_Msg =xQueueCreate(UART_TO_BRC188_Q_NUM, sizeof(UART_TO_BRC188_QueueSend_Stru*));      //创建应用于UARTRBC的消息队列
#endif

#ifdef Meter_DDF2_ENABLE
        UART_TO_DDF2_Msg =xQueueCreate(UART_TO_DDF2_Q_NUM, sizeof(UART_TO_DDF2_QueueSend_Stru*));            //创建应用于UARTRBC的消息队列
#endif

#ifdef Valve_NWK_ENABLE
        UART_TO_NWK_Msg = xQueueCreate(UART_TO_NWK_Q_NUM, sizeof(UART_TO_NWK_QueueSend_Stru*));               //创建应用于UARTRBC的消息队列
#endif



	
	ClientCH1_Msg =xQueueCreate(ClientCH1_Q_NUM, sizeof(ClientCH1_Queue_Stru*));        //创建应用于终端通信的消息队列

	Display_Semaphore =xSemaphoreCreateCounting(8,0);                                   //创建服务于LCD扫描的计数型信号量
	UseSend_Semaphore =xSemaphoreCreateCounting(4,0);                                   //创建计数型信号量 用户数据的发送数据
	EneryShare_Semaphore=xSemaphoreCreateCounting(4,0);                                 //创建计数型信号量 用于系统数据热量分摊
						
	dbg_printf(DEBUG_DEBUG,"系统信号量初始化完成...\r\n");
	
    //Task01
    xTaskCreate((TaskFunction_t )Task01_F,				//实时时钟  
                (const char*	)"RealTimeClk",   	    //任务名称
                (uint16_t	)Task01_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task01_Prio,		    //任务优先级 2
                (TaskHandle_t*	)&Task01_Handle);	    //任务句柄


    //Task02
    xTaskCreate((TaskFunction_t )Task02_F,				//脉冲控制  
                (const char*	)"PulseCTRL",   	    //任务名称
                (uint16_t	)Task02_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task02_Prio,		    //任务优先级 3
                (TaskHandle_t*	)&Task02_Handle);	    //任务句柄

    //Task03
    xTaskCreate((TaskFunction_t )Task03_F,				//按键扫描服务函数  
                (const char*	)"UI_KEY",   		    //任务名称
                (uint16_t	)Task03_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task03_Prio,		    //任务优先级 4
                (TaskHandle_t*	)&Task03_Handle);	    //任务句柄


    //Task04
    xTaskCreate((TaskFunction_t )Task04_F,				//液晶驱动服务函数  
                (const char*	)"UI_LCD",   	        //任务名称
                (uint16_t	)Task04_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task04_Prio,		    //任务优先级 5
                (TaskHandle_t*	)&Task04_Handle);	    //任务句柄

    //Task05
    xTaskCreate((TaskFunction_t )Task05_F,				//异步串行通信接收服务  
                (const char*	)"UART_RBC_Rx",         //任务名称
                (uint16_t	)Task05_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task05_Prio,		    //任务优先级 12
                (TaskHandle_t*	)&Task05_Handle);	    //任务句柄


    //Task06
    xTaskCreate((TaskFunction_t )Task06_F,				//异步串行通信发送服务  
                (const char*	)"UART_RBC_Tx",         //任务名称
                (uint16_t	)Task06_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task06_Prio,		    //任务优先级 11
                (TaskHandle_t*	)&Task06_Handle);	    //任务句柄


    //Task07
    xTaskCreate((TaskFunction_t )Task07_F,				//异步串行通信服务打包  
                (const char*	)"UART_Packing",        //任务名称
                (uint16_t	)Task07_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task07_Prio,		    //任务优先级 6
                (TaskHandle_t*	)&Task07_Handle);	    //任务句柄


    //Task08
    xTaskCreate((TaskFunction_t )Task08_F,				//Client 通信通道1 发送服务  
                (const char*	)"ClientSend",          //任务名称
                (uint16_t	)Task08_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task08_Prio,		    //任务优先级 4
                (TaskHandle_t*	)&Task08_Handle);	    //任务句柄        


    //Task09
    xTaskCreate((TaskFunction_t )Task09_F,				//Client 通信通道1 总线控制服务  
                (const char*	)"ClientCtrler",        //任务名称
                (uint16_t	)Task09_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task09_Prio,		    //任务优先级 4
                (TaskHandle_t*	)&Task09_Handle);	    //任务句柄     

              
    //Task10
    xTaskCreate((TaskFunction_t )Task10_F,				//Client 通信通道1 设备广播对时触发控制  
                (const char*	)"Task10_N",   	        //任务名称
                (uint16_t	)Task10_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task10_Prio,		    //任务优先级 2
                (TaskHandle_t*	)&Task10_Handle);	    //任务句柄 



                
/*
    //Task11
    xTaskCreate((TaskFunction_t )Task11_F,				//任务函数  
                (const char*	)"Task11_N",   	        //任务名称
                (uint16_t	)Task11_StkSize,			//任务堆栈
                (void*		)NULL,			            //任务参数
                (UBaseType_t	)Task11_Prio,		    //任务优先级
                (TaskHandle_t*	)&Task11_Handle);	    //任务句柄                     
*/



	//TaskCli
	if(CLI_R_OK == cli_res)
	{
		xTaskCreate((TaskFunction_t )TaskCli,		    //超级终端任务  
					(const char*	)"TaskCli",   	    //任务名称
					(uint16_t	)TaskCli_StkSize,	    //任务堆栈
					(void*		)NULL,			        //任务参数
					(UBaseType_t	)TaskCli_Prio,		//任务优先级 1
					(TaskHandle_t*	)&TaskCli_Handle);	//任务句柄     
	}



    //Task12  
    xTaskCreate((TaskFunction_t )Task12_F,				//用户数据定时上报任务   
                (const char*	)"Userdata_Send",   	//任务名称
                (uint16_t	)Task12_StkSize,			//任务堆栈
                (void*		)NULL,				        //任务参数
                (UBaseType_t	)Task12_Prio,			//任务优先级 3
                (TaskHandle_t*	)&Task12_Handle);		//任务句柄    


    //Task13  
    xTaskCreate((TaskFunction_t )Task13_F,				//设备数据间隔上报任务   
                (const char*	)"Devdata_Send",   	    //任务名称
                (uint16_t	)Task13_StkSize,			//任务堆栈
                (void*		)NULL,				        //任务参数
                (UBaseType_t	)Task13_Prio,			//任务优先级 2
                (TaskHandle_t*	)&Task13_Handle);		//任务句柄   



		
	dbg_printf(DEBUG_INFO,"操作系统加载成功...");
	dbg_printf(DEBUG_INFO,"系统初始化完成......欢迎使用...");	
	dbg_printf(DEBUG_INFO,"MakeInfo: %s %s \r\n\r\n",__DATE__,__TIME__); 
	portEXIT_CRITICAL();//退出临界代码



	
    osKernelStart();
	/*操作系统初始化结束*/

	
    while (1){}
}



void TaskCli(void const * argument)
{
  /* Infinite loop */
	cli_main();
	osThreadTerminate(NULL);
}









/*空闲任务*/
void vApplicationIdleHook(void)
{
	if( xTaskGetTickCount() !=SystemTick_ms)
	{
		SystemTick_ms	=xTaskGetTickCount();

		if(SystemTick_ms -SP706_Tick >ExWDT_CLs)
		{
			SP706_Tick =SystemTick_ms;
		}
	}
	/*脉冲控制组件执行服务函数*/
	PulseCtrl_Executing();
}













/* 

Timer01Callback01 function
定时器1的回调服务函数用于

*/
void Timer01Callback(void const * argument)
{
	static INT32U LoopTimes =0;

    LoopTimes ++;
	IndepKEY_ScanServer();	//按键扫描函数，注意该扫描间隔会引起用户体验感 注意设置扫描间隔

	
	if(SystemTick_ms -LCD_light_Ct >LCD_OFF_TICKS)	//长时间没有按键将不再刷屏
	{
		LCD_BL_OFF;
	}
	else
	{
		if(LoopTimes >=400)		//循环计数时间 400*5 =2000毫秒
		{
			LoopTimes =0;
			xSemaphoreGive(Display_Semaphore);
			LCD_BL_ON;
		}
		
	}


}



/*
Task01_F function 
实时时钟


*/
void Task01_F(void const * argument)
{
	INT32U Times =0;
	INT32U Times1 =0;
	INT32U Times2 =0;
	
	static INT16U RealySt = 0;
	RealySt =SysPara.RelayRecord;

	PowerRelay_SET(RealySt);			//主回路继电器动作控制
	createIWDG( &Iwdg_T1, 30);		    //软件看门狗创建

	

    while(1)
    {

		feedIWDG(Iwdg_T1);
		Times +=1;
		Times1 +=1;
		Times2 +=1;
		
        LED_RUN_Toggle;

		if(Times >=30)
		{
			Times =0;
			PCF8563_Read(&RTC_Time);										//RTC读取
			CalculateProvideTimeServer();									//供暖时间 以及供暖季的计算
			UpDateSysDevStatusErr();										//系统设备通信状态更新
			
			if(CalculateProvideTimeCtrler.PassData >3600l*24*60)		    //供暖时间结束2个月后进行供暖季的自行调整
			{
				SysPara.StartTime.Year +=1;
				SysPara.FinalTime.Year +=1;
				SysPara_Update();
			}
			/* 供暖季范围内的自动超收*/
			if(
				((CalculateProvideTimeCtrler.PassData <=3600l*24*30)&&( CalculateProvideTimeCtrler.PassData >=-3600l*24*30))	//供暖季后有效时间内
			)
			{
				CalculateProvideTimeCtrler.LoopWorkFlg =ENABLE;		
			}
			else
			{
				CalculateProvideTimeCtrler.LoopWorkFlg =DISABLE;
			}
        }
        else
		{
			RTC_TimeTicks +=1;
		}

		/*系统延时复位功能*/
        if( SysOnbootFlag ==1)
        {
        	
			dbg_printf(DEBUG_INFO,"重启倒计时 %lu...",RemoRebotCont-(SystemTick_ms -SysOnbootdelay)/1000);				
			if( SystemTick_ms -SysOnbootdelay >RemoRebotCont*1000ul)		//10秒的延时
			{
				SysOnbootFlag =0x00;
				NVIC_SystemReset();
			}
        }
        
        AlarmClk_ExecutServer();	//闹铃服务组件执行服务函数
        
		/*每10秒进行一次系统设备通信状态检查*/
		if(Times1 >=10)			
        {
        	Times1 =0;
			SysStatus.Dev_ComStatus = GetDev_ComStatus();
            //dbg_printf(DEBUG_INFO,"报警状态 = %d\r\n",SysStatus.Dev_ComStatus);
			if(SysStatus.Dev_ComStatus == HAL_OK)
			{
				LED_Alarm_OFF;
			}
			else
			{
				LED_Alarm_ON;
			}
        }

        
        /*每5秒进行一次设备故障状态检查*/
        if(Times2 >=5)			
		{
			Times2 =0;
            //dbg_printf(DEBUG_INFO,"故障状态 = %d\r\n", SysStatus.Syspara);
			if(SysStatus.Syspara == HAL_OK)
			{
				LED_Fault_OFF;
			}
			else
			{
				LED_Fault_ON;
			}
		}
		
		
        osDelay(1000);			//注意该延时时间不要随意修改 该任务涉及 RTC_TimeTicks的更新
    }
}





/* 
	Task02_F function
	脉冲控制
*/
void Task02_F(void const * argument)
{

	INT32U Times =0;
	INT32U TimeLed =0;

	
	createIWDG( &Iwdg_T2, 20);			 //软件看门狗创建
    while(1)
    {
		feedIWDG(Iwdg_T2);
    	Times++;
    	if( Times>=4)
    	{
    		Times =0;
	    	LED_COM1_OFF;
	    	LED_COM2_OFF;
	    	LED_COM3_OFF;
    	}


		TimeLed +=1;
		if( TimeLed >=60)
		{

			TimeLed =0;
			PulseLeaguer_SET(LedBR_Ctrler, 4, 10, 8, 16, 0, 0); 	//设置主板工作指示灯 重设
		}
    	osDelay(50);
	
    }
}





/* Task03_F function 
    按键扫描服务函数
*/
void Task03_F(void const * argument)
{

	BaseType_t Err;
	KEY_OUT_Stru value;
	KEY_OUT_Stru pi;
	IndepKEYFunction_Init();											//独立按键功能初始化
	KeyboardApp_Init();												    //按键应用初始化  IndepKEYFunction_Init 初始化被挂接后不用再次初始化

	osStatus TimerErr;
	TimerErr =TimerErr;

    /* Create the timer(s) */
    /* definition and creation of Timer01 */
    osTimerDef(Timer01, Timer01Callback);								//创建应用于按键扫描的定时器
    Timer01Handle = osTimerCreate(osTimer(Timer01), osTimerPeriodic, NULL);
    TimerErr =osTimerStart (Timer01Handle , 5 );	                    //定时器扫描间隔为5毫秒/Ticks

	Err =Err;
    while(1)
    {
        Err =xQueueReceive(KEY_OUT_Msg, &pi, portMAX_DELAY);
        if(Err ==pdTRUE)
        {
			value =pi;
			PulseLeaguer_SET(Beep_Ctrler, 1, 10, 5, 10, 0, 0); 	        //功能指针	脉冲数量  扫描间隔(tick*X) 边沿宽度   周期	  周期计数器  当前状态
			LCD_light_Ct =SystemTick_ms;					            //有按键按下时刷新背光控制器
			
			Keyvalue.value =value.Button_Num;
			Keyvalue.resp =1;
			Menu_KeyManager();
			xSemaphoreGive(Display_Semaphore);
        }
        
        osDelay(100);
    }
}







/* Task04_F function */
void Task04_F(void const * argument)
{

	LCD_IOInit();										        //LCD外设管脚初始化
	LCD_REST();										            //液晶复位
	
	Lcd_Init();											        //液晶驱动初始化
	Clear_VisionBUF();									        //清空显示缓冲区
	Refresh_Screen();									        //屏幕刷新
	BaseType_t Err=pdTRUE;
	
	if(Display_Semaphore !=NULL)
	{
		xSemaphoreGive(Display_Semaphore);
	}

	
	GetbuildMeterMessage();	 							        //获取栋表信息
    while(1)
    {
		Err =xSemaphoreTake(Display_Semaphore,portMAX_DELAY);	//等待屏幕刷新信号量
		if(Err ==pdTRUE)
		{
			DisplayManager();
			Refresh_Screen();
		}
    	osDelay(50);
	
    }
}






/* Task05_F function 
异步串行通信接收服务

*/
void Task05_F(void const * argument)
{

	createIWDG( &Iwdg_T5, 25);			 //软件看门狗创建
	while(1)
	{
		feedIWDG(Iwdg_T5);
		UART_RBC_RXServer();
		osDelay(50);
	}
}

/* Task06_F function
异步串行通信发送服务
*/
void Task06_F(void const * argument)
{
	createIWDG( &Iwdg_T6, 25);			 //软件看门狗创建
	while(1)
	{
		feedIWDG(Iwdg_T6);
		UART_RBC_TXServer();		    //异步串行通信发送服务
		osDelay(200);
	}
}


/* Task07_F function
异步串行通信服务打包  （采集器 数据打包）


协议打包
*/
void Task07_F(void const * argument)
{

	UART_TO_FY1000_QueueSend_Stru SendBuffer;
	if(FY_1000Send_Code_QInput(&SendBuffer,0XFE)==pdTRUE)
	{			
		dbg_printf(DEBUG_INFO,"主站重连注册申请....");
	}
	else
	{
		dbg_printf(DEBUG_INFO,"主站重连注册申请....");
	}
	createIWDG( &Iwdg_T7, 30);			                //软件看门狗创建


    while(1)
    {
		feedIWDG(Iwdg_T7);
		FY188_Pack_TxServer_S(UART_TO_FY188_CCB_S);		//FY-188打包服务

		FY2000_Pack_TxServer_S(UART_TO_FY2000_CCB_S);	//FY-2000打包服务
		FY1000_Pack_TxServer_S(UART_TO_FY1000_CCB_S);	//FY-1000打包服务

#ifdef Meter_H_ENABLE
		HZCRL_Pack_TxServer_S(UART_TO_HZCRL_CCB_S);		//汇中188打包服务
#endif

#ifdef  Meter_XY_ENABLE	        
		XY188_Pack_TxServer_S(UART_TO_XY188_CCB_S);		//XY-188打包服务
#endif

#ifdef  Meter_HT2X_ENABLE	        
        HT2X188_Pack_TxServer_S(UART_TO_HT2X188_CCB_S); //HT2X-188打包服务
#endif

#ifdef  Meter_BRC_ENABLE	        
        BRC188_Pack_TxServer_S(UART_TO_BRC188_CCB_S);   //BRC-188打包服务
#endif

#ifdef  Meter_DDF2_ENABLE	        
        DDF2_Pack_TxServer_S(UART_TO_DDF2_CCB_S);       //DDF2打包服务
#endif

#ifdef  Valve_NWK_ENABLE	        
        NWK_Pack_TxServer_S(UART_TO_NWK_CCB_S);         //NWK打包服务
        //dbg_printf(DEBUG_DEBUG,"--NWK--打包");
#endif
    	osDelay(500);
    }
}






/* Task08_F function
Client 通信通道1 发送服务  数据发送服务任务（采集器-->从机设备  采集器发送命令给设备）

*/


void Task08_F(void const * argument)
{
	BaseType_t Err;
	Err =Err;
	UBaseType_t Num =0;
	
	ClientReadCtrler.Num =0;
	SysDEV_Type DeviceType;
	ClientCH1_Queue_Stru DevQueue;
	UART_TO_FY188_QueueSend_Stru		FY188_QueueSend;        //声明热量表通信协议发送队列缓冲器
	UART_TO_FY2000_QueueSend_Stru	    FY2000_QueueSend;       //声明通断阀通信协议协议发送队列缓冲器

	
    
#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_QueueSend_Stru		HZCRL188_QueueSend;     //声明汇中188通信协议通信协议协议发送队列缓冲器
#endif
    
#ifdef  Meter_XY_ENABLE	 
	UART_TO_XY188_QueueSend_Stru		XY188_QueueSend;        //声明祥源热量表通信协议发送队列缓冲器
#endif    

#ifdef  Meter_HT2X_ENABLE	 
	UART_TO_HT2X188_QueueSend_Stru		HT2X188_QueueSend;      //声明海通HT2X热量表通信协议发送队列缓冲器
#endif  	

#ifdef  Meter_BRC_ENABLE	 
    UART_TO_BRC188_QueueSend_Stru       BRC188_QueueSend;       //声明贝特智联 BRC 热量表通信协议发送队列缓冲器
#endif 

#ifdef  Meter_DDF2_ENABLE	 
        UART_TO_DDF2_QueueSend_Stru     DDF2_QueueSend;         //海通通断阀通信协议发送队列缓冲器
#endif 

#ifdef  Valve_NWK_ENABLE	 
        UART_TO_NWK_QueueSend_Stru      NWK_QueueSend;          //耐威科modbus协议发送队列缓冲器
#endif 

	if(SysPara.LoopSpace <1000)
	{
		SysPara.LoopSpace =3000;
	}
	ClientCH1Ctrler.CreatFlag =HAL_OK;
	SysStatus.ShareFlag =HAL_ERROR;			//分摊标志复位

	createIWDG( &Iwdg_T8, 60);			    //软件看门狗创建

#if 0

    for(int i =8;i< 40;i++)
    {

    	SysDeviceList.Device[i].Type =Meter_HT3X;
    	SysDeviceList.Device[i].ID =0x05011768+i ;
    	SysDeviceList.Device[i].COM_Type =0x15 ;
    	SysDeviceList.Device[i].Num =i;
    	SysDeviceList.Device[i].UserNum =3;
	}
	
#endif
    while(1)
    {
		feedIWDG(Iwdg_T8);
    	if(ClientCH1Ctrler.Busy ==HAL_OK)                               //总线空闲 
    	{
			Num = uxQueueSpacesAvailable(ClientCH1_Msg);                //得到队列剩余大小
			if( (Num ==ClientCH1_Q_NUM)&&(SystemTick_ms -ClientReadCtrler.LoopSpace >SysPara.LoopSpace) )   //总线没有队列协议需要触发  同时检查循环抄收间隔计数器  此时可以触发自动超收设备序列
			{
				ClientCH1_QueueIN.Device=SysDeviceList.Device[ClientReadCtrler.Num];						//传递设备参数
				
				DeviceType =ClientCH1_QueueIN.Device.Type;		            								//获取设备类型

				
				ClientReadCtrler.Num +=1;
				if( ClientReadCtrler.Num >=MAXDevice_Num)               //循环限制
				{
					ClientReadCtrler.Num =0;
				}

				
				if( CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)    //自动轮超收有效
				{
					SysStatus.LoopCtrler +=1;
					if(SysStatus.LoopCtrler >=MAXDevice_Num)
					{
						SysStatus.ShareFlag =HAL_OK;
					}
					switch(DeviceType)      //选择设备类型
					{
						case Meter_B :      //大口径超声波热量表 FY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                  //获取设备编号
							ClientCH1_QueueIN.UaComFlg =0;										//协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							
							ClientCH1_QueueIN.SignleCom =SET;									//重复超收
							Err = FY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);             //队列填充	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    ERR ");
							}
							
						}break;
						


						case Meter_U ://用户超声波热量表 FY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;					//获取设备编号
							ClientCH1_QueueIN.UaComFlg =0;                                      //协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;									//重复超收
							Err = FY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);				//队列填充	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    ERR ");
							}							
						}break;

						case Valve_U ://户用通断控制器
						{
							INT16U UserNum =0;
							INT16U DevNum =0;
							
							UserNum =ClientCH1_QueueIN.Device.UserNum;                                                          //获取用户编号
							DevNum =ClientCH1_QueueIN.Device.Num;
							ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                                  //传递设备参数
							ClientCH1_QueueIN.UaComFlg =0;                                                                      //协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Head.DESN=ClientCH1_QueueIN.Device.Num;				//填入DESN
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LoopTime=CalculateProvideTimeCtrler.ProvideTime;		//周期供暖时间
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Apportion_Energy=UserData[UserNum].Apportion_Energy;	//填入周期热量/热量表表底
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Remain_Heat=UserData[UserNum].Remain_Heat;			//填入剩余热量
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Total_Heat=UserData[UserNum].Total_Heat;				//填入用户购入热量
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ControlType=SysDevData[DevNum].Device3.ControlType;   //填入控制类型
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ForceCtrlFlg=SysDevData[DevNum].Device3.ForceCtrlFlg; //填入强制控制标志
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_TCtrlFg=SysDevData[DevNum].Device3.Set_TCtrlFg;   //系统设定温度标志
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_Temp=SysDevData[DevNum].Device3.Set_Temp;			//系统设定温度

							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Flag=SysDevData[DevNum].Device3.LimtTE_Flag;   //系统极限温度标志
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Value=SysDevData[DevNum].Device3.LimtTE_Value; //系统极限设置温度
							ClientCH1_QueueIN.SignleCom =SET;
				 			Err =FY_2000Send_Code_QInput(&ClientCH1_QueueIN,59);										        //队列填充
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    ERR ");
							}
						}break;

						case Valve_UH ://户用通断控制器 回水阀用
						{
							INT16U UserNum =0;
							INT16U DevNum =0;
							
							UserNum =ClientCH1_QueueIN.Device.UserNum;												                //获取用户编号
							DevNum =ClientCH1_QueueIN.Device.Num;
							ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;											            //传递设备参数
							ClientCH1_QueueIN.UaComFlg =0;														                    //协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Head.DESN =DevNum;								        //填入DESN
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LoopTime =CalculateProvideTimeCtrler.ProvideTime;         //周期供暖时间
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Apportion_Energy =UserData[UserNum].Apportion_Energy;		//填入周期热量/热量表表底
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Remain_Heat =UserData[UserNum].Remain_Heat;			    //填入剩余热量
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Total_Heat =UserData[UserNum].Total_Heat;				    //填入总热量
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ControlType =SysDevData[DevNum].Device4.ControlType;		//填入控制类型
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ForceCtrlFlg =SysDevData[DevNum].Device4.ForceCtrlFlg;    //填入强制控制标志
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_TCtrlFg =0;		//系统设定温度标志
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_Temp =0;		    //系统设定温度

							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Flag =0;		//系统极限温度标志
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Value =0;		//系统极限设置温度
							ClientCH1_QueueIN.SignleCom =SET;
				 			Err =FY_2000Send_Code_QInput(&ClientCH1_QueueIN,59);		 	    //队列填充
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    ERR ");
							}
						}break;

#ifdef Meter_H_ENABLE
						case Meter_H ://汇中大口径超声波热量表 CJ-T188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                  //获取设备编号
							ClientCH1_QueueIN.UaComFlg =0;                                      //协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;									//重复超收
							Err = HZCRL_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);			//队列填充	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"HZCRL_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"HZCRL_188Send_Code_QInput    ERR ");
							}
						}break;					
#endif


#ifdef Meter_XY_ENABLE
						case Meter_XY ://祥源超声波热量表 XY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;									//获取设备编号
							ClientCH1_QueueIN.UaComFlg =0;													    //协议返回 标志复位
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;													//重复超收
							Err = XY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);								//队列填充	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"XY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"XY_188Send_Code_QInput    ERR ");
							}							
						}break;
#endif

#ifdef Meter_HT2X_ENABLE
                        case Meter_HT2X ://海通超声波热量表 HT2X-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //获取设备编号
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //协议返回 标志复位
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //重复超收
                            Err = HT2X_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                           //队列填充  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"HT2X_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"HT2X_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
                        
                        case Meter_HT3X ://海通超声波热量表 HT2X-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //获取设备编号
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //协议返回 标志复位
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //重复超收
                            Err = HT2X_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                           //队列填充  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"HT3X_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"HT3X_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Meter_BRC_ENABLE
                        case Meter_BRC ://海通超声波热量表 BRC-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //获取设备编号
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //协议返回 标志复位
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //重复超收
                            Err = BRC_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                            //队列填充  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"BRC_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"BRC_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Meter_DDF2_ENABLE
                        case Meter_DDF2 ://海通通断控制器DDF2
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //获取设备编号
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //协议返回 标志复位
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //重复超收
                            Err = DDF2_Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                              //队列填充  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"DDF2_Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"DDF2_Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Valve_NWK_ENABLE
                        case Valve_NWK ://NWK耐威科楼栋单元调节阀modbus协议
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //获取设备编号
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //协议返回 标志复位
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //重复超收
                            Err = NWK_Send_Code_QInput(&ClientCH1_QueueIN, 0X03);                               //队列填充  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG, "NWK_Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG, "NWK_Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

						default: break;
					}
				}
			}
			else    //有终端超收协议触发  需要将缓冲协议进行分发
			{
                Err =xQueueReceive(ClientCH1_Msg, &ClientCH1_QueueBFP, 20);
                if(Err ==pdTRUE)
                {   
                	INT16U DevNum =0;
					INT8U DevType =0;
					
					ClientCH1_QueueBF =*ClientCH1_QueueBFP;
					
                    ClientCH1Ctrler.Device =ClientCH1_QueueBF.Device;       		    //数据移交   将队列数据移交给通道控制器  
					ClientCH1Ctrler.SignleCom =ClientCH1_QueueBF.SignleCom;			    //传递重复超收次数命令
					ClientCH1Ctrler.UaComFlg =ClientCH1_QueueBF.UaComFlg;			    //传递协议标志
					ClientCH1Ctrler.Uapack=ClientCH1_QueueBF.Uapack;
					
					ClientCH1Ctrler.PackCreatFlag=ClientCH1_QueueBF.PackCreatFlag;		//传递协议触发控制标志
					ClientCH1Ctrler.PackINPort=ClientCH1_QueueBF.PackINPort;			//传递协议入口序号
					ClientCH1Ctrler.SendData=ClientCH1_QueueBF.SendData;    			//发送协议有效数据区  
					
					
					DevType	=ClientCH1Ctrler.Device.Type;				
                    DevNum =ClientCH1Ctrler.Device.Num;
                    
                    if(ClientCH1Ctrler.SignleCom ==SET)
                    {
                    	switch(DevType)	//对抄收设备对象的通信状态累加
	                    {
							case Meter_B:	//FY-188大口径表
							{
								SysDevStatus[DevNum].Device1.ComTolNum +=1;

							}break;
							
							case Meter_U:   //FY-188小口径表
							{
								SysDevStatus[DevNum].Device2.ComTolNum +=1;

							}break;		

							case Valve_U:	//FY-2100通断控制器 
							{
								SysDevStatus[DevNum].Device3.ComTolNum +=1;

							}break;	
							case Valve_UH:
							{		
								SysDevStatus[DevNum].Device4.ComTolNum +=1;
						
							}break;
#ifdef Meter_H_ENABLE
							case Meter_H:   //汇中 CJ-T188 大口径表
							{
								SysDevStatus[DevNum].Device5.ComTolNum +=1;

							}break;	
#endif

                            
#ifdef  Meter_XY_ENABLE
							case Meter_XY: //祥源 XY-188小口径表
							{
								SysDevStatus[DevNum].Device6.ComTolNum +=1;

							}break;	
#endif


#ifdef  Meter_HT2X_ENABLE
                            case Meter_HT2X: //海通 HT2X-188小口径表
                            {
                                SysDevStatus[DevNum].Device7.ComTolNum +=1;

                            }break; 
                            
                            case Meter_HT3X: //海通 HT2X-188小口径表
                            {
                                SysDevStatus[DevNum].Device10.ComTolNum +=1;

                            }break; 
#endif


#ifdef  Meter_BRC_ENABLE
                            case Meter_BRC: //贝特智联 BRC-188小口径表
                            {
                                SysDevStatus[DevNum].Device8.ComTolNum +=1;

                            }break; 
#endif

#ifdef  Meter_DDF2_ENABLE
                            case Meter_DDF2: ////海通 DDF2通断控制器
                            {
                                SysDevStatus[DevNum].Device9.ComTolNum +=1;

                            }break; 
#endif		
                            
#ifdef  Valve_NWK_ENABLE
                            case Valve_NWK: ////耐威科NWK楼栋调节阀modbus协议
                            {
                                SysDevStatus[DevNum].Device11.ComTolNum +=1;

                            }break; 
#endif	
							default :break;
	                    }
                    }
                    
					ClientCH1Ctrler.Busy =HAL_BUSY;
                    ClientCH1Ctrler.Repeat =0;
                 
                }
			}
    	}
    	
    	if(( ClientCH1Ctrler.Busy ==HAL_BUSY)&&(ClientCH1Ctrler.CreatFlag ==HAL_OK))   //总线处于占用状态 将会对不进行回复的终端设备进行重复抄收
    	{
    		DevQueue.Device.Type =ClientCH1Ctrler.Device.Type;
            switch(DevQueue.Device.Type)
            {
            	case Meter_B ://大口径超声波热量表
				{
					
					FY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //传递设备编号ID
					FY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//传递协议创建触发标志
					FY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //传递协议入口序号
					FY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //传递协议数据
					
					Err =UART_TO_FY188_CCB_QueueSend(&FY188_QueueSend);		        //发送消息
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY188_CCB_QueueSend    OK ");
					}
				}break;

            	case Meter_U ://户用超声波热量表
				{
				
					FY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //传递设备编号ID
					FY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//传递协议创建触发标志
					FY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //传递协议入口序号
					FY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //传递协议数据

					Err =UART_TO_FY188_CCB_QueueSend(&FY188_QueueSend);		        //发送消息
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY188_CCB_QueueSend    OK ");
					}
					
				}break;	
				

            	case Valve_U ://户用通断控制器 标准型
				{

					FY2000_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //传递设备编号ID
					FY2000_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//传递协议创建触发标志
					FY2000_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		//传递协议入口序号
				
					FY2000_QueueSend.SendData =ClientCH1Ctrler.SendData;			//传递协议数据

					Err =UART_TO_FY2000_CCB_QueueSend(&FY2000_QueueSend);		    //发送消息
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY2000_CCB_QueueSend    OK ");
					}
				}break;	


				

            	case Valve_UH ://户用通断控制器 回水阀
				{

					FY2000_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //传递设备编号ID
					FY2000_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//传递协议创建触发标志
					FY2000_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		//传递协议入口序号
					FY2000_QueueSend.SendData =ClientCH1Ctrler.SendData;			//传递协议数据

					Err =UART_TO_FY2000_CCB_QueueSend(&FY2000_QueueSend);		    //发送消息
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY2000_CCB_QueueSend    OK ");
					}
				}break;	

				
#ifdef Meter_H_ENABLE
                case Meter_H ://汇中超声波热量表 大口径
                {
                
                    HZCRL188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                       //传递设备编号ID
                    HZCRL188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;        //传递协议创建触发标志
                    HZCRL188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;              //传递协议入口序号
                    HZCRL188_QueueSend.SendData =ClientCH1Ctrler.SendData;                  //传递协议数据

                    Err =UART_TO_HZCRL_CCB_QueueSend(&HZCRL188_QueueSend);                  //发送消息
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_HZCRL_CCB_QueueSend    OK ");
                    }
                    
                }break;     
#endif




#ifdef  Meter_XY_ENABLE                
            	case Meter_XY ://祥源超声波热量表
				{
				
					XY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //传递设备编号ID
					XY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//传递协议创建触发标志
					XY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //传递协议入口序号
					XY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //传递协议数据

					Err =UART_TO_XY188_CCB_QueueSend(&XY188_QueueSend);		        //发送消息
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_XY188_CCB_QueueSend    OK ");
					}
					
				}break;
#endif				

#ifdef  Meter_HT2X_ENABLE                
                case Meter_HT2X ://祥源超声波热量表
                case Meter_HT3X ://祥源超声波热量表
                {
                
                    HT2X188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                    //传递设备编号ID
                    HT2X188_QueueSend.Type =ClientCH1Ctrler.Device.Type;                //传递设备类型 该型号表对应 
                    HT2X188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;     //传递协议创建触发标志
                    HT2X188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;           //传递协议入口序号
                    HT2X188_QueueSend.SendData =ClientCH1Ctrler.SendData;               //传递协议数据

                    Err =UART_TO_HT2X188_CCB_QueueSend(&HT2X188_QueueSend);             //发送消息
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        if(DevQueue.Device.Type == Meter_HT2X )
                        {
                            dbg_printf(DEBUG_DEBUG,"UART_TO_HT2X188_CCB_QueueSend    OK ");
                        }
                        else if(DevQueue.Device.Type == Meter_HT3X )
                        {
                            dbg_printf(DEBUG_DEBUG,"UART_TO_HT3X188_CCB_QueueSend    OK ");
                        }
                        
                    }
                    
                }break;
#endif	

#ifdef  Meter_BRC_ENABLE                
                case Meter_BRC ://祥源超声波热量表
                {
                
                    BRC188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                  //传递设备编号ID
                    BRC188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;   //传递协议创建触发标志
                    BRC188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;         //传递协议入口序号
                    BRC188_QueueSend.SendData =ClientCH1Ctrler.SendData;             //传递协议数据

                    Err =UART_TO_BRC188_CCB_QueueSend(&BRC188_QueueSend);            //发送消息
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_BRC188_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

#ifdef  Meter_DDF2_ENABLE                
                case Meter_DDF2 ://海通通断控制器DDF2
                {
                
                    DDF2_QueueSend.ID =ClientCH1Ctrler.Device.ID;                  //传递设备编号ID
                    DDF2_QueueSend.COM_Type =ClientCH1Ctrler.Device.COM_Type;            
                    DDF2_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;   //传递协议创建触发标志
                    DDF2_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;         //传递协议入口序号
                    DDF2_QueueSend.SendData =ClientCH1Ctrler.SendData;             //传递协议数据

                    Err =UART_TO_DDF2_CCB_QueueSend(&DDF2_QueueSend);              //发送消息
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_DDF2_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

#ifdef  Valve_NWK_ENABLE                
                case Valve_NWK ://耐威科NWK
                {
                
                    NWK_QueueSend.ID                = ClientCH1Ctrler.Device.ID;            //传递设备编号ID
                    //NWK_QueueSend.COM_Type          = ClientCH1Ctrler.Device.COM_Type;            
                    NWK_QueueSend.PackCreatFlag     = ClientCH1Ctrler.PackCreatFlag;        //传递协议创建触发标志
                    NWK_QueueSend.PackINPort        = ClientCH1Ctrler.PackINPort;           //传递协议入口序号
                    NWK_QueueSend.SendData          = ClientCH1Ctrler.SendData;             //传递协议数据

                    Err =UART_TO_NWK_CCB_QueueSend(&NWK_QueueSend);                         //发送消息
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_NWK_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

				default :break;
            }
    	}
    	osDelay(200);
    }
}







/* Task09_F function
Client 通信通道1 总线控制服务     
*/
void Task09_F(void const * argument)
{
	BaseType_t err;
	err =err;

	if(( SysPara.ReadSpace<2000)||(SysPara.ReadSpace>1000*60*10))
	{
		SysPara.ReadSpace =3000;

	}
	createIWDG( &Iwdg_T9, 35);			 //软件看门狗创建

    while(1)
    {
		feedIWDG(Iwdg_T9);
    	if(ClientCH1Ctrler.Busy ==HAL_BUSY)		//通道占用状态监测
    	{
    		if( SystemTick_ms -ClientCH1Ctrler.Ticks >SysPara.ReadSpace)
    		{
    			ClientCH1Ctrler.CreatFlag =HAL_OK;
    			if(ClientCH1Ctrler.SignleCom ==SET)	//需要重复超收
    			{
					if(ClientCH1Ctrler.RetFlag ==HAL_OK)
					{
						ClientCH1Ctrler.Busy =HAL_OK;
						ClientCH1Ctrler.CreatFlag =HAL_OK;
						ClientReadCtrler.LoopSpace =SystemTick_ms;
					}
					else if( ClientCH1Ctrler.Repeat >=ClientRepeatNum)	//抄收失败
					{	
						UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
						INT16U DevNum =ClientCH1Ctrler.Device.Num;
						INT8U DevType =ClientCH1Ctrler.Device.Type;
						
						switch(DevType)
						{
							case Meter_B:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_B;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device1.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
                                       dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...楼栋热量表",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									case 0XAAAA: //远程抄收
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_B;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device1.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
                                        dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...楼栋热量表", DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									default:break;
								}
								
							}break;
							
							case Meter_U:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_U;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device2.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //远程抄收
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_U;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device2.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
										dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

									}break;
									default:break;
								}	
							}break;
							
							case Valve_U:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_U;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device3.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //远程抄收/控制
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //终端数据抄收
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_U;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device3.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
                                                dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                        DevType, ClientCH1Ctrler.Device.ID,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://阀门动作控制
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_U;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);
												dbg_printf(DEBUG_WARNING,"远程 控制失败 0X0D，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                        DevType, ClientCH1Ctrler.Device.ID,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
											}break;
										}
									}break;
										
								}
							}break;	
							
							case Valve_UH:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_UH;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device4.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //远程抄收/控制
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //终端数据抄收
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_UH;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device4.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                    DevType, ClientCH1Ctrler.Device.ID,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://阀门动作控制
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_UH;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"远程 控制失败 0X0D，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                    DevType, ClientCH1Ctrler.Device.ID,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
												
											}break;
										}
									}break;	
								}
							}break;	

							
#ifdef Meter_H_ENABLE
							case Meter_H:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_H;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device5.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);										
                                        dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...楼栋热量表",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									
									case 0XAAAA: //远程抄收
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_H;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device5.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);										
                                        dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...楼栋热量表", DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									default:break;
								}							
							}break;	
#endif



#ifdef  Meter_XY_ENABLE							
							case Meter_XY:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_XY;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device6.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);										
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //远程抄收
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_XY;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device6.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);										
										dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                 DevType, ClientCH1Ctrler.Device.ID,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									default:break;
								}							
							}break;
#endif                        

                            
#ifdef  Meter_HT2X_ENABLE							
                            case Meter_HT2X:
                            case Meter_HT3X:
                            {
                                switch(ClientCH1Ctrler.UaComFlg)
                                {
                                    case 0: //自动抄收  
                                    {
                                        SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =DevType;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device6.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device7.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device7.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device7.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);                                     
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    
                                    case 0XAAAA: //远程抄收
                                    {
                                        SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =DevType;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device6.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device7.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device7.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device7.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);                                     
                                        dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                 DevType, ClientCH1Ctrler.Device.ID,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    default:break;
                                }                           
                            }break;
#endif                        

                                                        
#ifdef  Meter_BRC_ENABLE							
                            case Meter_BRC:
                            {
                                switch(ClientCH1Ctrler.UaComFlg)
                                {
                                    case 0: //自动抄收  
                                    {
                                        SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_BRC;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device8.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device8.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device8.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device8.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);                                     
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    
                                    case 0XAAAA: //远程抄收
                                    {
                                        SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_BRC;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device8.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device8.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device8.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device8.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);                                     
                                        dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                             DevType, ClientCH1Ctrler.Device.ID,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    default:break;
                                }                           
                            }break;
#endif       

#ifdef  Meter_DDF2_ENABLE

							case Meter_DDF2:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_DDF2;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device4.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device9.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device9.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device9.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //远程抄收/控制
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //终端数据抄收
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_DDF2;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device9.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device9.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device9.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device9.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                     DevType, ClientCH1Ctrler.Device.ID,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://阀门动作控制
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Meter_DDF2;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"远程 控制失败 0X0D，类型:%d 编号:%08lX...位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                     DevType, ClientCH1Ctrler.Device.ID,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
												
											}break;
										}
									}break;	
								}
							}break;	
#endif

#ifdef  Valve_NWK_ENABLE
							case Valve_NWK:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//自动抄收  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_NWK;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;//COMBack_CE = 0x03。 0x02:抄收成功，0x03:设备通信异常
										
										SysDevStatus[DevNum].Device11.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device11.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device11.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device11.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
                                        dbg_printf(DEBUG_WARNING,"自动 抄收失败，类型:%d 编号:%08lX...楼栋单元调节阀",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									
									case 0XAAAA: //远程抄收/控制
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //终端数据抄收
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_NWK;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device11.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device11.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device11.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device11.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"远程 抄收失败 0X01，类型:%d 编号:%08lX...楼栋单元调节阀", DevType, ClientCH1Ctrler.Device.ID);

											}break;
											case 0X0D://阀门动作控制
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_NWK;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"远程 控制失败 0X0D，类型:%d 编号:%08lX...楼栋单元调节阀", DevType, ClientCH1Ctrler.Device.ID);
												
											}break;
										}
									}break;	
								}
							}break;	
#endif

							default:break;

						}
						
						ClientCH1Ctrler.Busy =HAL_OK;
						ClientCH1Ctrler.CreatFlag =HAL_OK;
						ClientReadCtrler.LoopSpace =SystemTick_ms;
						
					}
					else
					{
						ClientCH1Ctrler.CreatFlag =HAL_OK;
					}
				}
				else		//不需要重复超收 广播命令  或者终端数据已经返回
				{
				
					ClientCH1Ctrler.Busy =HAL_OK;
					ClientCH1Ctrler.CreatFlag =HAL_OK;
					ClientReadCtrler.LoopSpace =SystemTick_ms;
				}
    		}
    	}
    	osDelay(200);
    }
}









/* Task10_F function
Client 通信通道1 设备广播对时触发控制
*/
void Task10_F(void const * argument)
{

	INT32U Time2 =0;

	HbInit();//心跳管理模块初始化
	createIWDG( &Iwdg_T10, 60);			 //软件看门狗创建

	while(1)
	{
		feedIWDG(Iwdg_T10);
        
		/* 心跳管理 */
		HbMainTask();
		
		/*通断控制器广播对时*/
		Time2 +=1;
		if( Time2>=60)  //300秒广播对时触发一次
		{
			Time2 =0;
			ClientCH1_Queue_Stru	DATAIN;
            
			DATAIN.Device.Type  = Valve_U;				//填充设备类型
			DATAIN.Device.ID    = 0XAAAAAAAA;				
			DATAIN.Device.Num   = 0;						
			DATAIN.SignleCom    = RESET;			    //不需要从机返回
            
			FY_2000Send_Code_QInput(&DATAIN,50);
		}
        
		osDelay(1000*5);
	}
}



/* Task11_F function 周期测试任务预留
void Task11_F(void const * argument)
{
	BaseType_t err;
	err =err;
	INT32U Time1 =0;

    while(1)
    {
		Time1 +=1;
		if( Time1>=5)	
		{
			Time1 =0;

			
		}
    	osDelay(1000*60);

    	
    }
}
*/


/*
Task12_F function   
用户数据定时上报任务 
*/
void Task12_F(void const * argument)
{
	BaseType_t Err;
//	UART_TO_FY1000_QueueSend_Stru SendBuffer;


	/**
	用户能量分摊以及定时上报闹铃触发事件
	闹铃创建 
	@使能 禁止	 
	@回调函数	
	@周期触发使能
	@循环时间  XX(分钟)
	**/

	/* 系统最小分摊周期限定*/
	if(SysStatus.Syspara ==HAL_OK)
	{
		if(SysPara.Apportion_T <10)
		{
			SysPara.Apportion_T =10;
		}
	
	}
	else
	{
		SysPara.Apportion_T =120;
	}
	
	Alarm_UserShare = AlarmClk_CreatOne( AlarmClk_Disable,Alarm_UserShare_CallBack,AlarmClk_Enable,SysPara.Apportion_T);
	AlarmTime.Year = 2017; 
	AlarmTime.Month = 10;
	AlarmTime.Day = 15;
	AlarmTime.Hour = 00;
	AlarmTime.Minute = 00;
	AlarmTime.Second = 00;
	AlarmClk_ParaSet(Alarm_UserShare,&AlarmTime);
	AlarmClk_EnableCtrl(Alarm_UserShare,AlarmClk_Enable);


	while(1)
	{
		if(UseSend_Semaphore !=NULL)	//信号量有效性判断
		{
			Err =xSemaphoreTake(UseSend_Semaphore,portMAX_DELAY);	//等待用户数据分摊信号量
			if(Err ==pdTRUE)
			{
				for(INT16U UserNum =0;UserNum <SysPara.UserNum;UserNum +=1)
				{
					if( UserData_Save(UserNum) ==HAL_OK)
					{
                        dbg_printf(DEBUG_INFO,"用户数据保存成功 序号:%d    用户主键:%08lX    DeviceID:%08lX", UserNum, SysUserList.User[UserNum].User_ID, ClientCH1Ctrler.Device.ID);
                        //dbg_printf(DEBUG_INFO,"用户数据保存成功 序号:%d    用户主键:%08lX    DeviceID:%08lX---位置信息 %02d号楼-%d单元-%02d层-%02d室",\
                                                                                UserNum, SysUserList.User[UserNum].User_ID, ClientCH1Ctrler.Device.ID,\
                                                                                SysUserList.User[UserNum].Buld,\
                                                                                SysUserList.User[UserNum].Unit,\
                                                                                SysUserList.User[UserNum].Floor,\
                                                                                SysUserList.User[UserNum].Cell);
					}

					//取消用户数据的上传功能  2017年11月10日
/*					SendBuffer.SendData.Pack_0X84.UaComFlg =0;
					SendBuffer.SendData.Pack_0X84.UserID =SysUserList.User[UserNum].User_ID;
					SendBuffer.SendData.Pack_0X84.RemainHeat =UserData[UserNum].Remain_Heat;
					SendBuffer.SendData.Pack_0X84.Total_Heat =UserData[UserNum].Total_Heat;
					SendBuffer.SendData.Pack_0X84.Apportion_Energy =UserData[UserNum].Apportion_Energy;
					SendBuffer.SendData.Pack_0X84.Total_Time =UserData[UserNum].Total_Time;
					Err =FY_1000Send_Code_QInput(&SendBuffer,0X84);
*/


					osDelay(1000*10);
					
				}
			}
		}
		osDelay(1000*20);
	}
}









/*
Task13_F function   
设备数据间隔上报任务  自动上报任务（采集器-->服务器  采集器返回抄收到的数据打包为丰源采集器协议上报到服务器）
*/
void Task13_F(void const * argument)
{

	SysDevPara		Device;
	SysDEV_Type	DeviceType;
	UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
	ClientSendCtrler.Num =0;
	INT16U DevNum =0;

	if(SysPara.SendSpace <5000)		//最小上报间隔限制
	{
		SysPara.SendSpace =5000;
	}
	osDelay(1000*60);				//上电延时1分钟

	while(1)
	{

		if( CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)//自动轮超收有效
		{
			if(SysPara.SendMode ==DevSendMode_Loop)								//数据上报类型确认
			{
				Device=SysDeviceList.Device[ClientSendCtrler.Num];				//传递设备参数
				DeviceType =Device.Type;
				DevNum =ClientSendCtrler.Num;
				switch(DeviceType)
				{
					case Meter_B ://大口径超声波热量表 FY-188
					{
						//通信状态判断
						if( (SysDevStatus[DevNum].Device1.ComTolNum !=0)&&(SysDevStatus[DevNum].Device1.ComSucNum !=0)&&(SysDevStatus[DevNum].Device1.ComFauNum ==0) )
						{
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_Type =Meter_B;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Input_Temp =SysDevData[DevNum].Device1.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Output_Temp =SysDevData[DevNum].Device1.Output_Temp;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current =SysDevData[DevNum].Device1.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit =SysDevData[DevNum].Device1.Instant_Current_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy =SysDevData[DevNum].Device1.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit =SysDevData[DevNum].Device1.Instant_Energy_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current =SysDevData[DevNum].Device1.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit =SysDevData[DevNum].Device1.Total_Current_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code =SysDevData[DevNum].Device1.Total_Code;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit =SysDevData[DevNum].Device1.Total_Code_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy =SysDevData[DevNum].Device1.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit =SysDevData[DevNum].Device1.Total_Energy_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Work_Time =SysDevData[DevNum].Device1.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE1 =SysDevData[DevNum].Device1.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE2 =SysDevData[DevNum].Device1.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID);
							}
							osDelay(SysPara.SendSpace);
						}
					}break;




					case Meter_U ://用户超声波热量表 FY-188
					{
						//通信状态判断
						if( (SysDevStatus[DevNum].Device2.ComTolNum !=0)&&(SysDevStatus[DevNum].Device2.ComSucNum !=0)&&(SysDevStatus[DevNum].Device2.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;

							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device2.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device2.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device2.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device2.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device2.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device2.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device2.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device2.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =SysDevData[DevNum].Device2.Total_Code;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =SysDevData[DevNum].Device2.Total_Code_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device2.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device2.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device2.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device2.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device2.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}
					}break;
					
					case Valve_U ://户用通断控制器
					{
						if( (SysDevStatus[DevNum].Device3.ComTolNum !=0)&&(SysDevStatus[DevNum].Device3.ComSucNum !=0)&&(SysDevStatus[DevNum].Device3.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_Type =Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.BackFlag =COMBack_OK;
							
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Set_Temp =SysDevData[DevNum].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cur_Temp =SysDevData[DevNum].Device3.Cur_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Ave_Temp =SysDevData[DevNum].Device3.Ave_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Input_Temp =SysDevData[DevNum].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Output_Temp =SysDevData[DevNum].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ValvePosition =SysDevData[DevNum].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpTim =SysDevData[DevNum].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Apportion_Energy =SysDevData[DevNum].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Face_State =SysDevData[DevNum].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Valve_State =SysDevData[DevNum].Device3.Valve_State;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID);
							}
							osDelay(SysPara.SendSpace);
						}

					}break;

					case Valve_UH ://户用通断控制器 回水阀用
					{
						if( (SysDevStatus[DevNum].Device4.ComTolNum !=0)&&(SysDevStatus[DevNum].Device4.ComSucNum !=0)&&(SysDevStatus[DevNum].Device4.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type =Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DevNum].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =SysDevData[DevNum].Device4.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DevNum].Device4.Valve_State;

						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;

#ifdef Meter_H_ENABLE					
					case Meter_H ://汇中大口径超声波热量表 CJ-T188
					{
						if( (SysDevStatus[DevNum].Device5.ComTolNum !=0)&&(SysDevStatus[DevNum].Device5.ComSucNum !=0)&&(SysDevStatus[DevNum].Device5.ComFauNum ==0) )
						{
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_Type =Meter_H;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.BackFlag =COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Input_Temp =SysDevData[DevNum].Device5.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Output_Temp =SysDevData[DevNum].Device5.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current =SysDevData[DevNum].Device5.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit =SysDevData[DevNum].Device5.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy =SysDevData[DevNum].Device5.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit =SysDevData[DevNum].Device5.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current =SysDevData[DevNum].Device5.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit =SysDevData[DevNum].Device5.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code =SysDevData[DevNum].Device5.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit =SysDevData[DevNum].Device5.Total_Code_Unit =MW_h;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy =SysDevData[DevNum].Device5.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit =SysDevData[DevNum].Device5.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Work_Time =SysDevData[DevNum].Device5.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE1 =SysDevData[DevNum].Device5.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE2 =SysDevData[DevNum].Device5.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}


					}break;
#endif					

					
#ifdef  Meter_XY_ENABLE	
					case Meter_XY ://用户超声波热量表 XY-188
					{
						//通信状态判断
						if( (SysDevStatus[DevNum].Device6.ComTolNum !=0)&&(SysDevStatus[DevNum].Device6.ComSucNum !=0)&&(SysDevStatus[DevNum].Device6.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_XY;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device6.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device6.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device6.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device6.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device6.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device6.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device6.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device6.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device6.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device6.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device6.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device6.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device6.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
						
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}
					}break;
#endif

#ifdef  Meter_HT2X_ENABLE	
                    case Meter_HT2X ://用户超声波热量表 HT2X
                    case Meter_HT3X ://用户超声波热量表 HT3X
                    {
                        //通信状态判断
                        if( (SysDevStatus[DevNum].Device7.ComTolNum !=0)&&(SysDevStatus[DevNum].Device7.ComSucNum !=0)&&(SysDevStatus[DevNum].Device7.ComFauNum ==0) )
                        {
                        
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =DeviceType;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device7.Input_Temp;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device7.Output_Temp;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device7.Instant_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device7.Instant_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device7.Instant_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device7.Instant_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device7.Total_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device7.Total_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device7.Total_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device7.Total_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device7.Work_Time;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device7.STATE1;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device7.STATE2;
                            
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
                        
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
                            }
                            osDelay(SysPara.SendSpace);

                        }
                    }break;
#endif

#ifdef  Meter_BRC_ENABLE	
                    case Meter_BRC ://用户超声波热量表 BRC
                    {
                        //通信状态判断
                        if( (SysDevStatus[DevNum].Device8.ComTolNum !=0)&&(SysDevStatus[DevNum].Device8.ComSucNum !=0)&&(SysDevStatus[DevNum].Device8.ComFauNum ==0) )
                        {
                        
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_BRC;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device8.Input_Temp;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device8.Output_Temp;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device8.Instant_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device8.Instant_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device8.Instant_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device8.Instant_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device8.Total_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device8.Total_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device8.Total_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device8.Total_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device8.Work_Time;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device8.STATE1;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device8.STATE2;
                              
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
                            }
                            osDelay(SysPara.SendSpace);

                        }
                    }break;
#endif


#ifdef Meter_DDF2_ENABLE
					case Meter_DDF2 ://户用通断控制器 回水阀用
					{
						if( (SysDevStatus[DevNum].Device9.ComTolNum !=0)&&(SysDevStatus[DevNum].Device9.ComSucNum !=0)&&(SysDevStatus[DevNum].Device9.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type =Meter_DDF2;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DevNum].Device9.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =0;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;
					
#endif	
                    
#ifdef Valve_NWK_ENABLE
					case Valve_NWK ://耐威科楼栋单元调节阀modbus协议
					{
						if( (SysDevStatus[DevNum].Device11.ComTolNum !=0)&&(SysDevStatus[DevNum].Device11.ComSucNum !=0)&&(SysDevStatus[DevNum].Device11.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.CtrlFlag               = 0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dev_Type               = Valve_NWK;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dev_ID                 = Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.BackFlag               = COMBack_OK;

                            //数据域  //bytes_reverse( (unsigned char *)&temp, 2); 数据小端模式 字节倒序
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Input_Temp             = (UINT16)(SysDevData[DevNum].Device11.Input_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Output_Temp            = (UINT16)(SysDevData[DevNum].Device11.Output_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.EnterWater_Pressure    = (UINT16)(SysDevData[DevNum].Device11.EnterWater_Pressure*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure   = (UINT16)(SysDevData[DevNum].Device11.ReturnWater_Pressure*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Room_Temp              = (UINT16)(SysDevData[DevNum].Device11.Room_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Current_Valve_Open     = (UINT16)(SysDevData[DevNum].Device11.Current_Valve_Open*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.SetValue_Open          = (UINT16)(SysDevData[DevNum].Device11.SetValue_Open*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Temp_Diff              = (UINT16)(SysDevData[DevNum].Device11.Temp_Diff*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.ReturnTemp_Set         = (UINT16)(SysDevData[DevNum].Device11.ReturnTemp_Set*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.PressureDiff_Set       = (UINT16)(SysDevData[DevNum].Device11.PressureDiff_Set*100);
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Error                  = SysDevData[DevNum].Device11.Error;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Software_Version       = SysDevData[DevNum].Device11.Software_Version;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Run_Mode               = SysDevData[DevNum].Device11.Run_Mode;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Address                = SysDevData[DevNum].Device11.Address;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Motor_Steering         = SysDevData[DevNum].Device11.Motor_Steering;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Adjust_Switch          = SysDevData[DevNum].Device11.Adjust_Switch;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Adjust_Tigger          = SysDevData[DevNum].Device11.Adjust_Tigger;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed         = SysDevData[DevNum].Device11.Dc_Motor_Speed;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"设备数据循环发送  编号: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;
					
#endif	
					default: break;
				}
				
				ClientSendCtrler.Num +=1;
				if( ClientSendCtrler.Num >=MAXDevice_Num) //循环限制
				{
					ClientSendCtrler.Num =0;
				}
			}
		}
		osDelay(500);
	}
}






/*
	//定义历史数据保存闹铃触发回调函数
*/
void Alarm_DataSave_CallBack(void)
{
	RealClock_Str real;
	getRealTime(&RTC_TimeTicks,&real);
	dbg_printf(DEBUG_INFO,"历史数据保存闹铃触发:%d-%02d-%02d-%02d:%02d:%02d",real.Year,real.Month,real.Day,real.Hour,real.Minute,real.Second);
	SaveLog();		//历史数据保存服务函数
}







/*
//定义用户数据定时分摊闹铃触发回调函数
*/
void Alarm_UserShare_CallBack(void)
{
	if(CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)		//时间日期合适
	{
		if( SysPara.DeviceType ==Type_Valve)	//通断时间面积法计量系统
		{
			if(SysStatus.ShareFlag ==HAL_OK)		//判断是否已经轮训完成
			{
			
			//	if(SysStatus.Dev_ComStatus ==HAL_OK)
				if(1)
				{
					dbg_printf(DEBUG_INFO,"通断时间面积法热计量系统，即将计算分摊热量...");
					SystemEnergyValue_Cal();		//通断时间 能量分摊计算
					dbg_printf(DEBUG_INFO,"热量分摊完成...");
				}
				else
				{
					dbg_printf(DEBUG_INFO,"系统设备通信异常，取消本次分摊...");
				}
			}
			else
			{
				dbg_printf(DEBUG_INFO,"系统数据获取中,等待下次分摊...");
			}
		}
		if(UseSend_Semaphore !=NULL)	//信号量有效性判断
		{
			dbg_printf(DEBUG_INFO,"用户数据定时上报闹铃触发：%d",RTC_TimeTicks);
			xSemaphoreGive(UseSend_Semaphore);
		}
	}
}


















/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1) 
    {
    }
    /* USER CODE END Error_Handler_Debug */ 
}













/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: dbg_printf("Wrong parameters value: file %s on line %d", file, line) */
  /* USER CODE END 6 */
 dbg_printf(DEBUG_EMERG,"Wrong parameters value: file %s on line %d", file, line);

}



















/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
