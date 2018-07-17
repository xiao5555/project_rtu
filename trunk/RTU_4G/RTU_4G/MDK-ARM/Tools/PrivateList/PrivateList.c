#include "PrivateList/PrivateList.h"
#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <string.h>
/*******************************内部配置参数*********************************************************/

/*********************************私有函数********************************************************************/
static	uint16_t GetCount(struct SIS_List* list);
static  void * TakeFrontByType(struct SIS_List* list,char *type);//从头开始查找需要的类型
static void DelElemByType(struct SIS_List* list,char *type,void (*Delete)(void* address));//在链表中删除指定数据类型的成员
/*************************************************************************************************************************
static	uint16_t GetCount(struct SIS_List* list)
描述：得到挂载链表成员个数
	list         链表
返回值 ：>=0  
*************************************************************************************************************************/
static	uint16_t GetCount(struct SIS_List* list)
{
	uint16_t count = 0;
	struct SIS_List_Node* node = list->NodeHead;
	while(node)
	{
		count++;
		node = node->Next;
	}
	return count;
}
/*************************************************************************************************************************
static	void * TakeFront(struct SIS_List* list)
描述：从头部取走
	list         链表
返回值 ：NULL or 挂载地址  
*************************************************************************************************************************/
static	void * TakeFront(struct SIS_List* list)//
{
	void *_elem = NULL;
	struct SIS_List_Node* node = list->NodeHead;
	if(node)
	{
		list->NodeHead = node->Next;
		list->NodeHead->Prev = NULL;
		_elem = node->Elem;
		free(node);
	}
	return _elem;
}
/*************************************************************************************************************************
static	void * TakeFront(struct SIS_List* list)
描述：从头部取走
	list         链表
返回值 ：NULL or 挂载地址  
*************************************************************************************************************************/
static	struct SIS_List_Node* PeekListNode(struct SIS_List* list)//查看头部
{
	return list->NodeHead;
}
/*************************************************************************************************************************
static	void * Append(struct SIS_List* list)
描述：从尾部挂载
	list         链表
返回值 ：NULL or 挂载地址  
*************************************************************************************************************************/
static	int Append(struct SIS_List* list, void *elem)//末尾添加
{
	struct SIS_List_Node* node = malloc(sizeof(struct SIS_List_Node));
	if(node == NULL)
		return -1;
	memset(node,0,sizeof(struct SIS_List_Node));
	node->Elem = elem;
	uint16_t count = GetCount(list);
	if((count == 0)&&(list->Capacity))
	{
		list->NodeTail = list->NodeHead = node;
	}
	else
	{
		if(count >= list->Capacity)
		{
			free(node);
			return -1;
		}
		list->NodeTail->Next = node;
		node->Prev = list->NodeTail;
		list->NodeTail = node;
	}
	return 0;
}
/*************************************************************************************************************************
static	void * TakeFront(struct SIS_List* list)
描述：从头部取走
	list         链表
返回值 ：NULL or 挂载地址  
*************************************************************************************************************************/
struct SIS_List* CreateSIS_List(uint16_t capacity )
{
	struct SIS_List* list = malloc(sizeof(struct SIS_List));
	if(list)
	{
		memset(list,0, sizeof(struct SIS_List));
		list->Capacity = capacity;
		list->TakeFront = TakeFront;
		list->PeekListNode = PeekListNode;
		list->Append = Append;
		list->GetCount = GetCount;
		list->DelElemByType=DelElemByType;
		list->TakeFrontByType=TakeFrontByType;
	}
	return list;
}
/*************************************************************************************************************************
void ClearSIS_List(struct SIS_List* this_buff,void (*Delete)(void* ))
描述：
	list         链表
返回值 ：NULL or 挂载地址  
*************************************************************************************************************************/
void ClearSIS_List(struct SIS_List* this_buff,void (*Delete)(void* ))
{ 
	void* item = this_buff->TakeFront(this_buff);
	while(item)
	{	
		if(Delete)
			(*Delete)(item);
		item = this_buff->TakeFront(this_buff);
	}
}

/********************************************************************
 *@bref //从头开始查找需要的类型
 *     
 *@ret 
***********************************************************************/
static  void *TakeFrontByType(struct SIS_List* list,char *type)
{
	if(GetCount(list)==0)
	{
		return NULL;
	}
	struct SIS_List_Node* node = list->NodeHead;
	void *_elem = NULL;
	while(node)
	{
		if(strcmp(node->DataType,type)==0)
		{
			_elem=node->Elem;	
			if(node==list->NodeHead)
			{
				list->NodeHead=node->Next;
			
			}else
			{
				node->Prev->Next=node->Next;			
			}				
			free(node);
			return _elem;
		}
		node=node->Next;
	}
	return _elem;
}
/********************************************************************
 *@bref //在链表中删除指定数据类型的成员，成员的内存删除由自己的函数释放，而且只释放里面的内存，不要释放节点内存
 *     
 *@ret 
***********************************************************************/
static void DelElemByType(struct SIS_List* list,char *type,void (*Delete)(void* address))
{
	if(GetCount(list)==0)
	{
		return;
	}
	struct SIS_List_Node* node = list->NodeHead;
	while(node)
	{
		if(strcmp(node->DataType,type)==0)
		{
			if(Delete)
			{
				 Delete(node->Elem);	
			}
			if(node==list->NodeHead)
			{
				list->NodeHead=node->Next;
			}else
			{
				node->Prev->Next=node->Next;			
			}			
			free(node);
		}
		node=node->Next;
	}
}








