
FORTH.bc: FORTH.src ./ByteCompiler
	./ByteCompiler < $< > $<.log && od $@ >> $<.log

C += ByteCompiler.cpp ByteCompiler.parser.cpp ByteCompiler.lexer.cpp 
H += ByteCompiler.hpp ByteCompiler.parser.hpp

CXXFLAGS += -std=gnu++11
./ByteCompiler: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(L)

ByteCompiler.lexer.cpp: ByteCompiler.lex
	flex -o $@ $<

ByteCompiler.parser.cpp: ByteCompiler.yacc
	bison -o $@ $<

doxy: doxy.gen
	doxygen $< 1> /dev/null

