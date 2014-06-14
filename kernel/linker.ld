OUTPUT_FORMAT(elf32-i386)
ENTRY(loader)
phys = 0x00100000;
SECTIONS
{
	.text phys : AT(phys)
	{
		kernel_start = .;
		*(.text)
		. = ALIGN(4096);
	}

	.data : AT(phys + (data - kernel_start))
	{
		data = .;
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}

	.bss : AT(phys + (bss - kernel_start))
	{
		bss = .;
		*(.bss)
		. = ALIGN(4096);
	}
	kernel_end = .;
	/DISCARD/ :
	{
		*(.comment)
		*(.eh_frame)
		*(.note.gnu.build-id)
	}
}
