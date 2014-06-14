#ifndef KERN_KMALLOC
#define KERN_KMALLOC

#include <sys/types.h>

#define BLOCK_SIZE      512 
#define BLOCK_COUNT     512

typedef struct mem_block_t{
    uint32_t addr;
    uint32_t size;
    _Bool free;
}__attribute__((packed)) mem_block_t;

typedef struct memory_pool_t{
    mem_block_t blocks[BLOCK_COUNT];
    uint32_t pointer;
    _Bool initialized;
}__attribute__((packed)) memory_pool_t;

void add_usable_kmem_block(uint32_t, uint32_t);
void initialize_kmalloc(void);

#endif
