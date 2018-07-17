#include "Application/GUI/gui.h" 
static OS_MSG_Q GUI_Msg;
static OS_MSG_Q ServerToClient_Msg;
//static char *KEY_TABLE_VALUE[]={"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f","g","h","i","j",
//"k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",".","#","+","-","esc","enter","menu","up","down"};
/*****************************************************************************************************************
	esc->@
	enter->^
	menu->$
	up->%
	down->&
*****************************************************************************************************************/
static char KEY_TABLE_VALUE[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.','#','+','-','@','^','$','%','&'};

/********************************************************************
 *@bref 得到按键值，以字符的形式
 *     
 *@ret 
***********************************************************************/
char GUI_KeyGetValue(void(*EventKeyCallback)(char val),uint8_t *get_physical_value)
{
	uint8_t key_val=KEY_GetValue();
	if(key_val)
	{
		if(get_physical_value)
		{
			*get_physical_value=key_val;
		}
		if(EventKeyCallback)
		{
			EventKeyCallback(KEY_TABLE_VALUE[key_val]);
		}
		return (KEY_TABLE_VALUE[key_val]);
	}
	return 0;
}

/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void* GUI_GetMsgProcess(void(*EventKeyCallback)(char val),OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size)
{
		void *val=MsgGet(get_msg_type,get_size);
		if(IS_MSG_ID(*get_msg_type,KEY_GET_VAL_ID))
		{
			if(EventKeyCallback)
			{
				EventKeyCallback((char)(char*)val);
			}
		}
		return val;
}
/********************************************************************
 *@bref 处理当按键按下后更改的图标，
 *     
 *@ret 
***********************************************************************/
void GUI_DisKeyEvent(void* arg)
{
	
}
/********************************************************************
 *@bref GUI 的消息初始化，最多可接受15个消息
 *     
 *@ret 
***********************************************************************/
void GUI_MsgInit(void)
{
	uint8_t err;
	OS_MsgPoolInit(&err);
	OS_MsgQInit(&GUI_Msg,15);
	OS_MsgQInit(&ServerToClient_Msg,15);
}
/********************************************************************
 *@bref 发消息到送到GUI控制台，(消息类型使用时间戳的位置)
 *     msg_type 消息类型，
 *		arg      消息
 *		size     大小
 *@ret 
***********************************************************************/
void MsgPut(OS_MSG_TYPE msg_type,void *arg,OS_MSG_SIZE size)
{
	uint8_t err;
	OS_MsgQPut(&GUI_Msg,arg,size,OS_OPT_POST_FIFO,msg_type,&err);
//	GUI_RequestRefresh(&USER_GUI_MANAGER[GET_SCREEN_ID(msg_type)]);//指定要刷新的界面
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/

void *MsgGet(OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size)
{
	uint8_t err;
	return OS_MsgQGet(&GUI_Msg,get_size,get_msg_type,&err);
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
void MsgPut_GuiToClient(OS_MSG_TYPE msg_type,void *arg,OS_MSG_SIZE size)
{
	uint8_t err;
	OS_MsgQPut(&ServerToClient_Msg,arg,size,OS_OPT_POST_FIFO,msg_type,&err);
}
/********************************************************************
 *@bref    reveived GUI msg
 *     
 *@ret 
***********************************************************************/

void *MsgGet_GuiToClient(OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size)
{
	uint8_t err;
	return OS_MsgQGet(&ServerToClient_Msg,get_size,get_msg_type,&err);
}

void CreateParSetView()
{
	
}
