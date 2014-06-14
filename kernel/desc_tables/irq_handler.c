#include <kernel/kernel.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/registers.h>
#include <kernel/irq_handler.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <sys/types.h>
#include <asm/asm_work.h>

irq_handler_func_t irq_handles[16];

void irq_assign_handler(uint irq, irq_handler_func_t func)
{
	printk("Registering handler for IRQ %u\n", irq);
	if(irq_handles[irq] == NULL){
		irq_handles[irq] = func;
		printk("IRQ handle %u assigned\n", irq);
		return;
	}
	else
		printk("Handle already present for IRQ %u\n", irq);
	return;
}

void irq_remove_handler(uint irq)
{
	printk("Removing handler for IRQ %u\n", irq);
	if(irq_handles[irq] != NULL){
		irq_handles[irq] = NULL;
		printk("IRQ handle %u removed\n");
		return;
	}
	else
		printk("No handle present for IRQ %u\n", irq);
	return;
}

void irq_end_of_int(uint8_t irq)
{
	if(irq >= 12)
		outb(0xA0,0x20);
	outb(0x20,0x20);
	return;
}

void irq_install_handlers(void)
{
	return;
}

void irq_handler(regs_t *r)
{
	uint8_t irq;
	irq_handler_func_t handle;

	ints_off();
	irq = r->int_no - 32;

	if(irq_handles[irq] != NULL){
		handle = irq_handles[irq];
		handle(r);
	}
	else
		printk("No handle for IRQ %u\n", irq);
	irq_end_of_int(irq);
	ints_on();
	return;
}
