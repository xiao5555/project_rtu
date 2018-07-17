#ifndef _PRIVATE_MSG_H_
#define _PRIVATE_MSG_H_
#include <stdint.h>
#define  OS_OPT_POST_FIFO                    (OS_OPT)(0x0000u)  /* Default is to post FIFO                            */
#define  OS_OPT_POST_LIFO                    (OS_OPT)(0x0010u)  /* Post to highest priority task waiting              */
typedef  struct  os_msg         OS_MSG;
typedef  struct  os_msg_pool    OS_MSG_POOL;
typedef  struct  os_msg_q       OS_MSG_Q;
typedef  uint16_t 				OS_MSG_SIZE;
typedef	 uint32_t 				CPU_TS;
typedef  uint16_t				OS_MSG_QTY;
typedef  uint16_t		        OS_OPT;                      /* Holds function options                              <16>/32 */
struct  os_msg{                                            /* MESSAGE CONTROL BLOCK                                  */
    OS_MSG              *NextPtr;                           /* Pointer to next message                                */
    void                *MsgPtr;                            /* Actual message                                         */
    uint16_t          	MsgSize;                           /* Size of the message (in # bytes)                       */
    uint32_t              MsgTS;                             /* Time stamp of when message was sent                    */
};
struct  os_msg_pool {                                       /* OS_MSG POOL                                            */
    OS_MSG              *NextPtr;                           /* Pointer to next message                                */
    uint16_t           NbrFree;                           /* Number of messages available from this pool            */
    uint16_t           NbrUsed;                           /* Current number of messages used                        */
};
struct  os_msg_q {                                          /* OS_MSG_Q                                               */
    OS_MSG              *InPtr;                             /* Pointer to next OS_MSG to be inserted  in   the queue  */
    OS_MSG              *OutPtr;                            /* Pointer to next OS_MSG to be extracted from the queue  */
    OS_MSG_QTY           NbrEntriesSize;                    /* Maximum allowable number of entries in the queue       */
    OS_MSG_QTY           NbrEntries;                        /* Current number of entries in the queue                 */
};

/*********************************config ***********************************************************************/
#define OS_MSG_EN 1  //使用msg
#define OS_CFG_MSG_POOL_SIZE 50//总消息池的大小
/**********************************************External function**********************************************************/
void  OS_MsgPoolInit (uint8_t  *p_err);
OS_MSG_QTY  OS_MsgQFreeAll (OS_MSG_Q  *p_msg_q);
void  OS_MsgQInit (OS_MSG_Q    *p_msg_q,OS_MSG_QTY   size);
void  *OS_MsgQGet (OS_MSG_Q     *p_msg_q,
                   OS_MSG_SIZE  *p_msg_size,
                   CPU_TS       *p_ts,
                   uint8_t       *p_err);
void  OS_MsgQPut (OS_MSG_Q     *p_msg_q,
                  void         *p_void,
                  OS_MSG_SIZE   msg_size,
                  OS_OPT        opt,
                  CPU_TS        ts,
                  uint8_t       *p_err);			  
#endif//_PRIVATE_MSG_H_

