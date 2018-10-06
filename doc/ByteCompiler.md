ByteCode compiler {#bc}
=============

The system containts two parts:

1. [byte-code compiler](@ref bc), and
2. run-time **VM/ bytecode interpreter** provides access to hardware
   (memory, I/O and a few generic drivers)

@ref bc runs on host system (Linux/Windows), contains both
* **byte-code assembler** done as syntax parser implemented in `flex`/`bison`,
* [VM core](@ref vm) *is system-independent* and able to run in emulated mode on host with
* **host OS API wrappers** bound to some VM commands provides access to host-specific I/O

Due to VM core included it has minimal FORTH compiling functions,
implemented as VM commands: @ref compiler

