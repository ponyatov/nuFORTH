# VM core	{#vm}

**VM core** *is system-independent* and able to run
1. on Linux/Windows host **in emulated mode** with
* **host OS API wrappers** bound to some VM commands provides access to host-specific I/O via OS and std.library calls
2. on any computing hardware **in embedded mode** with
* some VM commands bound to **low-level drivers** doing *specific I/O for every computer module variant*

### Compiler in VM core

VM core includes minimal FORTH compiling functions, implemented as VM commands: @ref compiler

So **you can develop** not only 
* **on host** with [bytecode compiler](@ref bc), but also 
* **on real hardware** module 
  * in interactive session or 
  * sending large source code streams in batch mode
    * from serial terminal  
    * data media devices
	* network socket, telnet session,
      even in HTTP(S) requests if you don't afraid of backdoors down to low-level hardware access

In fact, `FORTH.bc` system provided in this project (with full source code),
is tightly integrated with @ref compiler to make its work done:
new commands you will create via colon definitions on-board will be compiled into bytecode.

### VM core portability

Due to VM core portability most code can be run in emulation
or on any hardware without any changes.

If you have some hardware-specific code, some of them still can be run portable
via @ref hal provides unified API to different hardware via specific low-level
drivers or host OS API wrappers.

