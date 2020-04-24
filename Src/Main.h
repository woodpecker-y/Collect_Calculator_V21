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
  * @author :ÐíÎ°
  * @date :2017/8/23 17:24
  ***************************************************************
  */ 
#ifndef _MAIN_H_
#define _MAIN_H_




#include "TypeDef.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"

#ifdef _MAIN_C_
#define MAIN_EXT
#else
#define MAIN_EXT extern
#endif

#include "cmsis_os.h"


#include "stm32f4xx_hal_msp.h"
#include "stm32f4xx_hal_timebase_TIM.h"
#include "LED.h"
#include "SP706.h"
#include "Pulse.h"
#include "Beep.h"
#include "CRC16.h"
#include "M4_UART1.h"
#include "M4_UART2.h"
#include "M4_UART3.h"
#include "M4_IIC1.h"
#include "FRAM.h"
#include "M4_CRC.h"
#include "M4_IIC2.h"
#include "RTC.h"
#include "PCF8563.h"
#include "M4_SPI1.h"

#include "W25QXX.h"
#include "M4_SDIO.h"
#include "KeyBoard.h"
#include "IndepKEY.h"
#include "AlarmClk.h"

#include "KeyboardAPP.h"

#include "PubDef.h"
#include "SysPara.h"
#include "Sys_State.h"

#include "UserPara.h"
#include "DevPara.h"

#include "UC1698.h"

#include "APP_UI.h"
#include "FY188Pro.h"
#include "FY2000Pro.h"
#include "FY1000Pro.h"
#include "HZCRL_XPro.h"
#include "XY188Pro.h"

#include "HT2X188PRO.h"
#include "BRC188PRO.h"
#include "DDF2PRO.h"
#include "NWKmodbus.h"




#include "COM_Server.h"
#include "ClientApp.h"
#include "fatfs.h"

#include "FS_APP.h"


#include "rtx_cli.h"
#include "debug.h"
#include "Calculate.h"
#include "serialization.h"
#include "watchdog.h"
#include "heartbeat.h"
#include "PowerRelay.h"






















#ifdef _MAIN_C_


#endif




MAIN_EXT void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
MAIN_EXT void assert_failed(uint8_t* file, uint32_t line);


MAIN_EXT Chip_ID_Stru ChipID;
MAIN_EXT INT32U ID;




MAIN_EXT void vApplicationIdleHook(void);



#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  



