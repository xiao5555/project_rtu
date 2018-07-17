#include "PrivateList/PrivateList.h"
#include "stm32l4xx_hal.h"
#include <stdlib.h>
#include <string.h>
/*******************************�ڲ����ò���*********************************************************/

/*********************************˽�к���********************************************************************/
static	uint16_t GetCount(struct SIS_List* list);
static  void * TakeFrontByType(struct SIS_List* list,char *type);//��ͷ��ʼ������Ҫ������
static void DelElemByType(struct SIS_List* list,char *type,void (*Delete)(void* address));//��������ɾ��ָ���������͵ĳ�Ա
/*************************************************************************************************************************
static	uint16_t GetCount(struct SIS_List* list)
�������õ����������Ա����
	list         ����
����ֵ ��>=0  
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
��������ͷ��ȡ��
	list         ����
����ֵ ��NULL or ���ص�ַ  
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
��������ͷ��ȡ��
	list         ����
����ֵ ��NULL or ���ص�ַ  
*************************************************************************************************************************/
static	struct SIS_List_Node* PeekListNode(struct SIS_List* list)//�鿴ͷ��
{
	return list->NodeHead;
}
/*************************************************************************************************************************
static	void * Append(struct SIS_List* list)
��������β������
	list         ����
����ֵ ��NULL or ���ص�ַ  
*************************************************************************************************************************/
static	int Append(struct SIS_List* list, void *elem)//ĩβ���
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
��������ͷ��ȡ��
	list         ����
����ֵ ��NULL or ���ص�ַ  
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
������
	list         ����
����ֵ ��NULL or ���ص�ַ  
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
 *@bref //��ͷ��ʼ������Ҫ������
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
 *@bref //��������ɾ��ָ���������͵ĳ�Ա����Ա���ڴ�ɾ�����Լ��ĺ����ͷţ�����ֻ�ͷ�������ڴ棬��Ҫ�ͷŽڵ��ڴ�
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








