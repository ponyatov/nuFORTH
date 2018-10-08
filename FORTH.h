/**
	@file
	@brief global Virtual Machine headers
			(ANSI C'89 code shared between byte compiler & embedded)
*/

/**
@defgroup vm FORTH Virtual Machine
@brief Platform independent part of Virtual Machine shared by VM part for all systems (host, qemu, nuc970 hw)
*/

#ifndef _H_FORTH
#define _H_FORTH

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
	@defgroup config Configuration
	@ingroup vm
	@{
*/

/**
  	@defgroup debug debug
  	@{
 */

/** @brief print trace log while program excutes in VM emulator */
#define VM_TRACELOG

/** @} */

/** @brief main memory size (bytes) */
#define Msz 0x10000

/** @brief return stack size (cells) */
#define Rsz 0x1000

/** @brief data stack size (cells) */
#define Dsz 0x10

/** @} */

/**
	@defgroup machinesize machine word
	@brief size constants
	@ingroup vm
	@{
*/

/** @brief byte */
#define BYTE uint8_t

/** @brief machine word (cell) */
#define CELL uint32_t 

/** @brief machine word size in bytes */
#define CELLsz (sizeof(CELL))

/** @} */

/** @brief bytecode memory */
extern BYTE M[Msz];

/** @brief instruction pointer */
extern CELL Ip;

/** @brief compiler pointer */
extern CELL Cp;

/** @brief save compiled vocabular memory to file
@param[in] filename filename (ignored in embedded without file system support)
*/
extern void save(char* filename);

/** @defgroup mem memory access
 * 	@ingroup vm
 * 	@{ */

/** @brief fetch VM machine word from @ref M address */
extern CELL fetch(CELL addr);

/** @brief store byte at @ref M address */
extern void Bstore(CELL addr, BYTE byte);

/** @brief store VM machine word at @ref M address */
extern void store(CELL addr, CELL cell);

/** @} */

/** @defgroup compiler Compiler in VM
	@brief Compiler implemented in VM commands
	@ingroup vm
	@{
*/

/** @brief `B, ( byte -- )` compile byte */
extern void Bcompile(BYTE byte);

/** @brief `, ( cell -- )` compile cell */
extern void compile(CELL cell);

/** @} */

/** @defgroup vmop command opcodes
	@ingroup vm
	@brief bytecode opcodes
	@{							*/

#define	op_NOP	0x00
#define op_BYE	0xFF

#define op_JMP	0x01

#define op_QUEST	0xD1
#define op_DUMP		0xD1

/** @defgroup vmcmd command functions
	@ingroup vm
	@brief C functions implement every VM command
	@{							*/

/** @brief `NOP ( -- )` no operation */
extern void NOP();

/** @brief `BYE ( -- )` stop system */
extern void BYE();

/** @brief 'jmp addr` unconditional jump */
extern void JMP();

extern void DUMP();

/** @defgroup bci bytecode interpreter
	@ingroup vm
	@brief interprets bytecode in @ref M`[]`
	@{ */

/** @brief bytecode interpreter */
extern void VM();

/** @} */

#endif // _H_FORTH

