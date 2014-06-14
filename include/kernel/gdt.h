#ifndef _GDT_KERN_
#define _GDT_KERN_
#include <sys/types.h>

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__((packed)) gdt_entry;

typedef struct {
	uint16_t limit;
	unsigned int base;
}__attribute__((packed))gdt_ptr;

/*Function Prototypes*/

/*gdt_asm.s*/
void gdt_flush(uint32_t *);

/*gdt.c*/
void gdt_set_gate(int, ulong_t, ulong_t, uint8_t, uint8_t);
void gdt_install(void);

#endif
