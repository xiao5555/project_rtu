#ifndef _USART_PROCESS_H_
#define _USART_PROCESS_H_
#include <stdint.h>

typedef struct USART{
	uint8_t *buffer;
	uint16_t len;
	uint8_t lock;
}USART_TypeDef;

typedef struct ELEM{
	uint8_t *buffer;
	uint16_t len;
}ELEM_TypeDef;
/**********************************************External function**********************************************************/
void Usart_ProcessInit(void);
#endif//_USART_PROCESS_H_

