# vocabulary structure {#voc}

This system support only single vocabulary made from linked list of Forth *word* headers:

| Short name 	| Long name             	| Description                           	| type/size          	|
|------------	|-----------------------	|---------------------------------------	|--------------------	|
| LFA        	| Link Field Area       	| link to prev. word in list or 0 = end 	| int                	|
| AFA        	|  Attribute Field Area 	| attributes includes bit0: IMMEDIATE   	| byte               	|
| NFA        	| Name Firld Area       	| word name                             	| byte string ASCIIZ 	|
| CFA        	| Code Field Area       	| executable code                       	| byte-code          	|
| PFA        	| Parameter Fielf Area  	| value for CONST/VAR                   	| int                	|

### Predefined words must be precompiled into vocabulary

|||
|-|-|
|jmp _entry|jump to entry point|
|FORTH|signature and vocabulary header|
|HERE|heap allocation pointer, Hp register must be mapped here|
|LATEST|LFA of last compiler word|
|ENTRY|CFA of running word on system start|
