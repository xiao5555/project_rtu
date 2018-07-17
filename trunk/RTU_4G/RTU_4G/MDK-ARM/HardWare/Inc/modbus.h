#ifndef _MODBUS_H_
#define _MODBUS_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct RECEIVED{
	uint8_t *buff;
	uint16_t len;
}RECEIVED_DATA_TypeDef;
typedef struct MODBUS{
	RECEIVED_DATA_TypeDef* (*SendAndReceivedData)(struct MODBUS* obj,uint16_t delay);//
	uint8_t (*AppendData)(struct MODBUS* obj,uint8_t *data,uint16_t len);
	void (*ReleaseData)(struct MODBUS* obj);
	uint8_t *buff;
	uint16_t buff_len;
	uint16_t buff_count;
	uint16_t max_len;
}MODBUS_TypeDef;
/**********************************************External function**********************************************************/
#define DEFAULT_MALLOC_SIZE   50
MODBUS_TypeDef *NewModbusPkg(void);
#endif//_MODBUS_H_

