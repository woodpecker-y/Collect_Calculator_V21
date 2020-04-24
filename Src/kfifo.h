#ifndef _KFIFO_H
#define _KFIFO_H

#include "string.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

#define max(x,y)  ( x>y?x:y )
#define min(x,y)  ( x<y?x:y )

#define MAX_KFIFO_SIZE 0X800

struct kfifo {
	unsigned char *buffer;	/* the buffer holding the data */
	unsigned int size;	/* the size of the allocated buffer */
	unsigned int in;	/* data is added at offset (in % size) */
	unsigned int out;	/* data is extracted from off. (out % size) */
};

extern struct kfifo *kfifo_init(unsigned char *buffer, unsigned int size);
extern struct kfifo *kfifo_alloc(unsigned int size);
extern void kfifo_free(struct kfifo *fifo);
extern unsigned int __kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len);
extern unsigned int __kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len);

/**
 * __kfifo_reset - removes the entire FIFO contents, no locking version
 * @fifo: the fifo to be emptied.
 */
static __inline void __kfifo_reset(struct kfifo *fifo)
{
	fifo->in = fifo->out = 0;
}

/**
 * kfifo_reset - removes the entire FIFO contents
 * @fifo: the fifo to be emptied.
 */
static __inline void kfifo_reset(struct kfifo *fifo)
{

	__kfifo_reset(fifo);

}

/**
 * kfifo_put - puts some data into the FIFO
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 */
static __inline unsigned int kfifo_put(struct kfifo *fifo,
				const unsigned char *buffer, unsigned int len)
{
	unsigned int ret;

	ret = __kfifo_put(fifo, buffer, len);

	return ret;
}

/**
 * kfifo_get - gets some data from the FIFO
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 */
static __inline unsigned int kfifo_get(struct kfifo *fifo,
				     unsigned char *buffer, unsigned int len)
{
	unsigned int ret;

	ret = __kfifo_get(fifo, buffer, len);

	/*
	 * optimization: if the FIFO is empty, set the indices to 0
	 * so we don't wrap the next time
	 */
//	if (fifo->in == fifo->out)
//		fifo->in = fifo->out = 0;

	return ret;
}

/**
 * __kfifo_len - returns the number of bytes available in the FIFO, no locking version
 * @fifo: the fifo to be used.
 */
static __inline unsigned int __kfifo_len(struct kfifo *fifo)
{
	return fifo->in - fifo->out;
}

/**
 * kfifo_len - returns the number of bytes available in the FIFO
 * @fifo: the fifo to be used.
 */
static __inline unsigned int kfifo_len(struct kfifo *fifo)
{
	unsigned int ret;

	ret = __kfifo_len(fifo);

	return ret;
}

#endif
