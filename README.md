# Nuvoton FORTH system

(c) Dmitry Ponyatov <<dponyatov@gmail.com>> , GNU Lesser GPL

github: https://github.com/ponyatov/NUC970_NonOS_BSP/tree/FORTH/ThirdParty/FORTH

#   This is a *hardware command shell*
##  it is not an OS or FORTH system
### Don't use it for programming

This is a **stand-alone (bare-metal) command shell console** was done for debugging and 
experimenting purposes with cool [Nuvoton nuc976 SoC](#nuc).

The syntax and principle were grabbed from the FORTH programming language
and OpenFirmware, though it does not follow any standard (it is more close to '83).

https://github.com/OpenNuvoton/NUC970_NonOS_BSP/issues/1

The core was **based on the bytecode interpreter** for 
* more **portability**
* **user/system code isolation**, and
* easier multithreading implementation,

but VM command system open for 
* low-level expansions like 
* (postfix) assembler, and 
* direct hardware control.

## Supported target platforms

* Nuvoton nuc976 SoC (primary target platform)
* HOST: Linux and Windows in compatibility/emulator mode for testing and development.

### TODO

* Ralink RT5350F (Hilink HLK-RM04)
* x86 bare-metal
* Cortex-M microcontrollers (STM32F)
* QEMU: `-arm926` , `-mips32` and `-x86`

