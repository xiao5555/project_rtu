#include "Memory/memory.h"

/****************************************************************************************
* 创建内存
***************************************************************************************/
void MY_MemCreate (MemoryStruct *p_mem,void *p_addr,MemoryNume  n_blks,MemorySize  blk_size)                                                 
{
		uint16_t     i;
    uint16_t     loops;
    uint8_t      *p_blk;
    void         **p_link;		  
		
	 p_link = (void **)p_addr;                               /* Create linked list of free memory blocks               */
    p_blk  = (uint8_t *)p_addr;
    loops  = n_blks - 1u;
    for (i = 0u; i < loops; i++) {
        p_blk +=  blk_size;
       *p_link = (void  *)p_blk;                            /* Save pointer to NEXT block in CURRENT block            */
        p_link = (void **)(void *)p_blk;                    /* Position     to NEXT block                             */
    }
   *p_link             = (void *)0;                         /* Last memory block points to NULL                       */
    p_mem->AddrPtr     = p_addr;                            /* Store start address of memory partition                */
    p_mem->FreeListPtr = p_addr;                            /* Initialize pointer to pool of free blocks              */
    p_mem->NbrFree     = n_blks;                            /* Store number of free blocks in MCB                     */
    p_mem->NbrMax      = n_blks;
    p_mem->BlkSize     = blk_size;                          /* Store block size of each memory blocks                 */
				   
}
/****************************************************************************************
* 申请内存
***************************************************************************************/
void *MY_MemGet(MemoryStruct *p_mem)
{
	  void    *p_blk;
		if (p_mem->NbrFree == (uint8_t)0) {                  /* See if there are any free memory blocks                */
        return ((void *)0);                                 /*      Return NULL pointer to caller                     */
    }
    p_blk              = p_mem->FreeListPtr;                /* Yes, point to next free memory block                   */
    p_mem->FreeListPtr = *(void **)p_blk;                   /*      Adjust pointer to new free list                   */
    p_mem->NbrFree--;                                       /*      One less memory block in this partition           */
    return (p_blk);                                         /*      Return memory block to caller                     */
}
/****************************************************************************************
* 释放内存
***************************************************************************************/
void  MY_MemPut (MemoryStruct  *p_mem,void    *p_blk)
{
	 if (p_mem->NbrFree >= p_mem->NbrMax) {                  /* Make sure all blocks not already returned              */
        return;
    }
    *(void **)p_blk    = p_mem->FreeListPtr;                /* Insert released block into free block list             */
    p_mem->FreeListPtr = p_blk;
    p_mem->NbrFree++;                                       /* One more memory block in this partition                */
}
/********************************************************************
 *@bref 实现内存的优化，当大于自定义区的时候，自动开辟数据区
 *     
 *@ret 
***********************************************************************/
void MY_MemAdvacedGet(MemoryStruct *p_mem,uint16_t size)
{
	
}

/****************************************************************************************
* 得到当前变更的数据
***************************************************************************************/
//void* MY_MemGetNonce(MemoryStruct  *p_mem,int timeOut)
//{
//	void *curr_point = p_mem->FreeListPtr;
//	while(timeOut--)
//	{
//		if(curr_point!=p_mem->FreeListPtr)
//		{	
//			return curr_point;			
//		}
//		HAL_Delay(1);
//	}
//	return 0;
//}

