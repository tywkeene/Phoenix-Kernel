#ifndef _PANIC_KERN_
#define _PANIC_KERN_
#include <sys/types.h>

#define PANIC_HALT 1
#define PANIC_NO_HALT 0

/*Function prototype*/
void oops(char *, ...);
void panic(_Bool, char *, ...);
#endif
