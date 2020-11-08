%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>

    #include <cstdlib>
    #include <string.h>

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }
    extern FILE *yyin;

    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> constraints;
    std::ofstream toTeX;
%}

%union
{
    char operation[2];
    char rels[2];
    char name[16];
    int  val;
    char comment[1024];
    enum relations {LessOrEqual,Equal,GreaterOrEqual};
    enum obj_relations {minimize,maximize};
}


%token<name> ID
%token VARKEYWORD STKEYWORD SCOMMENT
%token<name> BIN INT
%token<val> NUMBER
%token<operation> OPERATOR

%token<comment> SCOMMENTS
%token<name> O_REL
%token<rels> REL
%token<name> MINI
%token<name> MAXI

%type<comment> comment

//%type<name> rel

%%

file: vardecs  constdecs obj {std::cout << "FILE";}
    ;

vardecs: vardecs vardec comment  {std::cout << "vardecs";}
    |
    ;

vardec: VARKEYWORD ID relation ';' {std::cout << "vardec";}
    ;

relation:    REL NUMBER {std::cout << "rel";}
    |        BIN        {std::cout << "BIN";}
    |        INT        {std::cout << "INT";}
    ;


constdecs: constdecs comment constdec    {std::cout << "constdecS";}
    |
    ;

constdec:  STKEYWORD ID ':'  equation  {std::cout << "constdec";}
    ;

equation:   linear REL linear ';' {std::cout << "EQU";}
    |       
    ;
linear:     ID OPERATOR linear
    |       ID                      {std::cout << "ID";}
    |       NUMBER OPERATOR linear
    |       NUMBER                  {std::cout << "NUMBER";}
    ;

obj:    comment objtype ID ':'  linear ';' {std::cout << "OBJECTIVE";}
    ;

objtype: MINI
    |    MAXI
    ;

comment: SCOMMENTS {std::cout << "COMMENT"; strncpy($$,$1+2, sizeof($1)); std::cout << $$;}
    |   {strcpy($$, "");}
    ;


%%
