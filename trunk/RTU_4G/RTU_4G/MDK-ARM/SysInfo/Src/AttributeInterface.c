#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Inc/AttributeTypes.h"
#include "Inc/AttributeInterface.h"
#include "Inc/24cxx.h"

/********************************************************************
 *@bref 实际操作物理地址，读取数据
 *     
 *@ret 
***********************************************************************/
static IO_ERR LoadAttrFromEEROM( struct Attribute *c_this)
{
		int addr = 0;
		sscanf(c_this->priv.ValuePath,"0x%X",&addr);
		AT24CXX_Read(addr,(uint8_t*)c_this->priv.Value,SizeofAttr(c_this));
		return IO_ERR_OK;
}
/********************************************************************
 *@bref 实际操作物理地址，写数据
 *     
 *@ret 
***********************************************************************/
static IO_ERR WriteAttrToEEROM(struct Attribute *c_this,const void *val)
{

		int addr = 0;
		sscanf(c_this->priv.ValuePath,"0x%X",&addr);
		AT24CXX_Write(addr,(uint8_t*)val,SizeofAttr(c_this));
	  return IO_ERR_OK;
}

static IO_ERR LoadAttrFromFlash( struct Attribute *c_this)
{
//		FILINFO f;
//		const char *file = NULL;
//		if(f_stat(c_this->priv.ValuePath, &f) !=FR_OK)
//		{
//			if(f_stat(c_this->priv.DefaultValuePath, &f) !=FR_OK)
//				return IO_ERR_UNKOWN;
//			else
//				file = c_this->priv.DefaultValuePath;
//		}
//		else
//			file = c_this->priv.ValuePath;
//		char *buff = malloc(f.fsize+1);
//		memset(buff,0,f.fsize+1);
//		int readLen = ReadFromFile(file,buff,f.fsize);
//		
//		if(readLen < 0)
//		{
//			free(buff);
//			return IO_ERR_UNKOWN;
//		}
//		StringToAttr(buff,c_this);
//		free(buff);
		return IO_ERR_OK;//读的时候实际传的val应为二级指针
}

static IO_ERR WriteAttrToFlash(struct Attribute *c_this,const void *val)
{
//		char *str = AttrToString(c_this,val);
//		int writeLen =  WriteToFile(c_this->priv.ValuePath,str,strlen(str));
//		AttrToStringRelease(str);
//		if(writeLen < 0)
//			return IO_ERR_UNKOWN;
		return IO_ERR_OK;
}

struct AttrOperator AttrOperator[source_end] = {
	{LoadAttrFromEEROM,WriteAttrToEEROM},	//0 source_eerom
	{LoadAttrFromFlash,WriteAttrToFlash},// 1 source_flash
};



