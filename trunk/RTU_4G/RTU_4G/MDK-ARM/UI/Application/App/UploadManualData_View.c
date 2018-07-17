#include "Application/GUI/gui.h"

static  void UPLOAD_MANUAL_VIEW_Scanning(void *arg);
static void UPLOAD_MANUAL_VIEW_Run(int argc,char *argv[]);
static uint8_t run_mode=0;
static uint32_t old_5s_show;
static SCREEN_TypeDef UPLOAD_MANUAL_SCREEN_INFO={
	.self_name="Upload_Manual_Data_VIEW_ID",
};
/********************************************************************
 *@bref home 界面的初始化
 *     
 *@ret 
***********************************************************************/
void UPLOAD_MANUAL_VIEW_Init(void)
{
	USER_GUI_MANAGER[UPLOAD_MANUAL_DATA_VIEW_ID].RunProcess=UPLOAD_MANUAL_VIEW_Run;
	USER_GUI_MANAGER[UPLOAD_MANUAL_DATA_VIEW_ID].RunInit=UPLOAD_MANUAL_VIEW_Scanning;
	USER_GUI_MANAGER[UPLOAD_MANUAL_DATA_VIEW_ID].screen_info=&UPLOAD_MANUAL_SCREEN_INFO;
}
/********************************************************************
 *@bref 界面运行函数,处理接收的消息
 *     
 *@ret 
***********************************************************************/
void UPLOAD_MANUAL_VIEW_Run(int argc,char *argv[])
{	
	void *val;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	val= GUI_GetMsgProcess(0,&OS_MSG_TYPE,&get_size);
	switch(run_mode)
	{
		case 0:
				if((HAL_GetTick()-old_5s_show)>(3*1000))
					GUI_POP();
		break;
		case 1:			
				if(IS_MSG_ID(OS_MSG_TYPE,MSG_DEVICE_SET_RAIN))
				{
					if((uint32_t)(val)==1)//设置成功
					{
						LCD_DisString(FONT_15x16,1,5,(uint8_t*)"   设置成功!!!");
					}
					if((uint32_t)(val)==2)//设置失败
					{
						LCD_DisString(FONT_15x16,1,5,(uint8_t*)"   设置失败!!!");
					}
					old_5s_show=HAL_GetTick();
					run_mode=0;
				}else{
						if((HAL_GetTick()-old_5s_show)>(8*1000))
						{
							LCD_DisString(FONT_15x16,1,5,(uint8_t*)"   设置超时!!!");
							old_5s_show=HAL_GetTick();
							run_mode=0;
						}
				}
		break;
		default:
			break;
	}
	
}
/********************************************************************
 *@bref //lcd驱动界面初始化
 *     
 *@ret 
***********************************************************************/
 void UPLOAD_MANUAL_VIEW_Scanning(void *arg)
{
	switch((uint32_t)(arg))
	{
		case 0:
			MsgPut_GuiToClient(MSG_DEVICE_SET_RAIN,&SET_RAIN_VAL.val,sizeof(float));//发送消息给user
			LCD_ClearScreen();
			if(SET_RAIN_VAL.val==0xffff)
			{
				run_mode=0;
				old_5s_show=HAL_GetTick();
				UPLOAD_MANUAL_SCREEN_INFO.text_content[0].content="   请输入有效值!!!";
			}else
			{
				run_mode=1;
				old_5s_show=HAL_GetTick();
				UPLOAD_MANUAL_SCREEN_INFO.text_content[0].content="   正在上报*****";
			}
				LCD_DisString(FONT_15x16,1,3,(uint8_t*)UPLOAD_MANUAL_SCREEN_INFO.text_content[0].content);
		break;
	
		default:
			break;
	}
	
	
}
