#include "context.h"

const char defaultip[] = "61.182.229.143";
const char defaultport[] = "9262";

/* 初始化运行参数 */
CONTEXT_OP_RESULT contextInit(context_t *context)
{
	if(context == NULL)
	{
		return CONTEXT_FAIL;
	}
	memset((char *)context, 0x00, sizeof(context_t));
	context->isonce = NOTONCE;
	context->ota.type = O_NONE;
	memcpy(context->appparm.ip, defaultip, strlen(defaultip));
	memcpy(context->appparm.port, defaultport, strlen(defaultport));
	
	if(HAL_OK != spiFlashErase(ContextAddress,sizeof(context_t)))
	{
		return CONTEXT_FAIL;
	}
	if(HAL_OK != spiFlashWrite(ContextAddress,(uint8_t *)context,sizeof(context_t)))
	{
		return CONTEXT_FAIL;
	}
	return CONTEXT_SUCCESS;
}

/* 读取运行参数 */
CONTEXT_OP_RESULT contextLoad(context_t *context)
{
	if(context == NULL)
	{
		return CONTEXT_FAIL;
	}
	spiFlashRead(ContextAddress,(uint8_t *)context,sizeof(context_t));
	return CONTEXT_SUCCESS;
}

/* 保存运行参数 */
CONTEXT_OP_RESULT contextSave(context_t *context)
{
	if(context == NULL)
	{
		return CONTEXT_FAIL;
	}
	if(HAL_OK != spiFlashErase(ContextAddress,sizeof(context_t)))
	{
		return CONTEXT_FAIL;
	}
	if(HAL_OK != spiFlashWrite(ContextAddress,(uint8_t *)context,sizeof(context_t)))
	{
		return CONTEXT_FAIL;
	}
	return CONTEXT_SUCCESS;
}



