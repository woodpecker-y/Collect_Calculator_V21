/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon  
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
* @brief :
* 
* 
* 
*
* @author :
* @date :2017-01-13 16:05
***************************************************************
*/ 
#ifndef _W25QXX_H_
#define _W25QXX_H_
 
#include "M4_SPI1.h"
#include "TypeDef.h"
#include "CRC16.h"
#include "string.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "SP706.h"
#include "debug.h"

 
#ifdef _W25QXX_C_
#define W25QXX_EXT
#else
#define W25QXX_EXT extern
#endif
 
//W25X系列/Q系列芯片列表	   

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256	0XEF18


//W25Q64  8MFlash
#define SPI_FLASH_Size				1024*1024*8UL


#define SPI_FLASH_PageSize			256UL		//256 Byte
#define SPI_FLASH_PageNum			(SPI_FLASH_Size/SPI_FLASH_PageSize)//总数据页数量

#define SPI_FLASH_SectorSize			4096UL		//4K
#define SPI_FLASH_SectorNum			(SPI_FLASH_Size/SPI_FLASH_SectorSize)//总扇区数量



#define SPI_FLASH_BlockSize			65536UL		//64k
#define SPI_FLASH_BlockNum			(SPI_FLASH_Size/SPI_FLASH_BlockSize)//总数据块数量





////////////////////////////////////////////////////////////////////////////////// 
//指令表
#define W25X_WriteEnable			0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg1		0x05 
#define W25X_ReadStatusReg2		0x35 
#define W25X_ReadStatusReg3		0x15 
#define W25X_WriteStatusReg1		0x01 
#define W25X_WriteStatusReg2		0x31 
#define W25X_WriteStatusReg3		0x11 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase			0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID		0x90 
#define W25X_JedecDeviceID		0x9F 
#define W25X_Enable4ByteAddr		0xB7
#define W25X_Exit4ByteAddr		0xE9




#define Flash_WP_PORT			GPIOC
#define Flash_WP_PIN			GPIO_PIN_4
#define Flash_WP_H				(HAL_GPIO_WritePin(Flash_WP_PORT, Flash_WP_PIN, GPIO_PIN_SET))
#define Flash_WP_L				(HAL_GPIO_WritePin(Flash_WP_PORT, Flash_WP_PIN, GPIO_PIN_RESET))


#define Flash_HOLD_PORT			GPIOA
#define Flash_HOLD_PIN			GPIO_PIN_1
#define Flash_HOLD_H			(HAL_GPIO_WritePin(Flash_HOLD_PORT, Flash_HOLD_PIN, GPIO_PIN_SET))
#define Flash_HOLD_L			(HAL_GPIO_WritePin(Flash_HOLD_PORT, Flash_HOLD_PIN, GPIO_PIN_RESET))


#define Flash_CS_PORT			GPIOA
#define Flash_CS_PIN				GPIO_PIN_4
#define Flash_CS_H				(HAL_GPIO_WritePin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_SET))
#define Flash_CS_L				(HAL_GPIO_WritePin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_RESET))








 
#ifdef _W25QXX_C_


#define	SPIFlash_Size			SPI_FLASH_Size   
#define 	SPIFlash_DaBuf_Size		(SPI_FLASH_SectorSize*3)		 //定义SPIFlash缓冲区

void W25QXX_GPIO_Init(void);
INT16U W25QXX_ReadID(void);
INT8U W25QXX_ReadSR(INT8U regno) ;
void W25QXX_WriteSR(INT8U regno,INT8U sr) ;
void W25QXX_Write_Enable(void);
void W25QXX_Write_Disable(void);
INT16U W25QXX_PageWrite(INT8U* pBuffer, INT32U WriteAddr, INT16U NumByteToWrite);
void W25QXX_SectorWrite(INT8U * pBuffer, INT32U WriteAddr, INT16U NumByteToWrite);
void W25QXX_Erase_Chip(void);
HAL_StatusTypeDef W25QXX_Erase_Sector(INT32U Dst_Addr);
void W25QXX_Wait_Busy(void);
void W25QXX_PowerDown(void);
void W25QXX_WAKEUP(void);





#endif
W25QXX_EXT INT16U W25QXX_TYPE;					//定义W25QXX芯片型号		
W25QXX_EXT INT16U FlashID;

W25QXX_EXT void W25QXX_Init(void);
W25QXX_EXT INT16U W25QXX_ReadID(void);

W25QXX_EXT HAL_StatusTypeDef W25QXX_WriteBuffer(INT8U * pBuffer, INT32U WriteAddr, INT16U Lenth);/* 将发送缓冲区的数据写到flash中 */
W25QXX_EXT HAL_StatusTypeDef W25QXX_ReadBuffer(INT8U* pBuffer,INT32U ReadAddr,INT16U NumByteToRead);


W25QXX_EXT HAL_StatusTypeDef ReadData_SPIFlash(INT32U FM_Addr,INT8U *dstp,INT16U Byte_num);
W25QXX_EXT HAL_StatusTypeDef WriteData_SPIFlash(INT32U FM_Addr,INT8U *srcp,INT16U Byte_num);


W25QXX_EXT HAL_StatusTypeDef spiFlashErase(INT32U address, INT32U size);
W25QXX_EXT HAL_StatusTypeDef spiFlashWrite(INT32U address, INT8U *buf, INT32U size);
W25QXX_EXT HAL_StatusTypeDef spiFlashRead(INT32U address, INT8U *buf, INT32U size);




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
