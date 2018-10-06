%{
#include "ByteCompiler.hpp"
%}

%defines %union { uint8_t cmd0; char* bcfile; }

%token <cmd0> CMD0
%token SAVE
%token <bcfile> BCFILE

%%
REPL : | REPL CMD0	{ cout << $2 << endl; }
| REPL SAVE BCFILE	{ save($3); }
%%

