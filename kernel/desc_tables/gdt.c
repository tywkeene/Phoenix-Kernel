#include <kernel/kernel.h>
#include <kernel/gdt.h>
#include <kernel/printk.h>
#include <sys/types.h>

gdt_entry gdt[3];
gdt_ptr gp;

void gdt_set_gate(int num, ulong_t base, ulong_t limit, uint8_t access, uint8_t gran)
{
	printk("Num:%d Base:%#02x Limit:%#02x Access:%#02x Granularity:%#02x\n",
			num, base, limit, access, gran);
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_install(void)
{
	printk("Installing GDT\n");
	gp.limit = (sizeof(gdt_entry) * 3) - 1;
	gp.base = (uint) &gdt;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	gdt_flush((uint32_t *)&gp);
	set_kernel_status_on(KERN_STATUS_GDT);
}
