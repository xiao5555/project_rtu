#ifndef _LCD_API_H_
#define _LCD_API_H_
#include "Inc/LcdDriver.h"
typedef enum FONT{
	FONT_5x8=1,//8
	FONT_8x16=2,//16
	FONT_15x16=3,//16
	FONT_NUM
}FONT_ENUM;
/**********************************************External function**********************************************************/
void LCD_Dis(uint8_t start_line,uint8_t end_line);//显示的起始行到结束行
void LCD_full_display(uint8_t data_left,uint8_t data_right);
void LCD_DisString(FONT_ENUM font,uint8_t x,uint8_t y,uint8_t *str,...);
void LCD_display_graphic_192x64(uint8_t *dp);
void LCD_ClearScreen(void);//清除全屏
void LCD_ClearRectangle(uint8_t start_x,uint8_t start_y,uint8_t end_x,uint8_t end_y);
#endif//_LCD_API_H_
