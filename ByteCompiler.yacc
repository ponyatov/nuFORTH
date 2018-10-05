%{
#include "ByteCompiler.hpp"
%}

%defines %union { uint8_t cmd0; }

%token <cmd0> CMD0
%token SAVE

%%
REPL : | REPL CMD0	{ cout << $2 << endl; }
| REPL SAVE			{ cout << "save" << endl; }
%%

