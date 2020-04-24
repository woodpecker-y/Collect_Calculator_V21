/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SERIALIZATION_H
#define __SERIALIZATION_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "fatfs.h"
#include "FS_APP.H"
#include "main.h"


#define FS_TRY_TIMES 3

int SaveLog(void);

#ifdef __cplusplus
}
#endif
#endif /*__ota_H */




