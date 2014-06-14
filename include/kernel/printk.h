#ifndef _PRINTK_KERN_
#define _PRINTK_KERN_
#include <sys/types.h>
#include <sys/stdarg.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

/*Function Prototypes*/
void initialize_serial(uint16_t);
void putch(uint16_t, char);
void putstr(uint16_t, const char *);
void putoct(uint16_t, uint32_t, uint16_t, uint8_t);
void putdec(uint16_t, int, uint16_t, uint8_t);
void puthex(uint16_t, uint32_t, uint16_t, uint8_t);
void putuns(uint16_t, uint32_t, uint16_t, uint8_t);
void vaprintk(uint16_t, char *, va_list);
void printk(char *, ...);

#endif
