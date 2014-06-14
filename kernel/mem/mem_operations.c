#include <sys/types.h>

void *memcpy(void *dest, const void *src, uint32_t count)
{
	uint8_t *d;
	uint8_t *s;

	d = (uint8_t *) dest;
	s = (uint8_t *) src;

	while(count--)
		*d++ = *s++;

	return dest;
}
