#ifndef _H_ByteCompiler
#define _H_ByteCompiler

#include <iostream>

using namespace std;

#include <cassert>

#include "FORTH.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#include "ByteCompiler.parser.hpp"

#endif // _H_ByteCompiler

