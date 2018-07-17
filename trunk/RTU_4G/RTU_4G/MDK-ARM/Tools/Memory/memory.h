#ifndef __COUSTOM_MEMORY_H
#define __COUSTOM_MEMORY_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef uint8_t MemoryNume;
typedef uint32_t  MemorySize;
struct os_mem{
    void                *AddrPtr;                           /* Pointer to beginning of memory partition               */
    void                *FreeListPtr;                       /* Pointer to list of free memory blocks                  */
    MemorySize          BlkSize;                           /* Size (in bytes) of each block of memory                */
    MemoryNume           NbrMax;                            /* Total number of blocks in this partition               */
    MemoryNume           NbrFree;                           /* Number of memor*/
};
typedef  struct  os_mem    MemoryStruct; 
void MY_MemCreate (MemoryStruct *p_mem,void *p_addr,MemoryNume  n_blks,MemorySize  blk_size);
void *MY_MemGet(MemoryStruct *p_mem);
void  MY_MemPut (MemoryStruct  *p_mem,void    *p_blk);
//void* MY_MemGetNonce(MemoryStruct  *p_mem,int timeOut);
#endif//__COUSTOM_MEMORY_H

