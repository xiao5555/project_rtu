#ifndef __ATTRIBUTE_INTERFACE_H__
#define __ATTRIBUTE_INTERFACE_H__
#include "Inc/AttributeTypes.h"
struct AttrOperator
{
	IO_ERR (*LoadAttr)( struct Attribute *c_this);
	IO_ERR (*WriteAttr)(struct Attribute *c_this,const void *val);
};
extern struct AttrOperator AttrOperator[];

#endif//__ATTRIBUTE_INTERFACE_H__



