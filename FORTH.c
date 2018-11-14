/**
	@file
	@brief global Virtual Machine universal part
			(ANSI C'89 code shared between byte compiler & embedded)
*/

#include "FORTH.h"

BYTE M[Msz];					/* bytecode memory */

CELL Ip =0;						/* instruction pointer */

CELL Cp =0; 					/* compiler pointer */

CELL R[Rsz];					/* return stack */
CELL Rp =0;

void Bcompile(BYTE byte) {
	Bstore(Cp,byte); Cp++;
}

void compile(CELL cell) {
	store(Cp,cell); Cp += CELLsz;
}

void Acompile(const char* str) {
	ssize_t L = strlen(str);
	Bcompile(L);
	for (int i=0;i<L;i++) Bcompile(str[i]);
}

void Bstore(CELL addr, BYTE byte) {
	M[addr] = byte;
}

CELL fetch(CELL addr) {
	return *(CELL*)(&M[addr]);
}

void store(CELL addr, CELL cell) {
	*(CELL*)(&M[addr]) = cell;
/*
	M[addr+0] = cell>>0;
	M[addr+1] = cell>>8;
	M[addr+2] = cell>>16;
	M[addr+3] = cell>>24;
*/
}

void NOP() {
	#ifdef VM_TRACELOG
		printf("nop");
	#endif
}

void BYE() {
	#ifdef VM_TRACELOG
		printf("bye\n\n");
	#endif
	exit(0);
}

void JMP() {
	Ip = fetch(Ip);
	#ifdef VM_TRACELOG
		printf("jmp \t%.8X",Ip);
	#endif
	assert(Ip<Cp);
}

void CALL() {
	R[Rp++] = Ip + CELLsz; assert(Rp<Rsz);
	Ip = fetch(Ip);
	#ifdef VM_TRACELOG
		printf("call\t%.8X",Ip);
	#endif
	assert(Ip<Cp);
}

void RET() {
	#ifdef VM_TRACELOG
		printf("ret");
	#endif
	assert(Rp>0); Ip = R[--Rp]; assert(Ip<Cp);
}

void DUMP() {
	char dumpascii[] = "0123456789ABCDEF";		/* text representation    */
	CELL addr=0;								/* current memory address */
	for (addr=0; addr < Cp; addr++) {
		/* line begins if addr on paragraph bound */
		if (addr % 0x10 == 0) {
			if (addr>0) { printf("  %s",dumpascii); dumpascii[0] = 0; }
			printf("\n%.8X  ",addr);
		}
		else if (addr % 0x10 == 8) printf(" ");		/* mid split marker	*/
		printf("%.2X ",M[addr]);					/* hex byte			*/
		/* collect ascii symbols */
		if ( M[addr]>=' ' & M[addr]<0x80 )	dumpascii[addr%0x10] = M[addr];
		else								dumpascii[addr%0x10] = '.';
		/* move end of line */
		dumpascii[addr%0x10+1] = 0;
	}
	for (int i=0; i<(0x10-addr%0x10);i++) printf("   ");	/* padding 		*/
	printf("  %s\n\n",dumpascii);							/* rest of line */
}

void VM() {
	Ip=0;						/* reset Ip */
	uint8_t op;					/* opcode register */
	for (;;) {					/* infty bytecode interpreter loop */
		op = M[Ip++];
		#ifdef VM_TRACELOG
			printf("\n%.8X:\t%.2X\t",Ip-1,op);
		#endif
		switch (op) {			/* we'll move to command function table later */
			case op_NOP:  NOP();  break;
			case op_BYE:  BYE();  break;
			case op_JMP:  JMP();  break;
			case op_CALL: CALL(); break;
			case op_RET:  RET();  break;
			default:
			#ifdef VM_TRACELOG
			printf("\t<undefined opcode>\n\n");
			#endif
			abort();
		}
	}
}

