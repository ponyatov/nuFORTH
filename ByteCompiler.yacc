%{
#include "ByteCompiler.hpp"
%}

%defines %union {
	uint8_t cmd0; uint32_t cmd1;
	char* bcfile; std::string* sym; }

%token <cmd0> CMD0
%token <cmd1> CMD1
%token <sym> SYM
%token COLON
%token SAVE dotVM
%token <bcfile> BCFILE

%%
REPL :
| REPL CMD0			{ Bcompile($2); }
| REPL SAVE BCFILE	{ save($3); }
| REPL dotVM		{ DUMP(); VM(); }
| REPL CMD1 SYM		{ Bcompile($2); Lcompile($3); }
| REPL SYM COLON	{ Ldefine($2); }
%%
