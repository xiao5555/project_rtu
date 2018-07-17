#ifndef _KEY_H_
#define _KEY_H_
#include <stdint.h>
#include "stm32l4xx_hal.h"
typedef struct KEY{
	uint32_t  value;
	uint32_t time_count;
	uint8_t  buff_table[16];
}KEY_TypeDef;
#define DEFAULT_WAIT_GET_KET_VALUE  30  //在等待（DEFAULT_WAIT_GET_KET_VALUE*按键定时扫描时间）时间后读取按键值
//#define KEY_LINE_INPUT_COLUMN_OUT_MODE()  do{  \
//		GPIOC->MODER&=(~(0x0f<<12));GPIOD->MODER&=(~(0x0f<<28));/*******pc6,7 pd14,15	输入模式*****/ \
//		GPIOC->PUPDR&=(~(0x0f<<12));GPIOC->PUPDR|=(0x05<<12);GPIOD->PUPDR&=(~(0x0f<<28));GPIOD->PUPDR|=(0x05<<28); /******pc6,7 pd14,15上拉****/\
//		GPIOD->MODER&=(~(0xff<<18));GPIOD->MODER|=(0x55<<18);/*****pd9,10,11,12 输出********/\
//		GPIOD->PUPDR&=(~(0xff<<18));GPIOD->PUPDR|=(0xaa<<18); /****pd9,10,11,12 下拉**/\
//		GPIOD->BSRR|=(0x0f<<9); /*******pd 9,10,11,12 为0*******/\
//	}while(0)
////		GPIOD->OTYPER|=(0x0f<<9);/***********pd 9,10,11,12开楼**************/ 
//#define KEY_LINE_OUT_COLUMN_INPUT_MODE()	do{  \
//		GPIOC->MODER&=(~(0x0f<<12));GPIOC->MODER|=(0x05<<12);GPIOD->MODER&=(~(0xf<<28));GPIOD->MODER|=(0x05<<28);/************pc6,7 pd14,15	输出模式***********/  \
//		GPIOC->PUPDR&=(~(0x0f<<12));GPIOC->PUPDR|=(0x0a<<12);GPIOD->PUPDR&=(~(0x0f<<28));GPIOD->PUPDR|=(0x0a<<28);/**********pc6,7 pd14,15下拉***************/  \
//		GPIOC->BSRR|=(0x03<<6);GPIOD->BSRR|=(0x03<<14);/*****pc6,7 pd 14,15为0***********/	  \
//    	GPIOD->MODER&=(~(0xff<<18));GPIOD->PUPDR|=(0x55<<18);/****pd9,10,11,12 输入模式，上拉*******/  \
//}while(0)
////		GPIOC->OTYPER|=(0x03<<6);GPIOD->OTYPER|=(0x03<<14);/***pc6,7 开楼，pd14,15 开楼****/  
/********************************************** Private function**********************************************************/
uint8_t KEY_GetValue(void);
void KEY_Process(void *arg);
/**********************************************External function**********************************************************/
void KEY_Init(void);
#endif//_KEY_H_
