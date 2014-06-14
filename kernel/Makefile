CC	 = gcc
CFLAGS	 = -m32 -g -O0 -std=c11 \
	   -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Werror \
	   -nostdlib -nostartfiles -nodefaultlibs -nostdinc \
	   -ffreestanding -finline-functions -fno-stack-protector \
	   -I./../include 

LD	 = ld
LDFLAGS  = -melf_i386 -O0

AS 	 = nasm
ASFLAGS  = -felf32 

ASM  = $(patsubst %.s,%.o,$(wildcard asm/*.s))
CORE = $(patsubst %.c,%.o,$(wildcard core/*.c))
DESC = $(patsubst %.c,%.o,$(wildcard desc_tables/*.c))
MEM  = $(patsubst %.c,%.o,$(wildcard mem/*.c))

all: phoenix-kernel

phoenix-kernel: asm/boot.o core/kmain.o $(ASM) $(CORE) $(DESC) $(MEM)
	$(LD) -T linker.ld $(LDFLAGS) -o phoenix-kernel $^

clean:
	$(RM) $(OBJFILES) phoenix-kernel kernel-syms asm/*.o core/*.o desc_tables/*.o mem/*.o
