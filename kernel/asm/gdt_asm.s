bits 32
align 2

global gdt_flush

extern set_kernel_status_on

gdt_flush:
mov eax, [esp+4]
lgdt [eax]
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
ret
