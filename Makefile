
all: test.bc.log FORTH.bc

test: test.bc.log
test.bc.log: test.bc

test.bc: test.src ./ByteCompiler
	./ByteCompiler < $< > $@.log
FORTH.bc: FORTH.src ./ByteCompiler
	./ByteCompiler < $<

C += FORTH.c ByteCompiler.cpp ByteCompiler.parser.cpp ByteCompiler.lexer.cpp
H += FORTH.h ByteCompiler.hpp ByteCompiler.parser.hpp

CXXFLAGS += -std=gnu++11
#CXXFLAGS += -DVM_TRACELOG
./ByteCompiler: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(L)

ByteCompiler.lexer.cpp: ByteCompiler.lex
	flex -o $@ $<

ByteCompiler.parser.cpp: ByteCompiler.yacc
	bison -o $@ $<

doxy: doxy.gen
	doxygen $< 1> /dev/null
