/// @file

#include "ByteCompiler.hpp"

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(std::string msg) {
	std::cout << YYERR; std::cerr << YYERR;
	exit(-1);
}

int main(int argc, char *argv[]) {
//	assert (argc==3);
	return yyparse();
}

void save(char* filename) {
	FILE *img = fopen(filename,"wb"); assert(img);
	assert ( fwrite(M,1,Cp,img) == Cp );
	fclose(img);	
}

std::map<std::string,CELL> label;
std::map<std::string,std::vector<CELL>> forward;

void Lcompile(std::string *name) {
	if (label.find(*name) != label.end()) {		// if label name known
		compile(label[*name]);					// compile its
	} else {
		if (forward.find(*name) == forward.end()) // if not find in forward[]
			forward[*name] = std::vector<CELL>();		// create empty vector
		forward[*name].push_back(Cp);		// push current Cp to forward list
		compile(-1);						// compile dummy addr
	}
}
