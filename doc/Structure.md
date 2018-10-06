# System structure

This system containts two parts:

1. [byte-code compiler](@ref bc), and
2. run-time **VM/ bytecode interpreter** provides access to hardware
   (memory, I/O and a few generic drivers)

This double-part *bytecode-based architecture provides some portability*
across systems on which it can run,
*still having low-level access* to all the hardware for experiments.
Current version able to run portable code on:
* [Nuvoton nuc976 SoC](@ref nuc) (primary target platform)
* HOST: Linux and Windows in compatibility/emulator mode for testing and development.

TODO:
* [Ralink RT5350F](@ref halk)
* x86 bare-metal
* STM32F microcontrollers
* QEMU: `-arm926` , `-mips32` and `-x86`

