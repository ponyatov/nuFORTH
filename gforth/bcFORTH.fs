\ https://groups.google.com/forum/#!topic/comp.lang.forth/eYiPcW8uPRY

\ portable bytecode target compiler (pure FORTH in gFORTH)
\ (c) Dmitry Ponyatov <dponyatov@gmail.com>, public domain
\ github: https://github.com/ponyatov/nuFORTH/tree/dev/gforth

\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ target compiler

VOCABULARY TC					\ create target compiler vocabulary

\ words							\ will print main system vocabulary

ONLY FORTH ALSO TC DEFINITIONS	\ configure vocabulary search order/compiling

0x1000 value Msz				\ main memory size (bytes)
0x100  value Rsz				\ return stack size (cells)
0x10   value Dsz				\ data stack size (cells)

words cr						\ will print only target compiler vocabulary

cr ." M[ " Msz . ." ] Rsz[ " Rsz . ." ] Dsz=[ " Dsz . ." ]" cr

CREATE M Msz ALLOT				\ allocate M main memory buffer

: .dump ( addr size -- )		\ dump TC memory
	CR
	SWAP M + SWAP DUMP
	CR
;

0 value Cp						\ target compiler pointer

4 value TCELL					\ byte code cell size: default is 32-bit only

: .32bit 4 TO TCELL ;			\ default is full-size 32 bit
: .16bit 2 TO TCELL ;			\ 16 bit is much more useful for tiny embedded
: .8bit  1 TO TCELL ;			\ experimental narrow for IoT and sensor dust

: TB@ ( addr -- byte )			\ \\\\\ fetch byte from target compiler memory
	M + C@
;

: TB! ( byte addr -- )			\ \\\\\\\ store byte to target compiler memory
	M + C!
;

: T! ( cell addr -- )			\ \\\\\\\\\\\\\\\\\\\\\\\\\\ store cell to M[]
	M +
	TCELL 4 = IF  ! THEN
	TCELL 2 = IF W! THEN
	TCELL 1 = IF C! THEN
;

: TB, ( byte -- ) 				\ \\\\\\\\\\\\\\\\\\\\\\\\ compile single byte
	( byte ) Cp TB!				\ compile byte to target memory
	Cp 1+ TO Cp					\ increment TC pointer
;

: T, ( cell -- )				\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ compile cell
	( cell ) Cp T!
	Cp TCELL + TO Cp
;

: cmd0 ( op -- )				\ VM command w/o operands (single byte opcode)
	CREATE C,
	DOES>  @ TB,				\ compile opcode to target memory
;

: cmd1 ( op -- )				\ VM command with single cell operand
	CREATE C,
	DOES>  @ TB, ( param ) T,	\ compile opcode + parameter
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
	hex cr Ip 8 u.r space
	Ip TB@ ( opcode )			\ fetch opcode
	( opcode ) dup 2 u.r		\ dump opcode
	Ip 1+ TO Ip ( Ip++ )		\ shift to next byte in M
	decimal
	DUP 0x00 = IF THEN			\ 0x00 nop
	DUP 0xFF = IF BYE THEN		\ 0xFF bye
	DROP
;

: .vm ( -- )					\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\ run interpreter
	cr cr
	0 to Ip						\ reset entry point to start of the M image
	.step						\ run single command in VM
	cr cr
;

\ \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ target system code starts here

\ .16bit 

nop
bye
0xDeadBeef branch				\ byte order test: see in .bc dump

.save FORTH.bc					\ write compiled system and exit (batch build)

\ 0 Cp .dump
 .vm
\ .end

