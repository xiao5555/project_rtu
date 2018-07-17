#include "Inc/AttributeTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void StringToAttr(const char* str,struct Attribute *attr)
{
	switch(attr->priv.ValueType)
	{
		case attr_float:
			sscanf(str,"%f",(float*)(attr->priv.Value));
			break;
		case attr_double:
			sscanf(str,"%lf",(double*)(attr->priv.Value));
			break;
		case attr_i8:
			sscanf(str,"%hhd",(int8_t*)(attr->priv.Value));
			break;
		case attr_i16:
			sscanf(str,"%hd",(int16_t*)(attr->priv.Value));
			break;
		case attr_i32:
			sscanf(str,"%d",(int32_t*)(attr->priv.Value));
			break;
		case attr_i64:
			sscanf(str,"%ld",(long*)(attr->priv.Value));
			break;
		case attr_u8:
			sscanf(str,"%hhu",(uint8_t*)(attr->priv.Value));
			break;
		case attr_u16:
			sscanf(str,"%hu",(uint16_t*)(attr->priv.Value));
			break;
		case attr_u32:
			sscanf(str,"%u",(uint32_t*)(attr->priv.Value));
			break;
		case attr_u64:
			sscanf(str,"%lu",(unsigned long*)(attr->priv.Value));
			break;
		case attr_str32:
		case attr_str64:
			sscanf(str,"%s",(char*)(attr->priv.Value));
			break;
//		case attr_ipaddr:
//			{
//				uint8_t *arr = ((union IPAddress*)attr->priv.Value)->IP_arr;
//				sscanf(str,"%hhu.%hhu.%hhu.%hhu",arr,arr+1,arr+2,arr+3);
//			}
//			break;
//		case attr_macaddr:
//			{
//				uint8_t *arr = ((uint8_t *)attr->priv.Value);
//				sscanf(str,"%hhx-%hhx-%hhx-%hhx-%hhx-%hhx",arr,arr+1,arr+2,arr+3,arr+4,arr+5);
//			}
//			break;
//		case attr_alarm_stru:
//			{
//				struct AlarmStru* alarm_stru = (struct AlarmStru*)(attr->priv.Value);
//				sscanf(str,"%hhx:%hhx:%hhx:%hhx",&alarm_stru->Level,&alarm_stru->VerifyTimes,&alarm_stru->Linkage,&alarm_stru->Report);
//			}
//			break;
		default:
			break;
	}
}

void AttrRW(struct Attribute *attr,void *val,IO_FLAG flag)
{
	
	void *src = NULL, *dst = NULL;
	if(flag == IO_FLAG_R)
	{
		src = attr->priv.Value;
		dst = val;
	}
	else
	{
		src = val;
		dst = attr->priv.Value;
	}
	int size = SizeofAttr(attr);
	memcpy(dst,src,size);
}
bool AttrEquals(const struct Attribute *attr,const void *val)
{
	bool res;
	
	switch(attr->priv.ValueType)
	{
		case attr_str32:
		case attr_str64:
			res = strcmp(attr->priv.Value,val) == 0;
			break;
		default:
			{
				int size = SizeofAttr(attr);
				res = memcmp(attr->priv.Value,val,size) == 0;
			}
			break;
	}
	return res;
}

char* AttrToString(const struct Attribute *attr,const void* val)//此函数本质是按照attr的规则转换val
{
	char *str = NULL;
	switch(attr->priv.ValueType)
	{
		case attr_float:
			str = malloc(10);
			sprintf(str,"%f",*(float*)(val));
			break;
		case attr_double:
			str = malloc(20);
			sprintf(str,"%lf",*(double*)(val));
			break;
		case attr_i8:
			str = malloc(5);
			sprintf(str,"%hhd",*(int8_t*)(val));
			break;
		case attr_i16:
			str = malloc(6);
			sprintf(str,"%hd",*(int16_t*)(val));
			break;
		case attr_i32:
			str = malloc(10);
			sprintf(str,"%d",*(int32_t*)(val));
			break;
		case attr_i64:
			str = malloc(10);
			sprintf(str,"%ld",*(long*)(val));
			break;
		case attr_u8:
			str = malloc(5);
			sprintf(str,"%hhu",*(uint8_t*)(val));
			break;
		case attr_u16:
			str = malloc(6);
			sprintf(str,"%hu",*(uint16_t*)(val));
			break;
		case attr_u32:
			str = malloc(10);
			sprintf(str,"%u",*(uint32_t*)(val));
			break;
		case attr_u64:
			str = malloc(10);
			sprintf(str,"%lu",*(unsigned long*)(val));
			break;
		case attr_str32:
		case attr_str64:
			str = malloc(strlen(val)+1);
			memset(str,0,strlen(val)+1);
			sprintf(str,"%s",(char*)(val));
			break;
		case attr_ipaddr:
			{
//				str = malloc(16);
//				uint8_t *arr = ((union IPAddress*)val)->IP_arr;
//				sprintf(str,"%hhu.%hhu.%hhu.%hhu",arr[0],arr[1],arr[2],arr[3]);
			}
			break;
		case attr_macaddr:
			{
				str = malloc(18);
				uint8_t *arr = ((uint8_t *)attr->priv.Value);
				sprintf(str,"%hhx-%hhx-%hhx-%hhx-%hhx-%hhx",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
			}
			break;
		case attr_alarm_stru:
			{
//				str = malloc(15);
//				memset(str,0,15);
//				struct AlarmStru* alarm_stru = (struct AlarmStru*)val;
//				sprintf(str,"%hhx:%hhx:%hhx:%hhx",alarm_stru->Level,alarm_stru->VerifyTimes,alarm_stru->Linkage,alarm_stru->Report);
			}
			break;
		default:
			break;
	}
	return str;
}
void AttrToStringRelease(void *buff)
{
	free(buff);
}

int SizeofAttr(const struct Attribute *attr)
{
	int size = 0;
	switch(attr->priv.ValueType)
	{
		case attr_float:
			size = sizeof(float);
			break;
		case attr_double:
			size = sizeof(double);
			break;
		case attr_i8:
			size =  sizeof(int8_t);
			break;
		case attr_i16:
			size = sizeof(int16_t);
			break;
		case attr_i32:
			size = sizeof(int32_t);
			break;
		case attr_i64:
			size = sizeof(int64_t);
			break;
		case attr_u8:
			size = sizeof(uint8_t);
			break;
		case attr_u16:
			size = sizeof(uint16_t);
			break;
		case attr_u32:
			size = sizeof(uint32_t);
			break;
		case attr_u64:
			size = sizeof(uint64_t);
			break;
		case attr_str32:
			size = 32;
			break;
		case attr_str64:
			size = 64;
			break;
		default:
			break;
	}
	return size;
}

#include "Inc/AttributeInterface.h"

static IO_ERR LoadAttr(struct Attribute *c_this)
{
	return AttrOperator[c_this->priv.SourceType].LoadAttr(c_this);
}

void* ReadAttr(struct Attribute *c_this,IO_ERR *err)
{
	*err = IO_ERR_UNKOWN;
	if(c_this->priv.Valid == 0|| c_this->priv.CacheType == cache_nocache)
	{
		//char buff[10] = {0};
		*err = AttrOperator[c_this->priv.SourceType].LoadAttr(c_this);
		c_this->priv.Valid = 1;
	}
	return c_this->priv.Value;//读的时候实际传的val应为二级指针
}

IO_ERR WriteAttr(struct Attribute *c_this, void *value)
{
	IO_ERR err = IO_ERR_UNKOWN;
	if(c_this->priv.Valid == 0)
	{
		//char buff[10] = {0};
		err = LoadAttr(c_this);
		if(err != IO_ERR_OK)
			return err;
		c_this->priv.Valid = 1;
	}
	if(AttrEquals(c_this,value))
		return IO_ERR_OK;
	err = AttrOperator[c_this->priv.SourceType].WriteAttr(c_this,value);
	if(err != IO_ERR_OK)
			return err;
	if(c_this->priv.Listener)
	{
		struct NotifyState state;
		state.OldValue = (uint32_t)c_this->priv.Value;
		state.NewValue =  (uint32_t)value;
		c_this->priv.Listener(&state);
	}
	AttrRW(c_this,value,IO_FLAG_W); 
	return err;//读的时候实际传的val应为二级指针
}
