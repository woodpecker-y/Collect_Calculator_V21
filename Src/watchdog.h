/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "sp706.h"

#define IWDG_ENABLE   	//是否启用软件看门狗
	 
	 
#if( configUSE_16_BIT_TICKS == 1 )
     #define MAXEVENTCOUNT 8
#else
     #define MAXEVENTCOUNT 24
#endif


#define GUARDINTERVAL 500	//守护进程检测间隔
typedef struct
{
	uint32_t waitTime;
	uint32_t ticks;
}IWDG_Wait_t;



	 
int dogInit(void);
int createIWDG(EventBits_t *event, uint32_t sec);
void feedIWDG(EventBits_t iwdg);
	 

#ifdef __cplusplus
}
#endif
#endif /*__ota_H */




