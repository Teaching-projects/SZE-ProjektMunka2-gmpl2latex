%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>
    #include <list>

    #include <cstdlib>
    #include <string.h>

    #include "Variable.hpp"

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }
    extern FILE *yyin;

    std::list<Variable> variables;
    std::map<std::string, std::string> constraints;
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

    struct relstruct 
    {
        char relop[2];
        int num;
    } relstr;
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
%type<relstr> relation

//%type<name> rel

%%

file: vardecs  constdecs obj {std::cout << "FILE";}
    ;

vardecs: vardecs vardec  {std::cout << "vardecs";}
    |
    ;

vardec: VARKEYWORD ID relation ';' comment
                    {
                        std::cout << "vardec"; 
                        std::cout << "\n relation: " << $3.relop << "\n";

                        if ($3.relop[0] != 'B' && $3.relop[0] != 'I')
                        {
                            Variable newVar($2, $3.relop, $3.num, $5);
                            variables.push_back(newVar);
                        }
                        else
                        {
                            Variable newVar($2, $3.relop, $5);
                            variables.push_back(newVar);
                        }
                        

                    }
    ;

relation:    REL NUMBER {std::cout << "rel"; strcpy($<relstr.relop>$, $1); $<relstr.num>$ = $2;}
    |        BIN        {std::cout << "BIN"; strcpy($<relstr.relop>$, "BI");}
    |        INT        {std::cout << "INT"; strcpy($<relstr.relop>$, "IN");}
    ;


constdecs: constdecs constdec    {std::cout << "constdecS";}
    |
    ;

constdec: comment STKEYWORD ID ':'  equation  {std::cout << "constdec";}
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
