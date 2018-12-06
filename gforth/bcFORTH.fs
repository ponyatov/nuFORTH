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

0 value Cp						\ target compiler pointer

: TC, ( byte -- ) \ compile single byte
	( byte ) M Cp + C!			\ compile byte to target memory
	Cp 1+ TO Cp					\ increment TC pointer
;

: cmd0 ( op -- )				\ VM command w/o operands (single byte opcode)
	CREATE .S C,
	DOES>  @ TC,				\ compile opcode to target memory
;

: .end BYE ;					\ redefine gforth system bye before command

								\ \\\\\\\\\\\\\\\\\\\\\\ VM primitive commands
0x00 cmd0 nop					\ do nothing
0xFF cmd0 bye					\ stop the system

words

0 value file.bc
: .save ( -- ) \ write bytecode to image file
	BL WORD COUNT ( filename )
	( filename ) w/o create-file throw to file.bc
	M Cp file.bc write-file throw
	file.bc close-file throw
;

\ code starts here

nop
bye

.save FORTH.bc					\ write compiled system and exit (batch build)

.end

