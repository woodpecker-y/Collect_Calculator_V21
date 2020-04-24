/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __calmd5_H
#define __calmd5_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "crypto.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "W25QXX.h"
#include "debug.h"

void calMd5(void);
uint8_t calMd5_hash(uint32_t address, uint32_t datalen, uint8_t *md5, int32_t *md5len);
int32_t STM32_MD5_HASH_DigestCompute(uint8_t* InputMessage, uint32_t InputMessageLength, uint8_t *MessageDigest, int32_t* MessageDigestLength);
HAL_StatusTypeDef calMd5_hash_SPI(uint32_t address, uint32_t datalen, uint8_t *md5, int32_t *md5len);
	 
#ifdef __cplusplus
}
#endif
#endif /*__ calmd5_H */
