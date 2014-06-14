#include <kernel/kernel.h>
#include <kernel/printk.h>
#include <kernel/panic.h>
#include <kernel/registers.h>
#include <kernel/irq_handler.h>
#include <kernel/isr_handler.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <sys/types.h>
#include <asm/asm_work.h>

idt_entry idt[256];
idt_ptr idtp;

void idt_setgate(uint8_t num, uint32_t bas, uint16_t sel, uint8_t flg)
{
	idt[num].base_lo = bas & 0xFFFF;
	idt[num].base_hi = (bas >> 16) & 0xFFFF;
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flg;
}

void idt_install(void)
{
	printk("Installing IDT\n");
	idtp.limit = sizeof(idt_entry) * 256 - 1;
	idtp.base = (uint32_t)&idt;

	memset(&idt[0], 0, sizeof(idt_entry) * 256);

	/*Send out some bytes to some ports*/
	printk("Remapping PIC\n");
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);

	/*Setup the Interrupt Descriptor Table*/
	idt_setgate(0, (uint32_t)isr0, 0x08, 0x8E);
	idt_setgate(1, (uint32_t)isr1, 0x08, 0x8E);
	idt_setgate(2, (uint32_t)isr2, 0x08, 0x8E);
	idt_setgate(3, (uint32_t)isr3, 0x08, 0x8E);
	idt_setgate(4, (uint32_t)isr4, 0x08, 0x8E);
	idt_setgate(5, (uint32_t)isr5, 0x08, 0x8E);
	idt_setgate(6, (uint32_t)isr6, 0x08, 0x8E);
	idt_setgate(7, (uint32_t)isr7, 0x08, 0x8E);
	idt_setgate(8, (uint32_t)isr8, 0x08, 0x8E);
	idt_setgate(9, (uint32_t)isr9, 0x08, 0x8E);
	idt_setgate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_setgate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_setgate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_setgate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_setgate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_setgate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_setgate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_setgate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_setgate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_setgate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_setgate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_setgate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_setgate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_setgate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_setgate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_setgate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_setgate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_setgate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_setgate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_setgate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_setgate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_setgate(31, (uint32_t)isr31, 0x08, 0x8E);

	printk("Setting up IRQs\n");
	idt_setgate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_setgate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_setgate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_setgate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_setgate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_setgate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_setgate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_setgate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_setgate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_setgate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_setgate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_setgate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_setgate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_setgate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_setgate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_setgate(47, (uint32_t)irq15, 0x08, 0x8E);

	/*Give the CPU the pointer to the IDT*/
	idt_load((uint32_t)&idtp);

	ints_on();
	set_kernel_status_on(KERN_STATUS_IDT);
	set_kernel_status_on(KERN_STATUS_IRQ);
}
