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

words

: SAVE ( filename.bc -- ) \ write bytecode to image file
	( filename ) w/o create-file 
;

S" FORTH.bc" SAVE BYE			\ write compiled system and exit (batch build)

