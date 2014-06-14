#include <kernel/kernel.h>
#include <kernel/printk.h>
#include <kernel/panic.h>
#include <kernel/kmalloc.h>
#include <sys/types.h>

memory_pool_t kernel_memory_pool;
memory_pool_t usable_kmem_blocks;

void add_usable_kmem_block(uint32_t addr, uint32_t size)
{
    if(usable_kmem_blocks.initialized == 0){
        printk("[Initializing kernel memory block pool]\n");
        usable_kmem_blocks.initialized = 1;
        usable_kmem_blocks.pointer = 0;
    }
    usable_kmem_blocks.blocks[usable_kmem_blocks.pointer].addr = addr;
    usable_kmem_blocks.blocks[usable_kmem_blocks.pointer].size = size;
    usable_kmem_blocks.blocks[usable_kmem_blocks.pointer].free = 1;
    usable_kmem_blocks.pointer++;
    return;
}

void initialize_kmalloc(void)
{
    uint32_t i;
    uint32_t addr;
    int total_size = 0;

//    kernel_memory_pool = (memory_pool_t) ((uint32_t)0x00000000 & 0xFFFFF000);
    printk("%#08x\n", kernel_memory_pool);

    if(usable_kmem_blocks.initialized == 0)
        panic(PANIC_HALT, "Trying to initialize kmalloc without any usable"
                "memory blocks available\n");
    for(i = 0; i < usable_kmem_blocks.pointer; i++)
        total_size += usable_kmem_blocks.blocks[i].size;
    printk("Total usable memory [%d bytes] in %d blocks\n", total_size, i);

    for(i = 0; i < usable_kmem_blocks.pointer; i++){
        for(addr = usable_kmem_blocks.blocks[i].addr; 
                addr < usable_kmem_blocks.blocks[i].size;
                addr += BLOCK_SIZE){
            kernel_memory_pool.blocks[i].addr = addr;
            kernel_memory_pool.blocks[i].size = BLOCK_SIZE;
            kernel_memory_pool.blocks[i].free = 1;
        }
    }
}

void *kmalloc(int size)
{
    return NULL;
}
