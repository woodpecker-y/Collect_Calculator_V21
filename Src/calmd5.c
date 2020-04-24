#include "calmd5.h"


#define SizePerRW 64
uint8_t md5_read_data[SizePerRW] = {0};

/** 计算SPI Flash数据MD5值 **/
HAL_StatusTypeDef calMd5_hash_SPI(uint32_t address, uint32_t datalen, uint8_t *md5, int32_t *md5len)
{
	HAL_StatusTypeDef err = HAL_ERROR;
  MD5ctx_stt P_pMD5ctx;
  uint32_t error_status = HASH_SUCCESS;
	volatile uint32_t updateStartAddress = 0;
	uint32_t readLength = 0;
	uint32_t size = 0;

	/* Enable CRC clock */
	__CRC_CLK_ENABLE();
	
  /* Set the size of the desired hash digest */
  P_pMD5ctx.mTagSize = CRL_MD5_SIZE;

  /* Set flag field to default value */
  P_pMD5ctx.mFlags = E_HASH_DEFAULT;

  error_status = MD5_Init(&P_pMD5ctx);

	if (error_status != HASH_SUCCESS)
	{
		return HAL_ERROR;
	}
	
	memset(md5_read_data, 0xFF, SizePerRW);
	updateStartAddress = address;
	size = datalen/SizePerRW;
	
	// read data back from spi flash, calc md5
	for(int i = 0; i <= size; i++){
		if( i == size ){
			if( datalen%SizePerRW ){
				readLength = datalen%SizePerRW;
			}
			else{
				break;
			}
		}
		else{
			readLength = SizePerRW;
		}
		err = spiFlashRead(updateStartAddress, md5_read_data, readLength);
		if(HAL_OK != err){
			dbg_printf(DEBUG_DEBUG,"ERROR: [OTA] Read back data err=%d, offset=%d, len=%d.", err, updateStartAddress, readLength);
			return HAL_ERROR;
		}
		error_status = MD5_Append(&P_pMD5ctx, (uint8_t *)md5_read_data, readLength);
		updateStartAddress += readLength;
		if (error_status != HASH_SUCCESS)
		{
			return HAL_ERROR;
		}
	}
	
	// read done, calc MD5
	error_status = MD5_Finish(&P_pMD5ctx, md5, md5len);
	
	if(error_status == HASH_SUCCESS)
	{
		return HAL_OK;
	}
	
	return HAL_ERROR;
	
}

/** 计算片内Flash或内存区域数据MD5值 **/
uint8_t calMd5_hash(uint32_t address, uint32_t datalen, uint8_t *md5, int32_t *md5len)
{
	int32_t status = HASH_SUCCESS;
	__CRC_CLK_ENABLE();
	status = STM32_MD5_HASH_DigestCompute((uint8_t*)address, datalen, md5, md5len);
	if (status == HASH_SUCCESS)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief  MD5 HASH digest compute example.
  * @param  InputMessage: pointer to input message to be hashed.
  * @param  InputMessageLength: input data message length in byte.
  * @param  MessageDigest: pointer to output parameter that will handle message digest
  * @param  MessageDigestLength: pointer to output digest length.
  * @retval error status: can be HASH_SUCCESS if success or one of
  *         HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT,
  *         HASH_ERR_BAD_OPERATION if error occured.
  */
int32_t STM32_MD5_HASH_DigestCompute(uint8_t* InputMessage, uint32_t InputMessageLength,
                                     uint8_t *MessageDigest, int32_t* MessageDigestLength)
{
  MD5ctx_stt P_pMD5ctx;
  uint32_t error_status = HASH_SUCCESS;

  /* Set the size of the desired hash digest */
  P_pMD5ctx.mTagSize = CRL_MD5_SIZE;

  /* Set flag field to default value */
  P_pMD5ctx.mFlags = E_HASH_DEFAULT;

  error_status = MD5_Init(&P_pMD5ctx);

  /* check for initialization errors */
  if (error_status == HASH_SUCCESS)
  {
    /* Add data to be hashed */
    error_status = MD5_Append(&P_pMD5ctx,
                              InputMessage,
                              InputMessageLength);

    if (error_status == HASH_SUCCESS)
    {
      /* retrieve */
      error_status = MD5_Finish(&P_pMD5ctx, MessageDigest, MessageDigestLength);
    }
  }

  return error_status;
}

