%{
/// @file
/// @brief this lexer part of parser was autogenerated by `flex ByteCompiler.lex`
/// @defgroup parser Syntax parser
/// @ingroup bc

#include "ByteCompiler.hpp"
%}

%option noyywrap yylineno

%%

#[^\n]*			{}						// line comment
[ \t\r\n]+		{}						// drop spaces

nop				{ yylval.cmd0 = op_NOP; return CMD0; }
bye				{ yylval.cmd0 = op_BYE; return CMD0; }

jmp				{ yylval.cmd1 = op_JMP; return CMD1; }

":"				{ return COLON; }
\.vm			{ return dotVM; }
\.save			{ return SAVE; }
[A-Z0-9_]+\.bc	{ yylval.bcfile = yytext; return BCFILE; }

[A-Z0-9_]+		{ yylval.sym = new std::string(yytext); return SYM; }

.				{yyerror("lexer");}		// undetected char

%%


