/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HEARTBEAT_H
#define __HEARTBEAT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "app_ui.h"

#define HEARTBEAT_ENABLE                                    //是否启用心跳保活
#define TCPSEND_EVENT           0x01                        //TCP数据发送事件
#define TCPREV_EVENT            0x02                        //TCP数据接收事件
#define HEARTBEAT_TIMEOUT       (pdMS_TO_TICKS(60000))      //心跳超时时间
#define HEARTBEAT_TRYTIMES		30	                        //心跳超时后重试次数

	 
int HbInit(void);
void HbMainTask(void);
void tcpSendEvent(void);
void tcpRevEvent(void);


#ifdef __cplusplus
}
#endif
#endif /*__heartbeat_H */




