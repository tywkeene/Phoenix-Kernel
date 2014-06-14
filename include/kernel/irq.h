#ifndef _IRQ_KERN_
#define _IRQ_KERN_
#include <kernel/registers.h>
#include <sys/types.h>

#define _PIC_MASTER 	0x20
#define _PIC_SLAVE 	0xA0	

typedef void (*irq_handler_func_t)(regs_t *r);

void irq_remove_handler(uint);
void irq_assign_handler(uint, irq_handler_func_t);
void irq_end_of_int(uint8_t);
void irq_install_handlers(void);
void irq_handler(regs_t *);

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif
