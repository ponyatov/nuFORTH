/**
	@file
	@brief global Virtual Machine universal part
			(ANSI C'89 code shared between byte compiler & embedded)
*/

#include "FORTH.h"

BYTE M[Msz];					/* bytecode memory */

CELL Ip =0;						/* instruction pointer */

CELL Cp =0; 					/* compiler pointer */

void Bcompile(BYTE byte) {
	Bstore(Cp,byte); Cp++;
}

void compile(CELL cell) {
	store(Cp,cell); Cp += CELLsz;
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
		printf("jmp\t%.8X",Ip);
	#endif
	assert(Ip<Cp);
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
			case op_NOP: NOP(); break;
			case op_BYE: BYE(); break;
			case op_JMP: JMP(); break;
			default:
				#ifdef VM_TRACELOG
					printf("undefined opcode\n\n");
				#else
					fprintf(stderr,"\n%.8X:\t%.2X\tundefined opcode\n\n",Ip-1,op);
				#endif
				abort();
		}
	}
}

