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

/**
	@defgroup config Configuration
	@ingroup vm
	@{
*/

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
#define CELLsz sizeof(CELL)

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

/** @defgroup compiler Compiler in VM
	@brief Compiler implemented in VM commands
	@ingroup vm
	@{
*/

/** @brief `B, ( byte -- ) ` compile byte
*/
extern void Bcompile(BYTE byte);

/** }@ */

#endif // _H_FORTH

