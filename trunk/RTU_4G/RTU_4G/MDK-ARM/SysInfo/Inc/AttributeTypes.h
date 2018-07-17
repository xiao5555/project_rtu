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
	
	uint32_t OldValue;	//	实际为指针，使用时应转换为相应类型指针
	uint32_t NewValue;
};

struct AttributePriv		//内部维护
{
	void* Value;
	void (*Listener)(struct NotifyState* state);
	const char* ValuePath;
//	const char* DefaultValuePath;
	enum AttributeValueType ValueType;
	enum SourceType SourceType;
	enum CacheType CacheType;
	uint8_t Valid;	//	数据有效性标志 0 无效 1 有效
};



struct Attribute
{
	struct AttributePriv priv;
	void (*Set)(struct Attribute* c_this,const void* val,IO_ERR* err);		//Set/Get 中错误传出参数可传NULL忽略 
	const void* (*Get)(struct Attribute* c_this,IO_ERR* err);
};
int SizeofAttr(const struct Attribute *attr);
void AttrRW(struct Attribute *attr,void *val,IO_FLAG flag);
bool AttrEquals(const struct Attribute *attr,const void *val);

void StringToAttr(const char* str, struct Attribute *attr);
char* AttrToString(const struct Attribute *attr,const void* val);//此函数本质是按照attr的规则转换val
void AttrToStringRelease(void *buff);//属性转字符串会分配资源  需要调此Release函数释放资源


void* ReadAttr(struct Attribute *attr,IO_ERR *err);
IO_ERR WriteAttr(struct Attribute *c_this, void *value);
#endif//__ATTRIBUTE_TYPES_H__



