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
 *@bref ������ͷ����
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
	
//	ptr->buff//����֡ͷ
	ptr->buff_count=14;//֡ͷ�ĳ���
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
	uint16_t crc_val=calculate_crc(obj->buff,obj->buff_count);//CRCУ��
	AppendData(obj,(uint8_t*)&crc_val,2);
	SerialReceivedList->DelElemByType(SerialReceivedList,"MODBUS",private_del);
	HAL_UART_Transmit(&huart1,obj->buff,obj->buff_count,1000);//���ڷ�������
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
 *@bref ��������
 *     
 *@ret  0    ok 
		else err
***********************************************************************/
static uint8_t AppendData(struct MODBUS* obj,uint8_t *data,uint16_t len)
{
	if((len+obj->buff_count)>obj->max_len)
	{
		//���ݴ���
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
 *@bref �ͷ�����
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
////		ptr->buff//����֡ͷ
//		ptr->buff_count=14;//֡ͷ�ĳ���
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
	//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1
	uint16_t wcrc=0XFFFF;
	//�����м����
	uint8_t temp = 0;
	//�������
	int i=0,j=0;
	//ѭ������ÿ������
	for(i=0;i<len;i++)
	{
		//����λ������crc�Ĵ������
		temp=*buf&0X00FF;
		//ָ���ַ���ӣ�ָ���¸�����
		buf++;
		//�����ݴ���crc�Ĵ���
		wcrc^=temp;
		//ѭ����������
		for(j=0;j<8;j++)
		{
		  //�ж����Ƴ����ǲ���1�������1�������ʽ�������
		  if(wcrc&0X0001)
		  {
				//�Ƚ���������һλ
				wcrc>>=1;
				//������Ķ���ʽ�������
				wcrc^=0XA001;
		  }
		  //�������1����ֱ���Ƴ�
		  else
		  {
				//ֱ���Ƴ�
				wcrc>>=1;
		  }
		}
	}
	//crc��ֵ
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