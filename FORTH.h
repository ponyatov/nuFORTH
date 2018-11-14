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
#include <string.h>

/**
	@defgroup config Configuration
	@ingroup vm
	@{
*/

/**
  	@defgroup debug debug
  	@{
 */

/** @brief print trace log while program executes in VM emulator */
//#define VM_TRACELOG

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

/** @defgroup reg registers
	@brief VM registers and memory areas
	@ingroup vm
	@{ */

/** @brief bytecode memory */
extern BYTE M[Msz];

/** @brief instruction pointer */
extern CELL Ip;

/** @brief compiler pointer */
extern CELL Cp;

/** @brief return stack for `call`/`ret` */
extern CELL R[Rsz];
/** @brief return stack pointer */
extern CELL Rp;

/** @} */

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

/** @brief compile ASCIIZ string */
extern void Acompile(const char* str);

/** @} */

/** @defgroup vocstruct
	@brief vocabulary structure */

/** address of entry point variable (first `call _entry` command parameter ) */
#define _ENTRY	0x0001

/** @ref Cp compiler register saved/init value */
#define _HERE	(_ENTRY+CELLsz+1)

/** address of last defined vocabulary entity (variable value) */
#define _LATEST	(_HERE+CELLsz)

/** @defgroup vmop command opcodes
	@ingroup vm
	@brief **bytecode opcodes**
	@{							*/

#define	op_NOP		0x00
#define op_BYE		0xFF

/** @name control flow
 * @{							*/

#define op_JMP		0x01
#define op_qJMP 	0x02
#define op_CALL 	0x03
#define op_RET  	0x04

/** @}							*/

/** @name stack
 * @{							*/

#define op_LIT		0x05

#define op_DUP		0x10
#define op_DROP		0x11
#define op_SWAP		0x12
#define op_OVER		0x13
#define op_ROT		0x14
#define op_PRESS	0x15

/** @}							*/

/** @name input/output
 * @{							*/

#define op_KEY		0x20
#define op_EMIT		0x21

/** @}							*/

/** @name debug
 * @{							*/

#define op_QUEST	0xD1
#define op_DUMP		0xD1

/** @}							*/

/** @defgroup vmcmd command functions
	@ingroup vm
	@brief C functions implement every VM command
	@{							*/

/** @brief `NOP ( -- )` no operation */
extern void NOP();

/** @brief `BYE ( -- )` stop system */
extern void BYE();

/** @brief `jmp addr ( -- )` unconditional jump */
extern void JMP();

/** @brief `call addr ( -- ) (R: -- addr)` nested call */
extern void CALL();

/** @brief `ret ( -- ) (R: addr -- )` return from nested call */
extern void RET();

/** @brief `dump ( -- )` dump @ref M bytecode until @ref Cp */
extern void DUMP();

/** @defgroup bci bytecode interpreter
	@ingroup vm
	@brief interprets bytecode in @ref M`[]`
	@{ */

/** @brief bytecode interpreter */
extern void VM();

/** @} */

#endif // _H_FORTH

