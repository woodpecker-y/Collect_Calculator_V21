/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
*
* @file :
* @version :
* @function :
* 
* 
* 
* 
* 
* 
* @brief :SPI Flash驱动文件
* 
* 
* 
*
* @author :许伟
* @date :2017-01-13 16:05
***************************************************************
*/ 
#define _W25QXX_C_
#include "W25QXX.h"
 





osMutexId spiFlashMutexHandle;

static int spiFlash_SysInit(void)
{
	osMutexDef(spiFlashMutex);
	spiFlashMutexHandle = osMutexCreate(osMutex(spiFlashMutex));
	if(spiFlashMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}


/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void W25QXX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */

	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	//WP
	HAL_GPIO_WritePin(Flash_WP_PORT, Flash_WP_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_WP_PORT, &GPIO_InitStruct);


	//HOLD
	HAL_GPIO_WritePin(Flash_HOLD_PORT, Flash_HOLD_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_HOLD_PORT, &GPIO_InitStruct);
	
	//CS
	HAL_GPIO_WritePin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_CS_PORT, &GPIO_InitStruct);




}








//4Kbytes为一个Sector
//16个扇区为1个Block
//W25Q256
//容量为32M字节,共有512个Block,8192个Sector 
													 
//初始化SPI FLASH的IO口
void W25QXX_Init(void)
{ 
    INT8U temp;
    GPIO_InitTypeDef GPIO_Initure;
    
	GPIO_Initure =GPIO_Initure;
	W25QXX_GPIO_Init();
    
	Flash_CS_H;			            //SPI FLASH不选中
	MX_SPI1_Init();		   			    //初始化SPI
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_2); //设置为45M时钟,高速模式
	W25QXX_TYPE=W25QXX_ReadID();	        //读取FLASH ID.
    if(W25QXX_TYPE==W25Q64)                //SPI FLASH为W25Q256
    {
        temp=W25QXX_ReadSR(3);              //读取状态寄存器3，判断地址模式
        if((temp&0X01)==0)			        //如果不是4字节地址模式,则进入4字节地址模式
		{
			Flash_CS_L; 			        	//选中
			SPI1_ReadWriteByte(W25X_Enable4ByteAddr);//发送进入4字节地址模式指令   
			Flash_CS_H;       		        	//取消片选   
		}
    }
	spiFlash_SysInit();//初始化spi Flash读写互斥锁
}  




//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
//0XEF18,表示芯片型号为W25Q256
u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	Flash_CS_L;				    
	SPI1_ReadWriteByte(0x90);//发送读取ID命令	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	Flash_CS_H;				    
	return Temp;
}   		    





//读取W25QXX的状态寄存器，W25QXX一共有3个状态寄存器
//状态寄存器1：
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
//状态寄存器2：
//BIT7  6   5   4   3   2   1   0
//SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
//状态寄存器3：
//BIT7      6    5    4   3   2   1   0
//HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
//regno:状态寄存器号，范:1~3
//返回值:状态寄存器值
INT8U W25QXX_ReadSR(INT8U regno)   
{  
	INT8U byte=0,command=0; 
    switch(regno)
    {
        case 1:
            command=W25X_ReadStatusReg1;    //读状态寄存器1指令
            break;
        case 2:
            command=W25X_ReadStatusReg2;    //读状态寄存器2指令
            break;
        case 3:
            command=W25X_ReadStatusReg3;    //读状态寄存器3指令
            break;
        default:
            command=W25X_ReadStatusReg1;    
            break;
    }    
	Flash_CS_L;                            //使能器件   
	SPI1_ReadWriteByte(command);            //发送读取状态寄存器命令    
	byte=SPI1_ReadWriteByte(0Xff);          //读取一个字节  
	Flash_CS_H;                            //取消片选     
	return byte;   
} 


//写W25QXX状态寄存器
void W25QXX_WriteSR(INT8U regno,INT8U sr)   
{   
    INT8U command=0;
    switch(regno)
    {
        case 1:
            command=W25X_WriteStatusReg1;    //写状态寄存器1指令
            break;
        case 2:
            command=W25X_WriteStatusReg2;    //写状态寄存器2指令
            break;
        case 3:
            command=W25X_WriteStatusReg3;    //写状态寄存器3指令
            break;
        default:
            command=W25X_WriteStatusReg1;    
            break;
    }   
	Flash_CS_L;                            //使能器件   
	SPI1_ReadWriteByte(command);           //发送写取状态寄存器命令    
	SPI1_ReadWriteByte(sr);                 //写入一个字节  
	Flash_CS_H;                            //取消片选     	      
}   


//W25QXX写使能	
//将WEL置位   
void W25QXX_Write_Enable(void)   
{
	Flash_CS_L;                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteEnable);   //发送写使能  
	Flash_CS_H;                            //取消片选     	      
} 

//W25QXX写禁止	
//将WEL清零  
void W25QXX_Write_Disable(void)   
{  
	Flash_CS_L;                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteDisable);  //发送写禁止指令    
	Flash_CS_H;                            //取消片选     	      
} 

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void W25QXX_Write_Page(INT8U* pBuffer,uint32_t WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    W25QXX_Write_Enable();                  //SET WEL 
	Flash_CS_L;                            //使能器件   
    SPI1_ReadWriteByte(W25X_PageProgram);   //发送写页命令   
    if(W25QXX_TYPE==W25Q256)                //如果是W25Q256的话地址为4字节的，要发送最高8位
    {
        SPI1_ReadWriteByte((INT8U)((WriteAddr)>>24)); 
    }
    SPI1_ReadWriteByte((INT8U)((WriteAddr)>>16)); //发送24bit地址    
    SPI1_ReadWriteByte((INT8U)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((INT8U)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//循环写数  
	Flash_CS_H;                            		//取消片选     	      
	W25QXX_Wait_Busy();					   		//等待写入结束
} 



/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to. 实际物理地址
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : 数据超限返回 超出数据的数量  正常返回0X00
*******************************************************************************/
INT16U W25QXX_PageWrite(INT8U* pBuffer, INT32U WriteAddr, INT16U NumByteToWrite)
{
	INT16U BackValue =0X0000;
	//新增加边界限制命令 不允许超页写
  	INT16U Pageborder =SPI_FLASH_PageSize-(WriteAddr%SPI_FLASH_PageSize);	//计算当前页下该地址允许写入的字节数量
	W25QXX_Write_Enable();												/* Enable the write access to the FLASH */
	Flash_CS_L;															/* Select the FLASH: Chip Select low */
	
	SPI1_ReadWriteByte(W25X_PageProgram); 								/* Send "Write to Memory " instruction */
    if(W25QXX_TYPE==W25Q256)                							//如果是W25Q256的话地址为4字节的，要发送最高8位
    {
        SPI1_ReadWriteByte((INT8U)((WriteAddr)>>24)); 
    }	
	SPI1_ReadWriteByte((WriteAddr & 0xFF0000) >> 16);/* Send WriteAddr high nibble address byte to write to */
	SPI1_ReadWriteByte((WriteAddr & 0xFF00) >> 8); /* Send WriteAddr medium nibble address byte to write to */
	SPI1_ReadWriteByte(WriteAddr & 0xFF); /* Send WriteAddr low nibble address byte to write to */



	//新增加边界限制命令 不允许超页写
	if(NumByteToWrite > Pageborder) 
	{
		BackValue =NumByteToWrite -Pageborder;
		NumByteToWrite = Pageborder;
	}

	/* while there is data to be written on the FLASH */
	while (NumByteToWrite--)
	{
	/* Send the current byte */
		SPI1_ReadWriteByte(*pBuffer);
	/* Point on the next byte to be written */
	pBuffer++;
	}
	/* Deselect the FLASH: Chip Select high */
	Flash_CS_H;
	/* Wait the end of Flash writing */
	W25QXX_Wait_Busy();
	return BackValue;
}




/*******************************************************************************
* Function Name  : SPI_FLASH_SectorWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void W25QXX_SectorWrite(INT8U * pBuffer, INT32U WriteAddr, INT16U NumByteToWrite)
{
	INT8U NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	Addr = WriteAddr % SPI_FLASH_PageSize;			//页对齐监测标志
	count = SPI_FLASH_PageSize - Addr;				//首页距页尾边界字节数量
	
	NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;//整页计数器
	NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;//半页字节计数器

	
	if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
	{
		if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
	  	{
	  		W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
	  	}
	  	else /* NumByteToWrite > SPI_FLASH_PageSize */
	  	{
	  		while (NumOfPage--)//连续写入整页
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}
			if ( NumOfSingle !=0)//写入半页
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
			
		}
	}
	/* WriteAddr is not SPI_FLASH_PageSize aligned  */
	else //起始字节没有页对齐
	{
		if (NumOfPage == 0) //没有完整数据页
		{
			if ( NumByteToWrite<=count)//字节数量没有跨页
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
			}
			else
			{
				temp = NumOfSingle - count;
				W25QXX_PageWrite(pBuffer, WriteAddr, count);
				WriteAddr +=  count;
				pBuffer += count;
				W25QXX_PageWrite(pBuffer, WriteAddr, temp);
			}
		}
		
    	else /* NumByteToWrite > SPI_FLASH_PageSize */
    	{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
			NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
			W25QXX_PageWrite(pBuffer, WriteAddr, count);
			WriteAddr +=  count;
			pBuffer += count;
			while (NumOfPage--)
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}
			if (NumOfSingle != 0)
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
    	}
  	}
}








//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();					//SET WEL 
    W25QXX_Wait_Busy();   
	Flash_CS_L;                            //使能器件   
    SPI1_ReadWriteByte(W25X_ChipErase);			//发送片擦除命令  
	Flash_CS_H;							//取消片选     	      
	W25QXX_Wait_Busy();					//等待芯片擦除结束
}   


/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input              : SectorAddr: address of the sector to erase.
		该地址为存储器的物理地址，通过该指令存储器会计算所写物理地址所属扇区并予以擦除
* Output           : None
* Return            :0X00  正常   0XA0 地址超出存储器范围
*******************************************************************************/
HAL_StatusTypeDef W25QXX_Erase_Sector(INT32U Dst_Addr)   
{  
  	HAL_StatusTypeDef BackVal =HAL_OK;
 	if (Dst_Addr >=SPI_FLASH_Size)
	{
		BackVal =HAL_ERROR;
		return BackVal;
	}
    W25QXX_Write_Enable();                	//SET WEL 	 
    W25QXX_Wait_Busy();   
	Flash_CS_L;                            //使能器件   
    SPI1_ReadWriteByte(W25X_SectorErase);   		//发送扇区擦除指令 
    if(W25QXX_TYPE==W25Q256)            	//如果是W25Q256的话地址为4字节的，要发送最高8位
    {
        SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>24)); 
    }
    SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>16));	//发送24bit地址    
    SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((INT8U)Dst_Addr);  
	Flash_CS_H;							//取消片选     	      
    W25QXX_Wait_Busy();   				    //等待擦除完成
    
	BackVal =HAL_OK;
	return BackVal;
    
}  


 
//等待空闲
void W25QXX_Wait_Busy(void)   
{   

	while((W25QXX_ReadSR(1)&0x01)==0x01)			// 等待BUSY位清空
	{
		osDelay(1);
		SP706_Toggle;
	}
} 



//进入掉电模式
void W25QXX_PowerDown(void)   
{ 
	Flash_CS_L;									//使能器件   
    SPI1_ReadWriteByte(W25X_PowerDown);				//发送掉电命令  
	Flash_CS_H;                            	//取消片选     	      

}   
//唤醒
void W25QXX_WAKEUP(void)   
{  
	Flash_CS_L;									//使能器件   
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);		//send W25X_PowerDown command 0xAB    
	Flash_CS_H;                            	//取消片选     	      

}   









/*

 函数名称:向Flash制定地址写入连续数据。再写入之前会对所在的扇区进行擦除

INT8U * pBuffer:数据指针
uint32_t WriteAddr:存储器首地址
u16 Lenth:数据长度
//0X00  正常   0XA0 地址超出存储器范围
*/
HAL_StatusTypeDef W25QXX_WriteBuffer(INT8U * pBuffer, INT32U WriteAddr, INT16U Lenth)/* 将发送缓冲区的数据写到flash中 */
{
	HAL_StatusTypeDef BackVal =HAL_OK;
	INT16U Sector_Start =WriteAddr /SPI_FLASH_SectorSize;				//计算所写数据起始扇区
	INT16U Sector_End =(WriteAddr+Lenth-1) /SPI_FLASH_SectorSize;		//计算所写数据终止扇区
	INT16U BU =0;		//扇区擦除记录器

	if ((WriteAddr+Lenth)>SPI_FLASH_Size)
	{
		BackVal =HAL_ERROR;
		return BackVal;
	}
	
	for (BU =Sector_Start;BU<=Sector_End;BU++)
	{
	 	BackVal =W25QXX_Erase_Sector(BU*SPI_FLASH_SectorSize);//扇区擦除
	 	if( BackVal !=HAL_OK )
	 	{
			return BackVal;
	 	}
	}
	W25QXX_SectorWrite (pBuffer,WriteAddr,Lenth);	//向扇区写入数据
	return BackVal;

}





//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
HAL_StatusTypeDef W25QXX_ReadBuffer(INT8U* pBuffer,INT32U ReadAddr,INT16U NumByteToRead)   
{ 
 	u16 i;   										    
	Flash_CS_L;                            	//使能器件   
    SPI1_ReadWriteByte(W25X_ReadData);			//发送读取命令  
    if(W25QXX_TYPE==W25Q256)               	//如果是W25Q256的话地址为4字节的，要发送最高8位
    {
        SPI1_ReadWriteByte((INT8U)((ReadAddr)>>24));    
    }
    SPI1_ReadWriteByte((INT8U)((ReadAddr)>>16));   //发送24bit地址    
    SPI1_ReadWriteByte((INT8U)((ReadAddr)>>8));   
    SPI1_ReadWriteByte((INT8U)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);    //循环读数  
    }
	Flash_CS_H;                          //取消片选   

	return HAL_OK;
}  






/*
 函数名称: ReadData_SPIFash(unsigned int FM_Addr,unsigned char *dstp,unsigned int Byte_num)
*/

static __inline HAL_StatusTypeDef ReadData_SPIFlash_UnSafe(INT32U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	INT8U readcount =0;
	INT8U* SPIReadBuf = pvPortMalloc( SPIFlash_DaBuf_Size);
		
	
	if(SPIReadBuf == NULL)
	{
		BackValue =HAL_ERROR;
		dbg_printf(DEBUG_ERR,"内存不足");
		return BackValue;
	}

	if (Byte_num>SPIFlash_DaBuf_Size)
	{
		BackValue =HAL_ERROR;
		
		vPortFree( SPIReadBuf);
		return BackValue;
	}
	if((FM_Addr+Byte_num) >SPIFlash_Size)
	{
		BackValue =HAL_ERROR;

		vPortFree( SPIReadBuf);
		return BackValue;
	}
	readcount = 0;

	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			BackValue=HAL_ERROR;
			break;
		}

		if(HAL_OK ==W25QXX_ReadBuffer(SPIReadBuf,FM_Addr,Byte_num))
		{
			
			if(CRC16Check(SPIReadBuf,Byte_num-2)==0)
			{
				BackValue=HAL_OK;
				memcpy(dstp,SPIReadBuf,Byte_num);
				break;
			}
		}
	}

	
	vPortFree( SPIReadBuf);
	return BackValue;
}

/* 线程安全版本 */
HAL_StatusTypeDef ReadData_SPIFlash(INT32U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = ReadData_SPIFlash_UnSafe(FM_Addr,dstp,Byte_num);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


/*
函数名称 :INT8U WriteData_SPIFLASH(unsigned int FM_Addr,unsigned char *srcp,unsigned int Byte_num)
 函数功能: 向存储器写入一定数量的数据,注意最后4个字节为校验码

   返回值: 0XF0读写数据数量超出缓冲区
	       0XA0读数据地址超出存储器地址
	       0XFF数据校验错误
	       0X00正常
*/
static __inline HAL_StatusTypeDef WriteData_SPIFlash_UnSafe(INT32U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	INT8U readcount =0;
	if (Byte_num>SPIFlash_DaBuf_Size)
	{
		BackValue =HAL_ERROR;
		return BackValue;
	}

	if ((FM_Addr+Byte_num)>SPIFlash_Size)
	{
		BackValue =HAL_ERROR;
		return BackValue;
	}
	
	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			BackValue =HAL_ERROR;
			break;
		}
		CRC16Put(srcp,Byte_num-2);
		
		if(HAL_OK ==W25QXX_WriteBuffer(srcp,FM_Addr,Byte_num))
		{
			if(HAL_OK == W25QXX_ReadBuffer(srcp,FM_Addr,Byte_num))
			{
				BackValue =HAL_OK;
				break;
			}
		}	
	}
	return BackValue;
}

/* 线程安全版本 */
HAL_StatusTypeDef WriteData_SPIFlash(INT32U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = WriteData_SPIFlash_UnSafe(FM_Addr,srcp,Byte_num);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


/* 线程安全版本的只擦除不写入函数 */
HAL_StatusTypeDef spiFlashErase(INT32U address, INT32U size)
{
	HAL_StatusTypeDef result = HAL_OK;
	INT16U Sector_Start = address / SPI_FLASH_SectorSize;				//计算所写数据起始扇区
	INT16U Sector_End = (address + size-1) / SPI_FLASH_SectorSize;	//计算所写数据终止扇区


	
	INT16U BU = 0;		//扇区擦除记录器

	if ((address + size) > SPI_FLASH_Size)
	{
		return HAL_ERROR;
	}
	
	/* 执行线程安全擦除 */
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	for (BU = Sector_Start; BU<=Sector_End; BU++)
	{
		result = W25QXX_Erase_Sector(BU * SPI_FLASH_SectorSize);//扇区擦除
	 	if( result != HAL_OK )
	 	{
			osMutexRelease(spiFlashMutexHandle);
			os_printf("\r\n");
			return result;
	 	}
		os_printf("\33[K");
		os_printf("\rerase:%d/%d",BU-Sector_Start+1, Sector_End-Sector_Start+1);
	}
	os_printf("\r\n");
	osMutexRelease(spiFlashMutexHandle);

	return result;
}





/* 线程安全版本的只写入不擦除函数 */
HAL_StatusTypeDef spiFlashWrite(INT32U address, INT8U *buf, INT32U size)
{
	HAL_StatusTypeDef result = HAL_OK;

	if ((address + size) > SPI_FLASH_Size)
	{
		return HAL_ERROR;
	}
	
	/* 执行线程安全写入 */
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	W25QXX_SectorWrite (buf, address, size);	//向扇区写入数据
	osMutexRelease(spiFlashMutexHandle);

	return result;
}

/* 线程安全版本的读函数 */
HAL_StatusTypeDef spiFlashRead(INT32U address, INT8U *buf, INT32U size)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = W25QXX_ReadBuffer(buf, address, size);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
