#include "kfifo.h"

/**
 * is_power_of_2 - 判断size是否为2的幂扩展
 * @size: 要判断的值
 *
 */
int is_power_of_2(unsigned int size)
{
	return !(size & (size - 1));
}

/** 
 * fls - find last bit set 
 * @x: the word to search 
 * 
 * This is defined the same way as ffs: 
 * - return 32..1 to indicate bit 31..0 most significant bit set 
 * - return 0 to indicate no bits set 
 */  
#if defined(__GNUC__)  
static int fls(int x)  
{  
    int r;  
  
    __asm__("bsrl %1,%0\n\t"  
            "jnz 1f\n\t"  
            "movl $-1,%0\n"  
            "1:" : "=r" (r) : "rm" (x));  
    return r+1;  
}  
#else  
static int fls(int x)  
{  
    int position;  
    int i;  
    if(0 != x)  
    {  
        for (i = (x >> 1), position = 0; i != 0; ++position)  
            i >>= 1;  
    }  
    else  
    {  
        position = -1;  
    }         
    return position+1;  
}  
#endif  
/** 
 * fls64 - find last bit set in a 64-bit value 
 * @n: the value to search 
 * 
 * This is defined the same way as ffs: 
 * - return 64..1 to indicate bit 63..0 most significant bit set 
 * - return 0 to indicate no bits set 
 */  
static int fls64(uint64_t x)  
{  
    uint32_t h = x >> 32;  
    if (h)  
        return fls(h) + 32;  
    return fls(x);  
}  
  
static unsigned fls_long(unsigned long l)  
{  
    if (sizeof(l) == 4)  
        return fls(l);
		else
			return fls64(l);  
}  
  
static unsigned long roundup_pow_of_two(unsigned long x)  
{  
    return 1UL << fls_long(x - 1);  
}



/**
 * kfifo_init - allocates a new FIFO using a preallocated buffer
 * @buffer: the preallocated buffer to be used.
 * @size: the size of the internal buffer, this have to be a power of 2.
 * @gfp_mask: get_free_pages mask, passed to kmalloc()
 * @lock: the lock to be used to protect the fifo buffer
 *
 * Do NOT pass the kfifo to kfifo_free() after use! Simply free the
 * &struct kfifo with kfree().
 */
struct kfifo *kfifo_init(unsigned char *buffer, unsigned int size)
{
	struct kfifo *fifo;

	/* size must be a power of 2 */
	if(!is_power_of_2(size))
		return NULL;
	
	fifo = (struct kfifo*)pvPortMalloc(sizeof(struct kfifo));
	if (!fifo)
		return NULL;

	fifo->buffer = buffer;
	fifo->size = size;
	fifo->in = fifo->out = 0;

	return fifo;
}

/**
 * kfifo_alloc - allocates a new FIFO and its internal buffer
 * @size: the size of the internal buffer to be allocated.
 * @gfp_mask: get_free_pages mask, passed to kmalloc()
 * @lock: the lock to be used to protect the fifo buffer
 *
 * The size will be rounded-up to a power of 2.
 */
struct kfifo *kfifo_alloc(unsigned int size)
{
	unsigned char *buffer;
	struct kfifo *ret;

	/*
	 * round up to the next power of 2, since our 'let the indices
	 * wrap' technique works only in this case.
	 */
	if(!is_power_of_2(size))
	{
		if(size > MAX_KFIFO_SIZE)
			return NULL;
		size = roundup_pow_of_two(size);
	}
	
	buffer = (unsigned char *)pvPortMalloc(size);
	if (!buffer)
		return NULL;

	ret = kfifo_init(buffer, size);

	if (ret == NULL)
		vPortFree(buffer);

	return ret;
}

/**
 * kfifo_free - frees the FIFO
 * @fifo: the fifo to be freed.
 */
void kfifo_free(struct kfifo *fifo)
{
	vPortFree(fifo->buffer);
	vPortFree(fifo);
}

/**
 * __kfifo_put - puts some data into the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
unsigned int __kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, fifo->size - fifo->in + fifo->out);


	/* first put the data starting from fifo->in to buffer end */
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
	memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(fifo->buffer, buffer + l, len - l);

	/*
	 * Ensure that we add the bytes to the kfifo -before-
	 * we update the fifo->in index.
	 */


	fifo->in += len;

	return len;
}

/**
 * __kfifo_get - gets some data from the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
unsigned int __kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, fifo->in - fifo->out);

	/* first get the data from fifo->out until the end of the buffer */
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(buffer + l, fifo->buffer, len - l);
	
	fifo->out += len;

	return len;
}


