#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#include "main.h"

#ifndef _MODBUS_H
#define _MODBUS_H

#define MODBUS_DATA_MAX    80

// MODBUS命令码
#define MODBUS_CMD_READ_MULTI		0x03	// 读多个寄存器
#define MODBUS_CMD_WRITE_SINGLE		0x06	// 写单个寄存器
#define MODBUS_CMD_WRITE_MULTI		0x10	// 写多个寄存器

// MODBUS地址码
#define MODBUS_ADDR	0xFF

typedef enum _ModbusRet{
    MODBUS_OK = 0,
	MODBUS_ERR_INVALID_CMD,		 // 未知功能码
    MODBUS_ERR_CRC16,			 // 校验和错误
    MODBUS_ERR_LESS_MEMORY,      // 内存不足
    MODBUS_ERR_ADDR,             // 地址不匹配
	MODBUS_ERR_LENGTH			 // 长度错误
}ModbusRet;

// Modbus协议帧定义
typedef struct _ModbusPkg{
    u8  addr;		// 仪表地址
    u8  cmd;		// 命令码
    u8*  data;	    // 数据
    u8  data_len;	// 数据长度
}modbus_pkg;

extern modbus_pkg g_modbus_pkg;

u8 modbus_read_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_val, u16 *reg_cnt);
u8 modbus_write_single_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr, u16 *reg_val);
u8 modbus_write_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr_st, u16 *reg_val, u8 *reg_cnt);
u8 modbus_pack(u8 *package, u8 *size, u8 addr, u8 cmd, u8 *dat, u8 len);
u8 modbus_unpack(u8 *package, u8 size, u8 *addr, u8 *cmd, u8 **dat, u8 *len);




#endif
#endif

