a.out: lex.yy.c grammar.tab.c grammar.tab.h
	g++-10 -std=gnu++17 lex.yy.c grammar.tab.c main.cpp
lex.yy.c: tokens.l
	flex tokens.l
grammar.tab.c grammar.tab.h: grammar.y
	bison -d grammar.y