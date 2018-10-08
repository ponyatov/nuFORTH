/// @file
/// @brief bytecode compiler headers

/// @defgroup bc Bytecode compiler
/// @brief @ref bc should be run on developer host computer to build .bc files
///        contains platform-independent bytecode part of FORTH system
///        or other .bc written applications (you can run them standalone in VM)

#ifndef _H_ByteCompiler
#define _H_ByteCompiler

#include <iostream>
#include <map>
#include <vector>

#include "FORTH.h"

/// @defgroup sym Symbol table
/// @ingroup bc
/// @{

/// @brief code labels table
extern std::map<std::string,CELL> label;

/// @brief table of forward references
extern std::map<std::string,std::vector<CELL>> forward;

/// @brief compile label
extern void Lcompile(std::string *name);

/// @brief define label
extern void Ldefine(std::string *name);

/// @}

/// @brief lexer interface
/// @returns `int` token id + can return extra parsed data
///          via @ref yylval structure to syntax parser
extern int yylex();

extern int yylineno;
extern char* yytext;

/// @brief syntax parser interface
extern int yyparse();

/// @brief syntax error callback
/// @param[in] message string with message text generated in lexer or parser
extern void yyerror(std::string message);

#include "ByteCompiler.parser.hpp"

#endif // _H_ByteCompiler

