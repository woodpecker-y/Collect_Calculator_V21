/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __updateparm_H
#define __updateparm_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "debug.h"
#include "common.h"
#include "w25qxx.h"
#include "calmd5.h"
#include "APP_UI.h"
#include "context.h"

#define bool _Bool
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0

typedef struct
{
    uint8_t IP1;
    uint8_t IP2;
    uint8_t IP3;
    uint8_t IP4;
    uint16_t Port;
}Server_Parm;

int updateServerIP(char **serverParm);
int down_env_data(void);
void printServerIP(Server_Parm *serverIP);
int verifyProcessFile(void);
int flash_file_type(ota_type type);

#ifdef __cplusplus
}
#endif
#endif /*__ota_H */




