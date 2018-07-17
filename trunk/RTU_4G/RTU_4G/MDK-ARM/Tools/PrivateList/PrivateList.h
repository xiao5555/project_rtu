#ifndef _PRIVATE_LIST_H_
#define _PRIVATE_LIST_H_

#include <stdint.h>
/************内部使用***************/
struct SIS_List_Node{
	struct SIS_List_Node* Prev;
	struct SIS_List_Node* Next;
	char *DataType;//数据类型
	void* Elem;
};
/**********************************/

struct SIS_List{
	struct SIS_List_Node* NodeHead;
	struct SIS_List_Node* NodeTail;
	uint16_t Capacity;
	uint16_t (*GetCount)(struct SIS_List* list);
	int (*Append)(struct SIS_List* list, void *elem);//末尾添加	
	void *(*TakeFront)(struct SIS_List* list);//从头部取走
	struct SIS_List_Node* (*PeekListNode)(struct SIS_List* list);//查看头部
	void *(*TakeFrontByType)(struct SIS_List* list,char *type);//从头开始查找需要的类型
	void (*DelElemByType)(struct SIS_List* list,char *type,void (*Delete)(void* address));//在链表中删除指定数据类型的成员
};
struct SIS_List* CreateSIS_List(uint16_t capacity );
void ClearSIS_List(struct SIS_List* this,void Delete(void* ));
#endif//_PRIVATE_LIST_H_

