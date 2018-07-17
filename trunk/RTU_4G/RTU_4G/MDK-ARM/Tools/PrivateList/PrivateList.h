#ifndef _PRIVATE_LIST_H_
#define _PRIVATE_LIST_H_

#include <stdint.h>
/************�ڲ�ʹ��***************/
struct SIS_List_Node{
	struct SIS_List_Node* Prev;
	struct SIS_List_Node* Next;
	char *DataType;//��������
	void* Elem;
};
/**********************************/

struct SIS_List{
	struct SIS_List_Node* NodeHead;
	struct SIS_List_Node* NodeTail;
	uint16_t Capacity;
	uint16_t (*GetCount)(struct SIS_List* list);
	int (*Append)(struct SIS_List* list, void *elem);//ĩβ���	
	void *(*TakeFront)(struct SIS_List* list);//��ͷ��ȡ��
	struct SIS_List_Node* (*PeekListNode)(struct SIS_List* list);//�鿴ͷ��
	void *(*TakeFrontByType)(struct SIS_List* list,char *type);//��ͷ��ʼ������Ҫ������
	void (*DelElemByType)(struct SIS_List* list,char *type,void (*Delete)(void* address));//��������ɾ��ָ���������͵ĳ�Ա
};
struct SIS_List* CreateSIS_List(uint16_t capacity );
void ClearSIS_List(struct SIS_List* this,void Delete(void* ));
#endif//_PRIVATE_LIST_H_

