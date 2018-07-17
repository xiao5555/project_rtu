#include "Application/GUI/gui.h"
#include "Inc/sysinfo.h"
static void MAIN_CustomSpecialEffects(char key_val);
static  void MAIN_VIEW_Scanning(void *arg);
static void MAIN_VIEW_Run(int argc,char *argv[]);
static void MAIN_ImageInit(void);
static void(*RefreshArray[5])(void *arg);
static void Refresh_RainHour(void *arg);
static void Refresh_RainDay(void *arg);
static void Refresh_Water(void *arg);
static void Refresh_Rssis(void *arg);
static void Refresh_SysTime(void *arg);



static SCREEN_TypeDef MAIN_SCREEN_INFO={
	.state=STATE_INIT,
	.text_content[0].content="   ʱ������ %2.1f��mm��",
//	.text_content[0].font_size=DEFAULT_FONT_SIZE,
//	.text_content[0].x=MAIN_BASE_OFFSET_X,
//	.text_content[0].y=MAIN_BASE_OFFSET_Y+0*DEFAULT_FONT_SIZE,
	.text_content[1].content="   �������� %2.1f��mm��",
//	.text_content[1].font_size=DEFAULT_FONT_SIZE,
//	.text_content[1].x=MAIN_BASE_OFFSET_X,
//	.text_content[1].y=MAIN_BASE_OFFSET_Y+1*DEFAULT_FONT_SIZE,
	.text_content[2].content="   ˮ  λ�� %2.1f��m��",
//	.text_content[2].font_size=DEFAULT_FONT_SIZE,
//	.text_content[2].x=MAIN_BASE_OFFSET_X,
//	.text_content[2].y=MAIN_BASE_OFFSET_Y+2*DEFAULT_FONT_SIZE,
	.screen_name[0]="Config_VIEW_ID",
	.screen_total_num=1,
	.self_name="Main_View_ID",
	.focus_point=0,
};
/********************************************************************
 *@bref home ����ĳ�ʼ��
 *     
 *@ret 
***********************************************************************/
void MAIN_VIEW_Init(void)
{
	MAIN_ImageInit();
	USER_GUI_MANAGER[MAIN_VIEW_ID].RunProcess=MAIN_VIEW_Run;
	USER_GUI_MANAGER[MAIN_VIEW_ID].RunInit=MAIN_VIEW_Scanning;
	USER_GUI_MANAGER[MAIN_VIEW_ID].screen_info=&MAIN_SCREEN_INFO;
	RefreshArray[GET_SUB_ID(MSG_HOUR_RAIN)]=Refresh_RainHour;
	RefreshArray[GET_SUB_ID(MSG_DAY_RAIN)]=Refresh_RainDay;
	RefreshArray[GET_SUB_ID(MSG_WATER)]=Refresh_Water;
	RefreshArray[GET_SUB_ID(MEG_SIM_RSISS)]=Refresh_Rssis;
	RefreshArray[GET_SUB_ID(MSG_RTC_UPDATE)]=Refresh_SysTime;
}
static void Refresh_RainHour(void *arg)
{
	SetRainHour((uint32_t)arg);
//	LCD_ClearRectangle(2,80,2,192);
	LCD_DisString(FONT_15x16,1,2,(uint8_t*)MAIN_SCREEN_INFO.text_content[0].content,GetRainHour());
}
static void Refresh_RainDay(void *arg)
{
	SetRainDay((uint32_t)arg);
	//	LCD_ClearRectangle(4,80,4,192);
	LCD_DisString(FONT_15x16,1,4,(uint8_t*)MAIN_SCREEN_INFO.text_content[1].content,GetRainDay());
				
}
static void Refresh_Water(void *arg)
{
	SetWaterDay((uint32_t)arg);
	//	LCD_ClearRectangle(6,80,6,192);
	LCD_DisString(FONT_15x16,1,6,(uint8_t*)MAIN_SCREEN_INFO.text_content[2].content,GetWaterDay());
}
static void Refresh_Rssis(void *arg)
{
	
}
static void Refresh_SysTime(void *arg)
{
	LCD_DisString(FONT_5x8,1,7,(uint8_t*)arg);
}

/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static void MAIN_ImageInit(void)
{
	MAIN_SCREEN_INFO.image_content->p_image=bmp1;
	MAIN_SCREEN_INFO.image_content->height=20;
	MAIN_SCREEN_INFO.image_content->width=30;
	MAIN_SCREEN_INFO.image_content->x_start=100;
	MAIN_SCREEN_INFO.image_content->y_start=0;
}
/********************************************************************
 *@bref �������к���,������յ���Ϣ
 *     
 *@ret 
***********************************************************************/
void MAIN_VIEW_Run(int argc,char *argv[])
{
	void* val=0;
	OS_MSG_SIZE get_size;
	OS_MSG_TYPE OS_MSG_TYPE;
	val= GUI_GetMsgProcess(MAIN_CustomSpecialEffects,&OS_MSG_TYPE,&get_size);
	if(IS_MSG_ID(OS_MSG_TYPE,KEY_GET_VAL_ID))
	{
		switch((char)(char*)val)
		{
			case KEY_MENU://�˵�����
					GUI_PUSH("Config_View_ID");//�������ý���
				break;
			default:
			break;
		}
	}else
	{
		if(IS_MSG_ID(OS_MSG_TYPE,MAIN_VIEW_ID))
		{
			RefreshArray[GET_SUB_ID(OS_MSG_TYPE)](val);//ˢ�£���Ϊֻ���������漰��ˢ���������Ե����������Ϳ���
		}
	}
}
/********************************************************************
 *@bref //lcd���������ʼ������ʼ������0
 *     arg ��ʾ���ǵڼ�ҳ
 *@ret 
***********************************************************************/
 void MAIN_VIEW_Scanning(void *arg)
{
	switch((uint8_t)(arg))
	{
		case 0:
				LCD_ClearScreen();
//				LCD_display_graphic_192x64(MAIN_SCREEN_INFO.image_content->p_image);
				LCD_DisString(FONT_15x16,1,2,(uint8_t*)MAIN_SCREEN_INFO.text_content[0].content,GetRainHour());
				LCD_DisString(FONT_15x16,1,4,(uint8_t*)MAIN_SCREEN_INFO.text_content[1].content,GetRainDay());
				LCD_DisString(FONT_15x16,1,6,(uint8_t*)MAIN_SCREEN_INFO.text_content[2].content,GetWaterDay());
		break;
		default:
			break;		
	}
	
}
/********************************************************************
 *@bref //�Զ���İ���������Ч
 *     
 *@ret 
***********************************************************************/
static void MAIN_CustomSpecialEffects(char key_val)
{
	switch(key_val)
	{		
		case KEY_UP:
				
		break;
		case KEY_DOWN:
			
		break;
	}
}

