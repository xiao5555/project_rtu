#ifndef _PRIVATE_TIMER_H
#define _PRIVATE_TIMER_H
#include <stdint.h>
/*******************************���ò���*********************************************************/
typedef  void                 (*tmr_HardWareInit_point)(void);  
typedef  void                 (*tmr_callback_point)(void *p_arg);

typedef struct
{
	uint8_t enable;//��ʱ��ʹ��
	uint32_t period;//����ֵ
	uint32_t dly;//��ʱֵ
	uint32_t remain;//ʣ��ֵ
	tmr_callback_point fuc;//�ص�����
	void *tmr_arg;
}tmr;
/*******************************�ɲü������ò���*********************************************************/


#define MAX_TIMERTASKNUM          5//���ӵ�е������� ϵͳ֧�ֵ����������
#define DEVISION_HardwareTimer    1//��Ӳ����ʱ�����з�Ƶ���õ���ֵ���Ƕ�ʱ�Ļ�׼ʱ��



/*************************************���ý���************************************************************/


/*******************************�ⲿ����*********************************************************/
int CUSTOM_TimerCreat(tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period);//������ʱ����
int CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg);//��ʼ����ʱ��
void CUSTOM_TimerTask(void);//������жϣ��ú��������ж���ʹ�ã������в�Ҫ��������


#endif// _PRIVATE_TIMER_H.h





















