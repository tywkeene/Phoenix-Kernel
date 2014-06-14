#ifndef _MM_KERN_
#define _MM_KERN_
#include <sys/types.h>
#include <sys/multiboot.h>

/*Function Prototypes*/
void print_memory_locations(void);
void detect_physical_memory(multiboot_t *);

#endif
