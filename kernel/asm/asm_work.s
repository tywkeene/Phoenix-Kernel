bits 32 
align 2

global ints_off
global ints_on
global kern_halt
global outb
global inb
global outw
global inw
global outl
global inl

extern set_kernel_status_on
extern set_kernel_status_off

ints_off:
push ebp
mov ebp, esp
cli
mov eax, 1 	;turn off the interrupts bit in kern_status
push eax
call set_kernel_status_off
pop eax
pop ebp
ret

ints_on:
push ebp
mov ebp, esp
sti
mov eax, 1 	;turn on the interrupts bit in kern_status
push eax
call set_kernel_status_on
pop eax
pop ebp
ret

kern_halt:
call ints_off
hlt

inb:
push ebp
mov ebp, esp
mov edx, [ebp+8]
xor eax, eax
in al, dx
pop ebp
ret

outb:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, al
pop ebp
ret

inw:
push ebp
mov ebp, esp
mov edx, [ebp+8]
xor eax, eax
in ax, dx
pop ebp
ret

outw:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, ax
pop ebp
ret

inl:
push ebp
mov ebp, esp
mov edx, [ebp+8]
xor eax, eax
in eax, dx
pop ebp
ret

outl:
push ebp
mov ebp, esp
mov edx, [ebp+8]
mov eax, [ebp+12]
out dx, eax
pop ebp
ret
