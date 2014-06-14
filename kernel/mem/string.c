#include <sys/types.h>
#include <sys/string.h>

uint32_t strlen(const char *str)
{
	uint32_t i;

	for(i = 0; *str++ != '\0'; i++);
	return i;
}

uint32_t strcpy(char *dest, const char *src)
{
	uint32_t count = 0;
	while(*src != '\0'){
		*dest++ = *src++;
		count++;
	}
	return count;
}
