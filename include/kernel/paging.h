#ifndef _PAGING_KERN_
#define _PAGING_KERN_

#include <kernel/kernel.h>
#include <sys/multiboot.h> 
#include <sys/types.h> 

typedef struct {
	uint32_t present  : 1;
	uint32_t rw       : 1;
	uint32_t user     : 1;
	uint32_t          : 2;
	uint32_t accessed : 1;
	uint32_t dirty    : 1;
	uint32_t          : 2;
	uint32_t          : 3;
	uint32_t frame    :20;
}__attribute__((packed)) page_t;

typedef struct {
	page_t pages[1024];
}__attribute__((packed)) page_table_t;

typedef struct {
	page_table_t *tables[1024];
	uint32_t table_phys_addrs[1024];
	uint32_t page_table_phys_addr;
}__attribute__((packed)) page_dir_t;

/*Function Prototypes*/

/*From paging.c*/
void initialize_paging(void);

/*From paging_asm.s*/
extern void load_pagedir_addr(uint32_t *);
extern void turn_paging_on(uint32_t *);
extern void flush_page_table_entry(uint32_t *);

#endif
