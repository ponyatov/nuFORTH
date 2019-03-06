/// @file
/// @brief Single-file FORTH system for embedding into any STM32-based project
///
/// https://groups.google.com/d/msg/comp.lang.forth/eYiPcW8uPRY/Er4vVzJVDgAJ

/// data stack size, cells
#define Dsz 0x10

#include <stdint.h>

/// FreeRTOS target project tasks, queues and synchronizations will be here
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "config.h"

/// FVM machine word
typedef union { int n ; void* p; char* s; } CELL;
/// FVM size of CELL in bytes
#define CELLsz (sizeof(CELL))

/// Data Stack
CELL D[Dsz];
/// Data Stack pointer
uint8_t Dp=0;

void inline PUSH(CELL c)	{ D[Dp++]=c;		}
CELL inline POP(void)		{ return D[--Dp];	}

void PRINT(void)			{ osMessagePut(qLOGHandle,(uint32_t)POP().s,0); }

/// FORTH init point
void FORTH(void) {
	PUSH((CELL)"\033[33;7mSTM32\033[0m FORTH"); PRINT();
	for (;;) {

	}
}
