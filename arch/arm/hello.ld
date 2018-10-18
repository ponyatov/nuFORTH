ENTRY(_Reset)

SECTIONS
{
	. = 0x10000;
	.boot : { hello_s.o(.text) }
	.text : { *(.text) }
	. = ALIGN(8);
	. = . + 0x1000; /* 4K stack */
	stack_top = . ;
}

