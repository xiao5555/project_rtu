#include "Application/GUI/gui.h"
#include "PrivateTimer/PrivateTimer.h"

 GUI_TypeDef *GUI_TAB_VIEW[GUI_SCREEN_NUM]={0};//用于记录界面切换
 GUI_TypeDef *POINT_GUI_CURRENT_VIEW=NULL;//当前的指向的界面
 GUI_TypeDef USER_GUI_MANAGER[GUI_SCREEN_NUM]={0};//界面管理区
 static GUI_TypeDef * SearchScreenByName(char *name);

/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void APP_GUI_Init(void)
{
	GUI_MsgInit();
	MAIN_VIEW_Init();
	CONFIG_VIEW_Init();
	MANUAL_SET_VIEW_Init();
	SET_RAIN_MAIN_VIEW_Init();
	SET_RAIN_VALUE_VIEW_Init();
	HINT_VIEW_Init();
	UPLOAD_MANUAL_VIEW_Init();
	PARAMETER_SET_VIEW_Init();
	INSTALL_TEST_VIEW_Init();
	CLEAR_HISTORICAL_VIEW_Init();
	VERSION_VIEW_Init();
	POINT_GUI_CURRENT_VIEW=&USER_GUI_MANAGER[MAIN_VIEW_ID];//设置记录默认值
	CUSTOM_TimerCreat(APP_GUI_Exc,0,10,20);
}

/********************************************************************
 *@bref 界面处理函数，在周期定时器中调用
 * 
 *@ret 
***********************************************************************/
void APP_GUI_Exc(void*arg)
{
	switch(POINT_GUI_CURRENT_VIEW->screen_info->state)
	{
		case STATE_IDLE:
			
		break;
		case STATE_INIT:
				POINT_GUI_CURRENT_VIEW->RunInit(0);
				POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_RUN;
		break;
		case STATE_RUN:
				POINT_GUI_CURRENT_VIEW->RunProcess(0,0);
		break;
		default:
			
		break;
	}
}
/********************************************************************
 *@bref  POP 到上个界面
 *     
 *@ret 
***********************************************************************/
 void POP_ScreenInfo(void)
  {
	  uint8_t count=0;
	  for(;GUI_TAB_VIEW[count];count++);//查找最高记录
	  
	  POINT_GUI_CURRENT_VIEW->screen_info->focus_point=0;//焦点位置清空
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_IDLE;//睡眠
	  POINT_GUI_CURRENT_VIEW=GUI_TAB_VIEW[count-1];
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_INIT;//唤醒
	  GUI_TAB_VIEW[count-1]=0;
  }
/********************************************************************
   *@bref PUSH该界面
   *     
   *@ret 
***********************************************************************/
  void PUSH_ScreenInfo(char *name)
  {
	  POINT_GUI_CURRENT_VIEW->screen_info->focus_point=0;//焦点位置清空
	  POINT_GUI_CURRENT_VIEW->screen_info->state=STATE_IDLE;
	  GUI_TypeDef *  val=SearchScreenByName(name); 
	  if(val)
	  {
		  uint8_t count=0;
		  for(;GUI_TAB_VIEW[count];count++);//查找最高记录
		  
		  GUI_TAB_VIEW[count]=POINT_GUI_CURRENT_VIEW;//座记录
			val->screen_info->state=STATE_INIT;
			POINT_GUI_CURRENT_VIEW=val;
			
	  }else
	  {		  
		 Debug_P("没有该界面，回到默认界面\r\n");
		 USER_GUI_MANAGER[MAIN_VIEW_ID].screen_info->state=STATE_INIT;
		 POINT_GUI_CURRENT_VIEW=&USER_GUI_MANAGER[MAIN_VIEW_ID];//
		  
	  }
  }
/********************************************************************
   *@bref 
   *     
   *@ret 
***********************************************************************/
  static GUI_TypeDef * SearchScreenByName(char *name)
  {
	for(int i=0;i<GUI_SCREEN_NUM;i++)
	  {
		if(strcmp(USER_GUI_MANAGER[i].screen_info->self_name,name)==0)
		{
			return &USER_GUI_MANAGER[i];
		}
	  }
	  return NULL;
  }
/********************************************************************
   *@bref 界面请求刷新函数
   *     
   *@ret 
***********************************************************************/  
void GUI_RequestRefresh(GUI_TypeDef *ptr)
{
	ptr->RequestRefresh=1;
}
/********************************************************************
 *@bref 当前界面刷新函数
 *     
 *@ret 
***********************************************************************/
void GUI_CurrentScreenRefresh(void)
{
//	if(POINT_GUI_CURRENT_VIEW->RequestRefresh)
//	{
//		POINT_GUI_CURRENT_VIEW->RequestRefresh=0;
//		POINT_GUI_CURRENT_VIEW->RunInit(0);
//		Debug("界面刷新存在bug，暂时只刷新第一屏界面\r\n");
//	}
}
