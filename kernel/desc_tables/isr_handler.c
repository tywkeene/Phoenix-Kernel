#include <kernel/kernel.h>
#include <kernel/panic.h>
#include <kernel/idt.h>
#include <kernel/isr_handler.h>
#include <asm/asm_work.h>
#include <sys/types.h>

static const char *exception_messages[] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint exception",
	"Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Co-processor",
	"Double Fault",
	"Co-processor Segment Overrun",
	"Bad TSS",
	"Segment not present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Co-processor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved"
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void page_fault(regs_t *r)
{

}

void isr_handler(regs_t *r)
{
	ints_off();
	if(r->int_no < 32){
		panic(PANIC_HALT, "Caught Exception [%d]: %s\n",
				r->int_no,
				exception_messages[r->int_no]);
	}
	ints_on();
	return;
}
