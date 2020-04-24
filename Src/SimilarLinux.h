/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIMILARLINUX_H
#define __SIMILARLINUX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "watchdog.h"

#define ETX 0x03	//ÕýÎÄ½áÊø
	 
void ps_A(void);
void ps_a(void);
void ps_p(int PID);
void ps_none(void);
void freecmd(void);
	 
	 
#ifdef __cplusplus
}
#endif
#endif /*__ota_H */




