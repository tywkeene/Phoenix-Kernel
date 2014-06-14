#ifndef _KERNEL_KERN
#define _KERNEL_KERN

#include <sys/types.h>

/*Make some gcc-builtins a little easier to use*/
#define abs(x) __builtin_abs(x)
#define memset(a, b, c) __builtin_memset(a, b, c)

/*
 Each bit represented below is initialzed to 0 when kmain() is called
 The bits 7 through 8 are reserved for future use and not currently used, 
 therefor their state is undefined

   +-------------------+
   |kern_status        |
   |-------------------|
   |1 Interrupts       | 	Are interrupts enabled?
   |2 IDT              | 	is the IDT loaded?
   |3 GDT              | 	is the GDT loaded?
   |4 Paging           | 	is paging setup and enabled?
   |5 IRQs             | 	Are IRQs setup?
   |6 Halted 	       | 	Has the cpu been halted?
   |7 Reserved         |
   |8 Reserved         |
   +-------------------+
 */

/*Kernel status bits*/
#define KERN_STATUS_INTS 	1
#define KERN_STATUS_IDT  	2
#define KERN_STATUS_GDT  	3
#define KERN_STATUS_PAG  	4
#define KERN_STATUS_IRQ  	5
#define KERN_STATUS_HLT  	6

/*Function Prototypes*/
void set_kernel_status_on(uint8_t);
void set_kernel_status_off(uint8_t);
_Bool check_kernel_status(uint8_t);
void dump_kernel_status(void);

#endif
