/********************************************************************
 * custom_timer.c
 * .Description
 *  定时基准时间 = 硬件定时时间*CUSTOM_TmrUpdateCtr 
 *  定时时间     = 定时基准时间* dly|period（来自CUSTOM_TimerCreat()函数 ）
 *  Author
 *  cgwu
 *  Date
 *  Version V5.0 
 *  V4.0 允许创建最多32个定时器函数
 *  V5.0 允许创建任意多个的定时器函数  2017年9月6日16:09:38
 ********************************************************************/
#include "PrivateTimer/PrivateTimer.h"
#include "stm32l4xx_hal.h"
/*******************************内部配置参数*********************************************************/

uint32_t CUSTOM_TmrUpdateCtr;//计数更新值
uint32_t CUSTOM_TmrUpdateCnt;//计数重载值
static tmr tmr_TaskTable[MAX_TIMERTASKNUM];//结构体数组

/*********************************私有函数********************************************************************/
static int CUSTOM_TimerCheckFreeId(void);
static int CUSTOM_TimerTaskClear(tmr_callback_point DleFuc);//删除指定函数
/*************************************************************************************************************************
void CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg) 

描述：创建的定时器函数 ,可以在任何时候调用
	pfuction    回掉函数，实现定时器的初始化，也可以为0，用于不需要在这进行初始化定时器的情况
	arg         传递参数
返回值 ：0  初始化完成
         -1 配置出错
*************************************************************************************************************************/
int CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg)
{
	(void)&arg;
	CUSTOM_TmrUpdateCtr=DEVISION_HardwareTimer;//计数更新值
    CUSTOM_TmrUpdateCnt=CUSTOM_TmrUpdateCtr;//计数重载值
	if(pfuction!=0)
	{
		pfuction();
	}
	return 0;
	
}
/*************************************************************************************************************************
int CUSTOM_TimerCreat(uint8_t tmr_id,tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period)                          *

描述：创建的定时器函数 ,可以在任何时候调用
	tmr_id 		每个函数有一个自己的id号，暂时不超过 32个
	pfuction    回掉函数，有一个void * 参数
	arg         传递参数
    dly         第一次延时时间
    period      周期延时时间//如果为0，则dly时间完成后，会取消下次开启，如果dly和period都为0 则立刻关闭该定时器
return 0  	ok
	  -1   参数无效
      -2   删除该定时器函数失败

*************************************************************************************************************************/
int CUSTOM_TimerCreat(tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period)
{
	if((dly+period)==0) //关闭定时器
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

描述：任务查询函数 ，时间到了之后执行任务，在定时器中调用

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
					if(tmr_TaskTable[i].period==0)tmr_TaskTable[i].enable=0;//清除查询标志位
					(*tmr_TaskTable[i].fuc)(tmr_TaskTable[i].tmr_arg);//执行函数
				}
			}
			else
			{
				tmr_TaskTable[i].remain--;
				if(tmr_TaskTable[i].remain==0)
				{
					tmr_TaskTable[i].remain=tmr_TaskTable[i].period;
					(*tmr_TaskTable[i].fuc)(tmr_TaskTable[i].tmr_arg);//执行函数
				}
			}
		}
	 }
}

/*************************************************************************************************************************
int CUSTOM_TimerTaskClear(tmr_callback_point DleFuc)

描述：删除某个函数注册的任务
返回值： 0  删除OK
		-1  没有找到相应注册函数

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

描述：用于查找已被释放的资源
返回值： >=0  释放的资源ID

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














