/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __context_H
#define __context_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "common.h"
#include "W25QXX.h"
#include "string.h"

	 
#define NOTONCE  0xaa
#define APP_PARM_SIZE  1024
#define ContextAddress					SysOTAPara_Addr 	//OTA参数配置区在SPI Flash中的起始地址
	 
typedef enum
{
	CONTEXT_SUCCESS,
	CONTEXT_FAIL,
}CONTEXT_OP_RESULT;
	 
typedef enum
{
	O_NONE=0,//不更新
	O_BOOT=1,//更新boot
	O_APP =2,//更新app
}ota_type;

#pragma pack(1)
typedef struct
{
	ota_type type;//固件更新类型
}ota_pram;

#pragma pack(1)
typedef struct
{
	char ip[64];//存储IP地址或域名
	char port[16];//存储端口
}appparm_t;

#pragma pack(1)
typedef struct
{
	uint8_t isonce;//是否首次启动
	ota_pram ota;
	appparm_t appparm;
	uint8_t reserved[APP_PARM_SIZE - sizeof(appparm_t)];
}context_t;

CONTEXT_OP_RESULT contextInit(context_t *context);
CONTEXT_OP_RESULT contextLoad(context_t *context);
CONTEXT_OP_RESULT contextSave(context_t *context);

#ifdef __cplusplus
}
#endif
#endif /*__context_H */


