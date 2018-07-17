#ifndef __MIDDLE_H_
#define __MIDDLE_H_
#include "Middle/Inc/config.h"
#include <stdint.h>
typedef  uint32_t   OS_MSG_TYPE;
typedef  uint16_t   OS_MSG_SIZE; 
#define KEY_ENTER '^'
#define KEY_ESC   '@'
#define KEY_UP    '%'
#define KEY_DOWN  '&'
#define KEY_MENU  '$'
char GUI_KeyGetValue(void(*EventKeyCallback)(char val),uint8_t *get_physical_value);
void GUI_MsgInit(void);
void *MsgGet(OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size);
void* GUI_GetMsgProcess(void(*EventKeyCallback)(char val),OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size);
void MsgPut_GuiToClient(OS_MSG_TYPE msg_type,void *arg,OS_MSG_SIZE size);

/**************************************************************Ex Fuction****************************************************************/
void MsgPut(OS_MSG_TYPE msg_type,void *arg,OS_MSG_SIZE size);
void *MsgGet_GuiToClient(OS_MSG_TYPE *get_msg_type,OS_MSG_SIZE *get_size);

#endif//__MIDDLE_H_
