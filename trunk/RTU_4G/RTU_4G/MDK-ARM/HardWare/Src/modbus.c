#include "Inc/modbus.h"
#include "Inc/sysinfo.h"
#include "stm32l4xx_hal.h"
#include "usart.h"

static RECEIVED_DATA_TypeDef* SendAndRevData(struct MODBUS* obj,uint16_t delay);//
static uint8_t AppendData(struct MODBUS* obj,uint8_t *data,uint16_t len);
static void ReleaseData(struct MODBUS* obj);
static uint16_t calculate_crc(uint8_t *buf,uint16_t len);
static void private_del(void *data);
/********************************************************************
 *@bref 创建包头函数
 *     
 *@ret 
***********************************************************************/
MODBUS_TypeDef *NewModbusPkg(void)
{
	MODBUS_TypeDef *ptr=ptr=calloc(sizeof(MODBUS_TypeDef),0);
	if(ptr==0)
goto err_handle;
	ptr->buff=calloc(DEFAULT_MALLOC_SIZE,0);
	if(ptr->buff==0)
goto err_handle;
	
//	ptr->buff//设置帧头
	ptr->buff_count=14;//帧头的长度
	ptr->max_len=DEFAULT_MALLOC_SIZE;
	ptr->SendAndReceivedData=SendAndRevData;
	ptr->AppendData=AppendData;
	ptr->ReleaseData=ReleaseData;
	return ptr;
err_handle:
	if(ptr->buff)
		free(ptr->buff);
	if(ptr)
		free(ptr);
	return 0;
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static RECEIVED_DATA_TypeDef* SendAndRevData(struct MODBUS* obj,uint16_t delay)//
{
	uint16_t crc_val=calculate_crc(obj->buff,obj->buff_count);//CRC校验
	AppendData(obj,(uint8_t*)&crc_val,2);
	SerialReceivedList->DelElemByType(SerialReceivedList,"MODBUS",private_del);
	HAL_UART_Transmit(&huart1,obj->buff,obj->buff_count,1000);//串口发送数据
	while(delay--)
	{
		RECEIVED_DATA_TypeDef* val=SerialReceivedList->TakeFrontByType(SerialReceivedList,(char*)"MODBUS");
		if(val)
			return val;
		HAL_Delay(1);
	}
	return 0;
}
/********************************************************************
 *@bref 挂载数据
 *     
 *@ret  0    ok 
		else err
***********************************************************************/
static uint8_t AppendData(struct MODBUS* obj,uint8_t *data,uint16_t len)
{
	if((len+obj->buff_count)>obj->max_len)
	{
		//扩容处理
		uint8_t *data_buff=calloc(len+obj->buff_count+5,0);
		if(data)
		{
			memcpy(data_buff,&obj->buff[0],obj->buff_count);
			memcpy(&data_buff[obj->buff_count],data,len);
			free(obj->buff);
			obj->buff=data_buff;
			obj->buff_count += len;
			obj->max_len = obj->buff_count+5;
		}else
		{
			return 0xff;
		}
	}else
	{
		memcpy(&obj->buff[obj->buff_count],data,len);
		obj->buff_count += len;
	}
	return 0;
}
/********************************************************************
 *@bref 释放数据
 *     
 *@ret 
***********************************************************************/
static void ReleaseData(struct MODBUS* obj)
{
	if(obj)
	{
		if(obj->buff)
			free(obj->buff);
		free(obj);		
	}
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
//static MODBUS_TypeDef *GetInstance(void)
//{
//	static MODBUS_TypeDef *ptr=0;
//	static uint8_t buff_data[DEFAULT_MALLOC_SIZE]={0};
//	if(ptr==0)
//	{
//		ptr=calloc(sizeof(MODBUS_TypeDef),0);
//		ptr->buff=calloc(DEFAULT_MALLOC_SIZE,0);			
//		if((ptr)&&(ptr->buff))
//		{
//goto err_handle;
//		}
////		ptr->buff//设置帧头
//		ptr->buff_count=14;//帧头的长度
//		ptr->SendAndReceivedData=SendAndRevData;
//		ptr->AppendData=AppendData;
//	}
//	return ptr;
//err_handle:
//	if(ptr->buff)
//		free(ptr->buff);
//	if(ptr)
//		free(ptr);
//	return 0;
//}
uint16_t calculate_crc(uint8_t *buf,uint16_t len)
{
	//预置16位crc寄存器，初值全部为1
	uint16_t wcrc=0XFFFF;
	//定义中间变量
	uint8_t temp = 0;
	//定义计数
	int i=0,j=0;
	//循环计算每个数据
	for(i=0;i<len;i++)
	{
		//将八位数据与crc寄存器异或
		temp=*buf&0X00FF;
		//指针地址增加，指向下个数据
		buf++;
		//将数据存入crc寄存器
		wcrc^=temp;
		//循环计算数据
		for(j=0;j<8;j++)
		{
		  //判断右移出的是不是1，如果是1则与多项式进行异或
		  if(wcrc&0X0001)
		  {
				//先将数据右移一位
				wcrc>>=1;
				//与上面的多项式进行异或
				wcrc^=0XA001;
		  }
		  //如果不是1，则直接移出
		  else
		  {
				//直接移出
				wcrc>>=1;
		  }
		}
	}
	//crc的值
	return wcrc;
}
static void private_del( void *data)
{
	if(data)
	{
		RECEIVED_DATA_TypeDef *val=data;
		free(val->buff);
		free(val);
	}
}