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

map<string,CELL> label;
map<string,vector<CELL>> forward;

void Lcompile(string *name) {
	if (label.find(*name) != label.end()) {		// if label name known
		compile(label[*name]);					// compile its
	} else {
//		if (forward.find(*name) == forward.end()) // if not find in forward[]
//			forward[*name] = new vector<CELL>;		// create empty vector
//		forward[*name]->append(Cp);			// push current Cp to forward list
		compile(-1);						// compile dummy addr
	}
}
