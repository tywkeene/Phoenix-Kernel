#ifndef _REGISTERS_KERN_
#define _REGISTERS_KERN_

#include <sys/types.h>

typedef struct {
    uint gs, fs, es, ds;
    uint edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint int_no, err_code;
    uint eip, cs, eflags, useresp, ss;
}__attribute__((packed)) regs_t;

#endif
