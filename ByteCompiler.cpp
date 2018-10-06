/// @file

#include "ByteCompiler.hpp"

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout << YYERR; cerr << YYERR; exit(-1); }

int main(int argc, char *argv[]) {
//	assert (argc==3);
	return yyparse();
}

void save(char* filename) {
	FILE *img = fopen(filename,"wb"); assert(img);
	assert ( fwrite(M,1,Cp,img) == Cp );
	fclose(img);	
}

