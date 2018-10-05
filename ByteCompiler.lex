%{
#include "ByteCompiler.hpp"
%}

%option noyywrap yylineno

%%

#[^\n]*			{}						// line comment
[ \t\r\n]+		{}						// drop spaces

\.save			return SAVE;

.				{yyerror("lexer");}		// undetected char

%%


