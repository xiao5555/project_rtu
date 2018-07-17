#ifndef _PRIVATE_TIMER_H
#define _PRIVATE_TIMER_H
#include <stdint.h>
/*******************************内置参数*********************************************************/
typedef  void                 (*tmr_HardWareInit_point)(void);  
typedef  void                 (*tmr_callback_point)(void *p_arg);

typedef struct
{
	uint8_t enable;//定时器使能
	uint32_t period;//重载值
	uint32_t dly;//延时值
	uint32_t remain;//剩余值
	tmr_callback_point fuc;//回掉函数
	void *tmr_arg;
}tmr;
/*******************************可裁剪的配置参数*********************************************************/


#define MAX_TIMERTASKNUM          5//最大拥有的任务数 系统支持的最大任务数
#define DEVISION_HardwareTimer    1//对硬件定时器进行分频，得到的值就是定时的基准时间



/*************************************配置结束************************************************************/


/*******************************外部函数*********************************************************/
int CUSTOM_TimerCreat(tmr_callback_point pfuction,void *arg,uint32_t dly,uint32_t period);//创建定时任务
int CUSTOM_TimerInit(tmr_HardWareInit_point pfuction,void *arg);//初始化定时器
void CUSTOM_TimerTask(void);//任务的判断，该函数放在中断中使用，函数中不要出现阻塞


#endif// _PRIVATE_TIMER_H.h





















