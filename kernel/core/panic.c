#include <kernel/kernel.h>
#include <kernel/printk.h> 
#include <kernel/panic.h>
#include <sys/types.h>
#include <sys/stdarg.h>
#include <asm/asm_work.h>

void oops(char *str, ...)
{
	va_list args;

	printk("OOPS - ");
	va_start(args, str);
	vaprintk(COM1, str, args);
	va_end(args);
	dump_kernel_status();
	return;
}

void phys_memory_dump(uint32_t start, uint32_t end)
{
	uint32_t *mem_addr;

	mem_addr = (uint32_t *)start;
	while((uint32_t) mem_addr < end){
		printk("[%#08x - %#08x]\n", mem_addr, *mem_addr);
		mem_addr++;
	}
}

void panic(_Bool halt, char *str, ...)
{
	va_list args;

	printk("PANIC - ");
	va_start(args, str);
	vaprintk(COM1, str, args);
	va_end(args);

	if(halt){
		ints_off();
		set_kernel_status_on(KERN_STATUS_HLT);
		dump_kernel_status();
//		phys_memory_dump(0x0010C000, 0x001F0000);
		kern_halt();
	}

	return;
}
