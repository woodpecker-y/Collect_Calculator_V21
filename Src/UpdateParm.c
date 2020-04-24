#include "updateparm.h"

static HAL_StatusTypeDef spiFlashCopy(INT32U dest, INT32U src, INT32U datalen);
static void sprintfhex(char *buf, uint8_t *data,uint32_t len);




static void sprintfhex(char *buf, uint8_t *data,uint32_t len)
{
	for(int i=0; i< len; i++)
	{
		sprintf(buf, "%02x ", data[i]);
		buf+=2;
	}
}

bool isValidStr(char *buf, Server_Parm *serverParm)
{  
    int part1,part2,part3,part4;  
    char tail = 0;  
    int field;  
    if(buf == NULL)  
    {  
        return false;  
    }  
    field=sscanf(buf,"%d . %d . %d . %d %c",&part1,&part2,&part3,&part4,&tail);
    if(field<4|| field>5)  
    {  
        return false;  
    }  
    if(tail!=0)  
    {  
        return false;  
    }  
    if( (part1>=0 && part1<=255) &&  (part2>=0 && part2<=255) &&  (part3>=0 && part3<=255) &&  (part4>=0 && part4<=255) )  
    {  
		serverParm->IP1 = part1;
		serverParm->IP2 = part2;
		serverParm->IP3 = part3;
		serverParm->IP4 = part4;
        return true;
    }
    return false;  
}

int updateServerIP(char **serverParm)
{
	Server_Parm setServer;

	/* 验证服务器IP和PORT是否合法 */
	int port = atoi(serverParm[2]);
	if(!(0<port && port<65536))
	{
		return -1;
	}
	if(!isValidStr(serverParm[1], &setServer))
	{
		return -2;
	}

	/* 更新服务器地址 */
	return setServerIP(setServer.IP1, setServer.IP2, setServer.IP3, setServer.IP4, port);
}

void printServerIP(Server_Parm *serverIP)
{
	getServerIP(&serverIP->IP1, &serverIP->IP2, &serverIP->IP3, &serverIP->IP4, &serverIP->Port);
}

/* 刷新Boot或App */
int flash_file_type(ota_type type)
{
	context_t *cp = pvPortMalloc(sizeof(context_t));
	
	if(NULL == cp)
	{
		dbg_printf(DEBUG_WARNING,"内存不足，无法更新固件");
		return -1;
	}
	
	contextLoad(cp);
	if(NOTONCE != cp->isonce)
	{
		contextInit(cp);
	}
	
	cp->ota.type = type;
	contextSave(cp);
	
	vPortFree(cp);
	cp = NULL;
	
	return 0;
}


/* 下载设备或用户档案信息并刷新 */
int down_env_data(void)
{
	int res;
	/* download files */
	if(0 != SerialDownload())
	{
		return -1;
	}
	dbg_printf(DEBUG_INFO,"Download file success");

	/* verify file and process it */
	res = verifyProcessFile();
	return res;
}

/* 验证下载的文件并处理 */
int verifyProcessFile(void)
{
	HAL_StatusTypeDef result;
	int returnvalue = 0;
	uint32_t filesize = 0;
	uint8_t md5[CRL_MD5_SIZE];
	uint8_t file_md5[CRL_MD5_SIZE];
	int32_t md5len;
	char temp[CRL_MD5_SIZE * 2 + 1] = {0};
	uint8_t mark = 0;

	
	/* read file size and md5 */
	result = spiFlashRead(SysDownload_Temp_Addr,(uint8_t *)&filesize,4);
	if(HAL_OK != result)
	{
		return -1;
	}	
	result = spiFlashRead(SysDownload_Temp_Addr + sizeof(uint32_t), (uint8_t *)file_md5, sizeof(file_md5));
	if(HAL_OK != result)
	{
		return -1;
	}	

	dbg_printf(DEBUG_INFO,"Read file size: %d",filesize);
	if(filesize > SysDownload_Temp_Size)
	{
		dbg_printf(DEBUG_INFO,"File size is too big");
		return -1;
	}
	sprintfhex(temp, file_md5, CRL_MD5_SIZE);
	dbg_printf(DEBUG_INFO,"Target md5: %s",temp);
	
	/* cal file md5 and check it*/
	result = calMd5_hash_SPI(SysDownload_Temp_Addr + sizeof(uint32_t) + sizeof(md5), filesize, md5, &md5len);
	if(HAL_OK != result)
	{
		return -1;
	}
	sprintfhex(temp, md5, CRL_MD5_SIZE);
	dbg_printf(DEBUG_INFO,"File md5: %s",temp);
	
	if(0 != memcmp(md5, file_md5, sizeof(file_md5)))
	{
		dbg_printf(DEBUG_INFO,"File md5 verify fail");
		return -1;
	}
	dbg_printf(DEBUG_INFO,"File md5 verify success,start update parameter.\r\n");
	
	/* read mark and update parameter */
	result = spiFlashRead(SysDownload_Temp_Addr + sizeof(uint32_t) + sizeof(md5), (uint8_t *)&mark, sizeof(mark));
	if(HAL_OK != result)
	{
		return -1;
	}
	switch(mark)
	{
		case 0x01:
			/* update user data */
			dbg_printf(DEBUG_INFO,"Start update user data");
			if(filesize > SysUserList_Size)
			{
				dbg_printf(DEBUG_INFO,"user data file size overflow");
				returnvalue = -1;
			}
			else
			{
				if(HAL_OK != spiFlashCopy(SysUserList_Addr, SysDownload_Temp_Addr + sizeof(uint32_t) + sizeof(md5) + sizeof(mark), filesize - sizeof(mark)))
				{
					dbg_printf(DEBUG_INFO,"flash user data fail");
					returnvalue = -1;
				}
			}
			break;
		case 0x02:
			/* update device */
			dbg_printf(DEBUG_INFO,"Start update device data");
			if(filesize > SysDeviceList_Size)
			{
				dbg_printf(DEBUG_INFO,"device data file size overflow");
				returnvalue = -1;
			}
			else
			{
				if(HAL_OK != spiFlashCopy(SysDeviceList_Addr, SysDownload_Temp_Addr + sizeof(uint32_t) + sizeof(md5) + sizeof(mark), filesize - sizeof(mark)))
				{
					dbg_printf(DEBUG_INFO,"flash user data fail");
					returnvalue = -1;
				}
			}
			break;
		default:
			/* unknow parameter */
			dbg_printf(DEBUG_INFO,"unknow parameter type");
			returnvalue = -1;
			break;
	}
	
	return returnvalue;
	
}

#define spiFlashTempSize 1024
uint8_t spiFlashTemp[spiFlashTempSize];
static HAL_StatusTypeDef spiFlashCopy(INT32U dest, INT32U src, INT32U datalen)
{
	HAL_StatusTypeDef err = HAL_ERROR;
	volatile uint32_t readStartAddress = 0;
	volatile uint32_t writeStartAddress = 0;
	volatile uint32_t offset = 0;
	uint32_t readLength = 0;
	uint32_t size = 0;


	spiFlashErase(dest,datalen);
	memset(spiFlashTemp, 0xFF, spiFlashTempSize);
	readStartAddress = src;
	writeStartAddress = dest;
	offset = 0;
	size = datalen/spiFlashTempSize;
	
	/* read data back from spi flash, write to flash */
	for(int i = 0; i <= size; i++){
		if( i == size ){
			if( datalen%spiFlashTempSize ){
				readLength = datalen%spiFlashTempSize;
			}
			else{
				break;
			}
		}
		else{
			readLength = spiFlashTempSize;
		}
		err = spiFlashRead(readStartAddress + offset, spiFlashTemp, readLength);
		if(HAL_OK != err){
			dbg_printf(DEBUG_DEBUG,"ERROR: [SPIFLASHCOPY] Read back data err=%d, offset=%d, len=%d.", err, readStartAddress + offset, readLength);
			return HAL_ERROR;
		}
		err = spiFlashWrite(writeStartAddress + offset, spiFlashTemp, readLength);
		offset += readLength;
		if (HAL_OK != err)
		{
			return HAL_ERROR;
		}
	}
	
	/* copy done */
	
	return err;
	
}

