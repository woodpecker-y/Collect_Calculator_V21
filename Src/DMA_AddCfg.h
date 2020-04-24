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
* @brief : 本文件用于 工程DMA 数据流的地址配置
* 
* 
* 
*
* @author :许伟
* @date :2017/10/2 13:33
***************************************************************
*/ 
#ifndef _DMA_ADDCFG_H_
#define _DMA_ADDCFG_H_
 



 
#ifdef _DMA_ADDCFG_C_
#define DMA_ADDCFG_EXT
#else
#define DMA_ADDCFG_EXT extern
#endif
 

/* DMA缓存区地址配置 */
#define OFFSETSIZE          0x4000                              //首地址偏移量

#define UART1_Amount	    (2048)								//最大接收DMA缓冲区数量
#define UART1_RX_DMA_ADD	(0x20000000 + OFFSETSIZE)
#define UART1_TX_DMA_ADD	(UART1_RX_DMA_ADD+UART1_Amount)

#define UART2_Amount	    (2048)								//最大接收DMA缓冲区数量
#define UART2_RX_DMA_ADD	(UART1_TX_DMA_ADD+2048)
#define UART2_TX_DMA_ADD	(UART2_RX_DMA_ADD+2048)

#define UART3_Amount	    (2048)								//最大接收DMA缓冲区数量
#define UART3_RX_DMA_ADD	(UART2_TX_DMA_ADD+2048)
#define UART3_TX_DMA_ADD	(UART3_RX_DMA_ADD+2048)

#define SD_Amount 		    (BLOCKSIZE)
#define SDIO_RX_DMA_ADD	    (UART3_TX_DMA_ADD+UART3_Amount)
#define SDIO_TX_DMA_ADD	    (SDIO_RX_DMA_ADD+SD_Amount)






#ifdef _DMA_ADDCFG_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
