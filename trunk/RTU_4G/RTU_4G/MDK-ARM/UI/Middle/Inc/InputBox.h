#ifndef __INPUT_BOX_H_
#define __INPUT_BOX_H_
#include <stdint.h>
#include "DRIVER/LcdApi.h"
#define BOX_LEN_BUFFER 50
typedef struct InputBox{
	uint8_t max_num;
	uint8_t start_x;
	uint8_t start_y;
	char buff[BOX_LEN_BUFFER];
	FONT_ENUM font;
	void (*StoreCharAndDis)(char c);
	char *(*GetString)(void);
	uint8_t (*Del)(void);
}InputBox_TypeDef;
InputBox_TypeDef *CreateInputBox(uint8_t x,uint8_t y,FONT_ENUM font,uint8_t max_num);

#endif//__INPUT_BOX_H_

