/********************************************************************
 * custom_timer.c
 * .Description
 *  ��ʱ��׼ʱ�� = Ӳ����ʱʱ��*CUSTOM_TmrUpdateCtr 
 *  ��ʱʱ��     = ��ʱ��׼ʱ��* dly|period������CUSTOM_TimerCreat()���� ��
 *  Author
 *  cgwu
 *  Date
 *  Version V5.0 
 *  V4.0 ���������32����ʱ������
 *  V5.0 �������������Ķ�ʱ������  2017��9��6��16:09:38
 ********************************************************************/
#include "PrivateTimer/PrivateTimer.h"
#include "stm32l4xx_hal.h"
/*******************************�ڲ����ò���*********************************************************/

uint32_t CUSTOM_TmrUpdateCtr;//��������ֵ
uint32_t CUSTOM_TmrUpdateCnt;//��������ֵ
static tmr tmr_TaskTable[MAX_TIMERTASKNUM];//�ṹ������

/*********************************˽�к���********************************************************************/
static int CUSTOM_TimerCheckFreeId(void);
static int CUSTOM_TimerTaskClear(tmr_callback_point DleFuc);//ɾ��ָ������
/*************************************************************************************************************************
void CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg) 

�����������Ķ�ʱ������ ,�������κ�ʱ�����
	pfuction    �ص�������ʵ�ֶ�ʱ���ĳ�ʼ����Ҳ����Ϊ0�����ڲ���Ҫ������г�ʼ����ʱ�������
	arg         ���ݲ���
����ֵ ��0  ��ʼ�����
         -1 ���ó���
*************************************************************************************************************************/
int CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg)
{
	(void)&arg;
	CUSTOM_TmrUpdateCtr=DEVISION_HardwareTimer;//��������ֵ
    CUSTOM_TmrUpdateCnt=CUSTOM_TmrUpdateCtr;//��������ֵ
	if(pfuction!=0)
	{
		pfuction();
	}
	return 0;
	
}
/*************************************************************************************************************************
int CUSTOM_TimerCreat(uint8_t tmr_id,tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period)                          *

�����������Ķ�ʱ������ ,�������κ�ʱ�����
	tmr_id 		ÿ��������һ���Լ���id�ţ���ʱ������ 32��
	pfuction    �ص���������һ��void * ����
	arg         ���ݲ���
    dly         ��һ����ʱʱ��
    period      ������ʱʱ��//���Ϊ0����dlyʱ����ɺ󣬻�ȡ���´ο��������dly��period��Ϊ0 �����̹رոö�ʱ��
return 0  	ok
	  -1   ������Ч
      -2   ɾ���ö�ʱ������ʧ��

*************************************************************************************************************************/
int CUSTOM_TimerCreat(tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period)
{
	if((dly+period)==0) //�رն�ʱ��
	{
		if(CUSTOM_TimerTaskClear(pfuction))return -2;
		return 0;
	}
	uint32_t creat_id=CUSTOM_TimerCheckFreeId();
	if(creat_id>=MAX_TIMERTASKNUM)return -1;
	if(pfuction==0)return -1;
	tmr_TaskTable[creat_id].fuc =pfuction;
	tmr_TaskTable[creat_id].tmr_arg=arg;
	tmr_TaskTable[creat_id].dly=dly;
	tmr_TaskTable[creat_id].period=period;
	tmr_TaskTable[creat_id].remain=period;	
	tmr_TaskTable[creat_id].enable=1;
	return 0;
}

/*************************************************************************************************************************
void CUSTOM_TimerTask(void)

�����������ѯ���� ��ʱ�䵽��֮��ִ�������ڶ�ʱ���е���

*************************************************************************************************************************/

void CUSTOM_TimerTask(void)
{
	uint32_t i=0;
	CUSTOM_TmrUpdateCtr--;
	if(CUSTOM_TmrUpdateCtr!=0)return;
	CUSTOM_TmrUpdateCtr=CUSTOM_TmrUpdateCnt;
	for(i=0;i<MAX_TIMERTASKNUM;i++)
	 {
		if(tmr_TaskTable[i].enable)
		{
			if(tmr_TaskTable[i].dly)
			{
				tmr_TaskTable[i].dly--;
				if(tmr_TaskTable[i].dly==0)
				{
					if(tmr_TaskTable[i].period==0)tmr_TaskTable[i].enable=0;//�����ѯ��־λ
					(*tmr_TaskTable[i].fuc)(tmr_TaskTable[i].tmr_arg);//ִ�к���
				}
			}
			else
			{
				tmr_TaskTable[i].remain--;
				if(tmr_TaskTable[i].remain==0)
				{
					tmr_TaskTable[i].remain=tmr_TaskTable[i].period;
					(*tmr_TaskTable[i].fuc)(tmr_TaskTable[i].tmr_arg);//ִ�к���
				}
			}
		}
	 }
}

/*************************************************************************************************************************
int CUSTOM_TimerTaskClear(tmr_callback_point DleFuc)

������ɾ��ĳ������ע�������
����ֵ�� 0  ɾ��OK
		-1  û���ҵ���Ӧע�ắ��

*************************************************************************************************************************/
static int CUSTOM_TimerTaskClear(tmr_callback_point DleFuc)
{
	uint32_t fuc_id;
	for(fuc_id=0;fuc_id<MAX_TIMERTASKNUM;fuc_id++)
	{
		if(tmr_TaskTable[fuc_id].enable)
		{
			if(tmr_TaskTable[fuc_id].fuc==DleFuc)
			{
				tmr_TaskTable[fuc_id].enable=0;
				return 0;
			}
		}
	}
	return -1;
}


/*************************************************************************************************************************
static int CUSTOM_TimerCheckFreeId(void)

���������ڲ����ѱ��ͷŵ���Դ
����ֵ�� >=0  �ͷŵ���ԴID

*************************************************************************************************************************/
static int CUSTOM_TimerCheckFreeId(void)
{
	uint32_t free_id;
	for(free_id=0;free_id<MAX_TIMERTASKNUM;free_id++)
	{
		if(tmr_TaskTable[free_id].enable==0)break;
	}
	return free_id;
}














