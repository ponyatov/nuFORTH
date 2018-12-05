\ https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

\ portable bytecode target compiler (pure FORTH in gFORTH)
\ (c) Dmitry Ponyatov <dponyatov@gmail.com>, public domain
\ github: https://github.com/ponyatov/nuFORTH/tree/dev/gforth

VOCABULARY TC					\ create target compiler vocabulary

\ words							\ will print main system vocabulary

ONLY FORTH ALSO TC DEFINITIONS	\ configure vocabulary search order/compiling

0x1000 constant Msz				\ main memory size (bytes)
0x100  constant Rsz				\ return stack size (cells)
0x10   constant Dsz				\ data stack size (cells)

words							\ will print only target compiler vocabulary

cr Msz . Rsz . Dsz . cr cr

CREATE M Msz ALLOT				\ allocate M main memory buffer

0 value THERE					\ target compiler pointer

: TC, ( byte -- ) \ compile single byte
	( byte ) M THERE + C!		\ compile byte to target memory
	THERE 1+ TO THERE			\ increment TC pointer
;

: cmd0 ( op -- )				\ VM command w/o operands (single byte opcode)
	CREATE C,
	DOES>  TC,					\ compile opcode to target memory
;

: END BYE ;						\ redefine gforth system bye before command

								\ \\\\\\\\\\\\\\\\\\\\\\ VM primitive commands
0x00 cmd0 nop					\ do nothing
0xFF cmd0 bye					\ stop the system

bye

words

0 value file.bc
: SAVE ( filename.bc -- ) \ write bytecode to image file
	( filename ) w/o create-file throw to file.bc
		M THERE file.bc write-file throw
		file.bc close-file throw
;

S" FORTH.bc" SAVE END			\ write compiled system and exit (batch build)

