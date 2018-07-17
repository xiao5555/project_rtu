#ifndef _24CXX_H_
#define _24CXX_H_
#include <stdint.h>

void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//从指定地址开始读出指定长度的数据
uint8_t AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC
#endif//_24CXX_H_

