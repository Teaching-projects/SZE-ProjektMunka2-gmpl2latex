%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>
    #include <list>
    #include <variant>

    #include <cstdlib>
    #include <string.h>

    #include "Variable.hpp"
    #include "Constraint.hpp"
    #include "Objective.hpp"

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }
    extern FILE *yyin;

    std::list<Variable> variables;
    std::list<Constraint> constraints;

    std::list<std::variant<Variable*, char, int>> EqSide;
    std::variant<Variable*, char, int> pusher;
    std::list<std::variant<Variable*, char, int>> RHS;
    std::list<std::variant<Variable*, char, int>> LHS;
    std::list<std::variant<Variable*, char, int>> OBJ;
    Objective object;
    bool ParseSuccessfull = false;
%}

%union
{
    char operation;
    char rels[2];
    char name[16];
    int  val;
    char comment[1024];
    enum relations {LessOrEqual,Equal,GreaterOrEqual};
    char obj_relations[8];

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
%type<rels> equation
%type<obj_relations> objtype

//%type<name> rel

%%

file: vardecs  constdecs obj {std::cout << "FILE"; ParseSuccessfull = true;}
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

constdec: comment STKEYWORD ID ':'  equation   {
                                                    std::cout << "constdec";
                                                    std::string re = $5;
                                                    std::string com = $1;
                                                    LHS.reverse();
                                                    RHS.reverse();
                                                    Constraint cons(LHS, RHS, re, com);
                                                    constraints.push_back(cons);

                                               }
    ;

equation:   lhs REL rhs ';' {std::cout << "EQU"; strcpy($$, $2);}
    ;

lhs:    linear {std::cout << "LEFTSIDE\n"; LHS = EqSide; EqSide.clear();};
rhs:    linear {std::cout << "RIGHT\n"; RHS = EqSide; EqSide.clear();};

linear:     ID OPERATOR linear      {
                                        for (auto it : variables)
                                        {
                                            std::string id = $1;
                                            if( it.getID() == id)
                                            {
                                                pusher = &it;
                                                EqSide.push_back(pusher);
                                                break;
                                            }
                                        }
                                        pusher = $2;
                                        EqSide.push_back(pusher);
                                    }

    |       ID                      {
                                        std::cout << "ID";
                                        for (auto it : variables)
                                        {
                                            std::string id = $1;
                                            if( it.getID() == id)
                                            {
                                                pusher = &it;
                                                EqSide.push_back(pusher);
                                                break;
                                            }
                                        }
                                    }
    |       NUMBER OPERATOR linear  {pusher = $2; EqSide.push_back(pusher); pusher = $1; EqSide.push_back(pusher);}
    |       NUMBER                  {std::cout << "NUMBER"; pusher = $1; EqSide.push_back(pusher);}
    ;

obj:    comment objtype ID ':'  objlinear ';' {
                                                std::cout << "OBJECTIVE";
                                                
                                                std::string comment = $1;
                                                std::string otype = $2;

                                                object = Objective(OBJ, otype, comment);

                                              }
    ;

objlinear: linear       {OBJ = EqSide; EqSide.clear();};

objtype: MINI   {strcpy($$, $1);}
    |    MAXI   {strcpy($$, $1);}
    ;

comment: SCOMMENTS {std::cout << "COMMENT"; strncpy($$,$1+2, sizeof($1)); std::cout << $$;}
    |   {strcpy($$, "");}
    ;


%%
