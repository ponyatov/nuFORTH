# Nuvoton FORTH system

(c) Dmitry Ponyatov <<dponyatov@gmail.com>> , GNU LGPL

github: https://github.com/ponyatov/NUC970_NonOS_BSP/tree/FORTH/ThirdParty/FORTH

This is a stand-alone (bare-metal) command console done for debugging and 
experimenting purposes with cool Nuvoton nuc976 SoC. 

The syntax and principle were grabbed from the FORTH programming language,
though it does not follow any standard (it is more close to '83).

The core was based on the bytecode interpreter for more portability
and easier multithreading implementation,
but VM command system open for low-level expansions like (postfix) assembler
and direct hardware control.

