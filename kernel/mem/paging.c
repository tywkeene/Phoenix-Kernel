#include <kernel/kernel.h>
#include <kernel/printk.h>
#include <kernel/paging.h>
#include <sys/types.h>

/*Local Variables*/
page_dir_t *kernel_page_dir;

/*Extern Variables*/
extern uint32_t kernel_end;

void initialize_paging(void)
{
	uint32_t *page_dir_addr;
	uint32_t *page_table_addr;
	uint32_t address;
	uint i;

	page_dir_addr = (uint32_t *)((uint32_t)&kernel_end & 0xFFFFF000) + 0x1000;
	page_table_addr = page_dir_addr + 0x1000;

	for(i = 0, address = 0; i < 1024; i++){
		page_dir_addr[i] = 0 | 2;
		page_table_addr[i] = address | 3;
		flush_page_table_entry((uint32_t *)page_table_addr[i]);
		address += 4096;
	}

	page_dir_addr[0] = (uint32_t)page_table_addr;
	page_dir_addr[0] |= 3;

	kernel_page_dir = (page_dir_t *) page_dir_addr;
	printk("Kernel PD Addr: %#08x\n", page_dir_addr);

	load_pagedir_addr((uint32_t *)kernel_page_dir);
	turn_paging_on((uint32_t *)kernel_page_dir);

	printk("Paging enabled\n");
	return; 
}
