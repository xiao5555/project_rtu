#include "Inc/usartProcess.h"
#include "PrivateList/PrivateList.h"
#include <stdlib.h>
#include <string.h>
#define SOURCE_MESH    "MESH"
#define SOURCE_SIM800  "SIM800"
#define SOURCE_MODBUS  "MODBUS"

struct SIS_List *List_MountElem=NULL;
void Usart_ProcessInit(void)
{
	List_MountElem=CreateSIS_List(10);
}

void UsartCallbackProcess(void *arg)
{
	uint8_t *p_data=arg;
	
}
void MeshCallbackProcess(void *arg)
{
	USART_TypeDef *p_data=arg;
	uint8_t *p_elem=0;
	uint8_t *data=0;
	p_data->lock=1;//ÉÏËø
	struct SIS_List_Node * p_list=calloc(sizeof(struct SIS_List_Node),0);
	if(p_list)
	{
		p_elem=calloc(sizeof(ELEM_TypeDef),0);
		if(p_elem==0)
		{
			goto err_handle;
		}
		data=malloc(p_data->len);
		memcpy(data,p_data->buffer,p_data->len);
		p_list->DataType=SOURCE_MESH;
		p_list->Elem=(void*)data;
	}
	p_data->lock=0;//½âËø
	return;
err_handle:
		if(p_list)
			free(p_list);
		if(p_elem)
			free(p_elem);
		if(data)
			free(data);
	p_data->lock=0;//½âËø
}