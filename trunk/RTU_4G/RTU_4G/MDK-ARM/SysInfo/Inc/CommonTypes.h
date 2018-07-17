#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__
typedef enum {
	IO_FLAG_R,
	IO_FLAG_W
}IO_FLAG;
typedef enum {
	IO_ERR_OK = 0,
	IO_ERR_OVER_INDEX,
	IO_ERR_BUFF_IS_SMALL,
	IO_ERR_NO_MEM,
	IO_ERR_UNKOWN
}IO_ERR;


#endif//__COMMON_TYPES_H__


