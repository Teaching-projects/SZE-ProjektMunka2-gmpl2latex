a.out: lex.yy.c grammar.tab.c grammar.tab.h LatexOutput.o LatexOutput.hpp main.cpp json_parser_project.h
	g++-10 -std=gnu++17 lex.yy.c grammar.tab.c LatexOutput.o main.cpp -I /usr/include/rapidjson/
lex.yy.c: tokens.l
	flex tokens.l
grammar.tab.c grammar.tab.h: grammar.y
	bison -d grammar.y

LatexOutput.o: LatexOutput.cpp LatexOutput.hpp
	g++-10 -std=gnu++17 -c LatexOutput.cpp
