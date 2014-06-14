#include <kernel/kernel.h>
#include <kernel/printk.h>
#include <kernel/mm.h>
#include <sys/multiboot.h>
#include <sys/types.h>

/*Variables*/
uint32_t total_usable_memory;
mmap_entry_t *mmap;

/*Extern variables*/
extern uint32_t kernel_start;
extern uint32_t data;
extern uint32_t bss;
extern uint32_t kernel_end;

void print_memory_locations(void)
{
	printk("Kernel Memory Locations\n");
	printk("Start :%#08x\n", &kernel_start);
	printk("Data  :%#08x\n", &data);
	printk("BSS   :%#08x\n", &bss);
	printk("End   :%#08x\n", &kernel_end);
	printk("Image size: %uK\n", (&kernel_end - &kernel_start) / 1024);
	return;
}

/*Detect how much physical RAM we have access to and print out the start/end addresses*/
void detect_physical_memory(multiboot_t *mboot_info)
{
	uint32_t start;
	uint32_t end;

	printk("Memory map\n");
	total_usable_memory = 0;
	mmap = (mmap_entry_t *) mboot_info->mmap_addr;
	while((uint32_t) mmap < mboot_info->mmap_addr + mboot_info->mmap_length){
		start = mmap->addr_l;	
		end   = mmap->addr_l + mmap->len_l;
		printk("[%#08x - %#08x] ", start, end);
		printk("%s\n", ( (mmap->type == 1) ? ("Usable   ") : ("Reserved ") ));
		if(mmap->type == 1)
			total_usable_memory += (end - start);
		mmap = (mmap_entry_t *) ((uint32_t) mmap + mmap->size + sizeof(uint));
	}
	printk("Total usable memory: %u MiB\n", (total_usable_memory / 1024) / 1024);
	return;
}

