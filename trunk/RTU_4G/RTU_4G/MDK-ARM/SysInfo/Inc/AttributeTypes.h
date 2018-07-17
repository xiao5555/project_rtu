#ifndef __ATTRIBUTE_TYPES_H__
#define __ATTRIBUTE_TYPES_H__
#include "Inc/CommonTypes.h"
#include <stdint.h>
#include <stdbool.h>
enum AttributeValueType{
	attr_i8,
	attr_i16,
	attr_i32,
	attr_i64,
	attr_u8,
	attr_u16,
	attr_u32,
	attr_u64,
	attr_float,
	attr_double,
	attr_str32,
	attr_str64,
	attr_ipaddr,
	attr_macaddr,
	attr_date_time,
	attr_audit,
	attr_alarm_stru
};
enum SourceType{
	source_eerom = 0,
	source_flash,
	source_end
};
enum CacheType{
	cache_cache,
	cache_nocache,
};
struct NotifyState
{
	
	uint32_t OldValue;	//	ʵ��Ϊָ�룬ʹ��ʱӦת��Ϊ��Ӧ����ָ��
	uint32_t NewValue;
};

struct AttributePriv		//�ڲ�ά��
{
	void* Value;
	void (*Listener)(struct NotifyState* state);
	const char* ValuePath;
//	const char* DefaultValuePath;
	enum AttributeValueType ValueType;
	enum SourceType SourceType;
	enum CacheType CacheType;
	uint8_t Valid;	//	������Ч�Ա�־ 0 ��Ч 1 ��Ч
};



struct Attribute
{
	struct AttributePriv priv;
	void (*Set)(struct Attribute* c_this,const void* val,IO_ERR* err);		//Set/Get �д��󴫳������ɴ�NULL���� 
	const void* (*Get)(struct Attribute* c_this,IO_ERR* err);
};
int SizeofAttr(const struct Attribute *attr);
void AttrRW(struct Attribute *attr,void *val,IO_FLAG flag);
bool AttrEquals(const struct Attribute *attr,const void *val);

void StringToAttr(const char* str, struct Attribute *attr);
char* AttrToString(const struct Attribute *attr,const void* val);//�˺��������ǰ���attr�Ĺ���ת��val
void AttrToStringRelease(void *buff);//����ת�ַ����������Դ  ��Ҫ����Release�����ͷ���Դ


void* ReadAttr(struct Attribute *attr,IO_ERR *err);
IO_ERR WriteAttr(struct Attribute *c_this, void *value);
#endif//__ATTRIBUTE_TYPES_H__



