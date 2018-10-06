/**
	@file
	@brief global Virtual Machine
			(ANSI C'89 code shared between byte compiler & embedded)
*/

#include "FORTH.h"

BYTE M[Msz];		/* bytecode memory */

CELL Ip =0;			/* instruction pointer */

CELL Cp =0; 		/* compiler pointer */

