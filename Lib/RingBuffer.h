
/* \file
 *
 * Ring buffer.
 */
 
#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#define BUFFER_SIZE        32 
#define BUFFER_NEARLY_FULL 28 
#define RingBuff_Data_t    uint8_t
#define RingBuff_Count_t   uint8_t

typedef struct
{
  RingBuff_Data_t  Buffer[BUFFER_SIZE]; /* Internal ring buffer data, referenced by the buffer pointers. */
  RingBuff_Data_t* In;                  /* Current storage location in the circular buffer */
  RingBuff_Data_t* Out;                 /* Current retrieval location in the circular buffer */
  RingBuff_Count_t Count;               /* Number of elements in the buffer */
} RingBuff_t;

/*
 * Initializes a ring buffer ready for use. Buffers must be initialized via this function
 * before any operations are called upon them. Already initialized buffers may be reset
 * by re-initializing them using this function.
 *
 * \param[out] Buffer  Pointer to a ring buffer structure to initialize
 */
static inline void RingBuffer_InitBuffer(RingBuff_t* const Buffer)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    Buffer->In  = Buffer->Buffer;
    Buffer->Out = Buffer->Buffer;
  }
}

/*
 * Retrieves the minimum number of bytes stored in a particular buffer. This value is computed
 * by entering an atomic lock on the buffer while the IN and OUT locations are fetched, so that
 * the buffer cannot be modified while the computation takes place. This value should be cached
 * when reading out the contents of the buffer, so that as small a time as possible is spent
 * in an atomic lock.
 *
 * \note The value returned by this function is guaranteed to only be the minimum number of bytes
 *        stored in the given buffer; this value may change as other threads write new data and so
 *        the returned number should be used only to determine how many successive reads may safely
 *        be performed on the buffer.
 *
 * \param[in] Buffer  Pointer to a ring buffer structure whose count is to be computed
 */
static inline RingBuff_Count_t RingBuffer_GetCount(RingBuff_t* const Buffer)
{
  RingBuff_Count_t Count;
  
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    Count = Buffer->Count;
  }
  
  return Count;
}

/*
 * Inserts an element into the ring buffer.
 *
 * \note Only one execution thread (main program thread or an ISR) may insert into a single buffer
 *       otherwise data corruption may occur. Insertion and removal may occur from different execution
 *       threads.
 *
 * \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
 * \param[in]     Data    Data element to insert into the buffer
 */
static inline void RingBuffer_Insert(RingBuff_t* const Buffer,
                                     const RingBuff_Data_t Data)
{
  *Buffer->In = Data;
  
  if (++Buffer->In == &Buffer->Buffer[BUFFER_SIZE])
    Buffer->In = Buffer->Buffer;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    Buffer->Count++;
  }
}

/*
 * Removes an element from the ring buffer.
 *
 * \note Only one execution thread (main program thread or an ISR) may remove from a single buffer
 *       otherwise data corruption may occur. Insertion and removal may occur from different execution
 *       threads.
 *
 * \param[in,out] Buffer  Pointer to a ring buffer structure to retrieve from
 *
 * \return Next data element stored in the buffer
 */
static inline RingBuff_Data_t RingBuffer_Remove(RingBuff_t* const Buffer)
{
  RingBuff_Data_t Data = *Buffer->Out;
  
  if (++Buffer->Out == &Buffer->Buffer[BUFFER_SIZE])
    Buffer->Out = Buffer->Buffer;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    Buffer->Count--;
  }
  
  return Data;
}

/** Atomically determines if the specified ring buffer contains any free space. This should
 *  be tested before storing data to the buffer, to ensure that no data is lost due to a
 *  buffer overrun.
 *
 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
 *
 *  \return Boolean true if the buffer contains no free space, false otherwise
 */		 
static inline bool RingBuffer_IsFull(RingBuff_t* const Buffer)
{
  return (RingBuffer_GetCount(Buffer) == BUFFER_SIZE);
}

/** Atomically determines if the specified ring buffer contains any data. This should
 *  be tested before removing data from the buffer, to ensure that the buffer does not
 *  underflow.
 *
 *  If the data is to be removed in a loop, store the total number of bytes stored in the
 *  buffer (via a call to the \ref RingBuffer_GetCount() function) in a temporary variable
 *  to reduce the time spent in atomicity locks.
 *
 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
 *
 *  \return Boolean true if the buffer contains no free space, false otherwise
 */		 
static inline bool RingBuffer_IsEmpty(RingBuff_t* const Buffer)
{
  return (RingBuffer_GetCount(Buffer) == 0);
}
#endif
