/// @file
/// @brief Single-file FORTH system for embedding into any STM32-based project
///
/// https://groups.google.com/d/msg/comp.lang.forth/eYiPcW8uPRY/Er4vVzJVDgAJ

/// FVM machine word
#define int32_t CELL
/// FVM size of CELL in bytes
#define CELLsz (sizeof(CELL))

/// Data Stack size
CELL D[Dsz];
/// Data Stack pointer
uint8_t Dp=0;

/// FORTH init point
void FORTH(void) {

}
