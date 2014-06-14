bits 32
align 2

global loader
global magic
global mbd
global stack
extern kmain

MODULEALIGN equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

	;16-bit kernel signature, should be: ' Phoenix Kernel '
	;Should be at address 0x00100000
	;Just for the hell of it :D
db 0x50, 0x68, 0x6F, 0x65, 0x6E, 0x69, 0x78, 0x20
db 0x4B, 0x65, 0x72, 0x6E, 0x65, 0x6C, 0x00, 0x00

section .text
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

STACKSIZE equ 0x4000

loader:
push esp
mov  esp, stack + STACKSIZE
mov  [magic], eax
mov  [mbd], ebx
cli
call kmain
cli
hlt

section .bss
align 4
stack: resb STACKSIZE
magic: resd 1
mbd:   resd 1
