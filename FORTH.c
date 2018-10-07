/**
	@file
	@brief global Virtual Machine
			(ANSI C'89 code shared between byte compiler & embedded)
*/

#include "FORTH.h"

BYTE M[Msz];					/* bytecode memory */

CELL Ip =0;						/* instruction pointer */

CELL Cp =0; 					/* compiler pointer */

void Bcompile(BYTE byte) {
	M[Cp++] = byte;
}

void VM() {
	Ip=0;						/* reset Ip */
	uint8_t op;					/* opcode register */
	for (;;) {					/* infty bytecode interpreter loop */
		op = M[Ip++];
		switch (op) {			/* we'll move to command function table later */
			default:
				fprintf(stderr,"%.8X:\t%.2X\n\nundefined opcode\n\n",Ip-1,op);
				abort();
		}
	}
}

