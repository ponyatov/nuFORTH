\ https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

\ portable bytecode target compiler (pure FORTH in gFORTH)
\ (c) Dmitry Ponyatov <dponyatov@gmail.com>, public domain
\ github: https://github.com/ponyatov/nuFORTH/tree/dev/gforth

\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ target compiler

VOCABULARY TC					\ create target compiler vocabulary

\ words							\ will print main system vocabulary

ONLY FORTH ALSO TC DEFINITIONS	\ configure vocabulary search order/compiling

0x1000 constant Msz				\ main memory size (bytes)
0x100  constant Rsz				\ return stack size (cells)
0x10   constant Dsz				\ data stack size (cells)

words							\ will print only target compiler vocabulary

cr Msz . Rsz . Dsz . cr cr

CREATE M Msz ALLOT				\ allocate M main memory buffer

: .dump ( addr size -- )		\ dump TC memory
	CR
	SWAP M + SWAP DUMP
	CR
;

0 value Cp						\ target compiler pointer

4 constant TCELL				\ byte code cell size: default is 32-bit only

: TC@ ( addr -- byte )			\ \\\\\ fetch byte from target compiler memory
	M + C@
;

: TC! ( byte addr -- )			\ \\\\\\\ store byte to target compiler memory
	M + C!
;

: T! ( cell addr -- )			\ \\\\\\\\\\\\\\\\\\\\\\\\\\ store cell to M[]
	M +  !
;

: TC, ( byte -- ) 				\ \\\\\\\\\\\\\\\\\\\\\\\\ compile single byte
	( byte ) Cp TC!				\ compile byte to target memory
	Cp 1+ TO Cp					\ increment TC pointer
;

: T, ( cell -- )				\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ compile cell
	( cell ) Cp T!
	Cp TCELL + TO Cp
;

: cmd0 ( op -- )				\ VM command w/o operands (single byte opcode)
	CREATE C,
	DOES>  @ TC,				\ compile opcode to target memory
;

: cmd1 ( op -- )				\ VM command with single cell operand
	CREATE C,
	DOES>  @ TC, ( param ) T,	\ compile opcode + parameter
;

: .end BYE ;					\ redefine gforth system bye before command

								\ \\\\\\\\\\\\\\\\\\\\\\ VM primitive commands

0x00 cmd0 nop					\ ( -- ) do nothing
0xFF cmd0 bye					\ stop the system

0x01 cmd1 branch				\ ( -- ) unconditional branch 

words

0 value file.bc
: .save ( .save FILENAME.bc ( -- ) \ \\\\\\\\\\\\ write bytecode to image file
	BL WORD COUNT ( filename )
	( filename ) w/o create-file throw to file.bc
	M Cp file.bc write-file throw
	file.bc close-file throw
;

\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ bytecode interpreter works inside of gforth

0 value Ip						\ bytecode interpreter instruction pointer

: .step ( -- )					\ \\\\\\\\\\\\\\\ execute single command in VM
	cr hex Ip . decimal space
	Ip C@ ( opcode )			\ fetch opcode
	Ip 1+ TO Ip ( Ip++ )		\ shift to next byte in M
;

: .vm ( -- )					\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\ run interpreter
	0 to Ip						\ reset entry point to start of the M image
	.step						\ run single command in VM
;

\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ target system code starts here

nop
bye
0xDeadBeef branch				\ byte order test: see in .bc dump

.save FORTH.bc					\ write compiled system and exit (batch build)

\ 0 Cp .dump
\ .vm
.end

