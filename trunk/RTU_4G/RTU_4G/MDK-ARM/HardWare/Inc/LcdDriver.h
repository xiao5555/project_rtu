#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_
#include "stm32l4xx_hal.h"
#include <stdint.h>

#define LCD_FONT_CS(n)    	(n?HAL_GPIO_WritePin(ROM_CS_GPIO_Port,ROM_CS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(ROM_CS_GPIO_Port,ROM_CS_Pin,GPIO_PIN_RESET))
#define LCD_FONT_SCLK(n)    (n?HAL_GPIO_WritePin(ROM_SCK_GPIO_Port,ROM_SCK_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(ROM_SCK_GPIO_Port,ROM_SCK_Pin,GPIO_PIN_RESET))
#define LCD_FONT_SI(n)		(n?HAL_GPIO_WritePin(ROM_IN_GPIO_Port,ROM_IN_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(ROM_IN_GPIO_Port,ROM_IN_Pin,GPIO_PIN_RESET))
#define LCD_FONT_SO(n)		(n?HAL_GPIO_WritePin(ROM_OUT_GPIO_Port,ROM_OUT_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(ROM_OUT_GPIO_Port,ROM_OUT_Pin,GPIO_PIN_RESET))
#define LCD_FONT_Read_SO()  HAL_GPIO_ReadPin(ROM_OUT_GPIO_Port,ROM_OUT_Pin)

#define LCD_SDA(n)		(n?HAL_GPIO_WritePin(LCD_SDA_GPIO_Port,LCD_SDA_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_SDA_GPIO_Port,LCD_SDA_Pin,GPIO_PIN_RESET))
#define LCD_SCL(n)		(n?HAL_GPIO_WritePin(LCD_SCL_GPIO_Port,LCD_SCL_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_SCL_GPIO_Port,LCD_SCL_Pin,GPIO_PIN_RESET))
#define LCD_REST(n)     (n?HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET))
#define LCD_POWER(n)    (n?HAL_GPIO_WritePin(LCD_PWR_EN_GPIO_Port,LCD_PWR_EN_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_PWR_EN_GPIO_Port,LCD_PWR_EN_Pin,GPIO_PIN_RESET))
/**********************************************External function**********************************************************/
void transfer_command(uint8_t com);
void transfer_data(uint8_t dat);
void LCD_Init(void);
#endif//_LCD_DRIVER_H_

