#ifndef _IRQ_HANDLER_KERN_
#define _IRQ_HANDLER_KERN_
#include <sys/types.h>
#include <kernel/registers.h>

typedef void (*irq_handler_func_t)(regs_t *r);

void irq_assign_handler(uint, irq_handler_func_t);
void irq_remove_handler(uint);
void irq_end_of_int(uint8_t);
void irq_install_handlers(void);
void irq_handler(regs_t *);

#endif
