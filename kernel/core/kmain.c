#include <kernel/kernel.h>
#include <kernel/printk.h>
#include <kernel/paging.h>
#include <kernel/registers.h>
#include <kernel/mem_operations.h>
#include <kernel/mm.h>
#include <kernel/gdt.h>
#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/panic.h>
#include <sys/string.h>
#include <sys/types.h>
#include <sys/multiboot.h>
#include <asm/asm_work.h>

/* Local Variables*/
/*Multiboot header from grub or another multiboot compliant bootloader*/
multiboot_t *mboot_info;

status_byte_t kern_status;

/*External variables*/

/*From linker.ld*/
extern uint32_t kernel_start;

inline void set_kernel_status_on(uint8_t bit)
{
	kern_status |= (1 << bit);
}

inline void set_kernel_status_off(uint8_t bit)
{
	kern_status &= ~(1 << bit);
}

_Bool check_kernel_status(uint8_t bit)
{
	return kern_status & (1 << bit);
}

void dump_kernel_status(void)
{
	printk("Kernel status byte: RES:00 HLT:%d IRQ:%d PAG:%d GDT:%d IDT:%d INTS:%d\n", 
			check_kernel_status(KERN_STATUS_HLT),
			check_kernel_status(KERN_STATUS_IRQ),
			check_kernel_status(KERN_STATUS_PAG), 
			check_kernel_status(KERN_STATUS_GDT), 
			check_kernel_status(KERN_STATUS_IDT),
			check_kernel_status(KERN_STATUS_INTS));
}

void kmain(uint32_t magic, uint32_t mboot)
{
	mboot_info = (multiboot_t *) mboot;

	set_kernel_status_off(KERN_STATUS_INTS);
	set_kernel_status_off(KERN_STATUS_IDT);
	set_kernel_status_off(KERN_STATUS_GDT);
	set_kernel_status_off(KERN_STATUS_PAG);
	set_kernel_status_off(KERN_STATUS_IRQ);
	set_kernel_status_off(KERN_STATUS_HLT);
	printk("Set kernel status bits\n");

	/*Turn on serial logging, our (currently) only form of output*/
	initialize_serial(COM1);

	/*The 16bit kernel signature is at 0x00100000 and should be: Phoenix Kernel*/
	printk("16bit Signature: %s\n", &kernel_start);
	printk("Command line: %s\n", mboot_info->cmdline);

	/*We rely on the multiboot header for a memory map, so if it's invalid we're screwed*/
	if(magic != MULTIBOOT_EAX_MAGIC)
		panic(PANIC_HALT, "Multiboot header magic number invalid");

	/*Get a map of memory from the multiboot header entry*/
	detect_physical_memory(mboot_info);

	/*Get the memory locations: kernel start, data/RO data and kernel endpoint*/
	print_memory_locations();

	/*Setup the descriptor tables*/
	gdt_install();
	idt_install();

	/*Initialize Paging*/
	initialize_paging();
	panic(PANIC_HALT, "Derp\n");
}
