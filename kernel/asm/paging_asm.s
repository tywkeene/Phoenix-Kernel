bits 32
align 2

global load_pagedir_addr 
global turn_paging_on
global flush_page_table_entry

extern set_kernel_status_on

load_pagedir_addr:
mov eax, [esp+4] ;get the address of the page dir
mov cr3, eax 	;put it in the control register

turn_paging_on:
mov eax, 4 	;paging in kern_status
push eax
call set_kernel_status_on
pop eax
mov eax, cr0 
or eax, 0x80000000 ;switch the paging enabled bit
mov cr0, eax
ret

flush_page_table_entry:
mov eax, [esp+4]
invlpg [eax]
ret
