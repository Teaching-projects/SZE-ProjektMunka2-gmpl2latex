%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>
    #include <list>
    #include <variant>
    #include <string>

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

    std::list<std::variant<Variable*, char, std::string>> EqSide;
    std::variant<Variable*, char, std::string> pusher;
    std::list<std::variant<Variable*, char, std::string>> RHS;
    std::list<std::variant<Variable*, char, std::string>> LHS;
    std::list<std::variant<Variable*, char, std::string>> OBJ;
    Objective object;

    bool ParseSuccessfull = false;
%}

%union
{
    char operation;
    char rels[2];
    char name[16];
    char  val[32];
    char comment[1024];
    char obj_relations[8];

    struct relstruct 
    {
        char relop[2];
        char num[32];
    } relstr;
}


%token<name> ID
%token VARKEYWORD STKEYWORD SCOMMENT
%token<name> BIN INT
%token<val> NUMBER
%token<operation> OPERATOR

%token<comment> SCOMMENTS
%token<comment> VARCOMMENTS
%token<rels> REL
%token<name> MINI
%token<name> MAXI

%type<comment> comment
%type<comment> varcomment
%type<relstr> relation
%type<rels> equation
%type<obj_relations> objtype


%%

file: vardecs  constdecs obj {ParseSuccessfull = true;}
    ;

vardecs: vardecs vardec  
    |
    ;

vardec: VARKEYWORD ID relation ';' varcomment
                    {

                        if ($3.relop[0] != 'B' && $3.relop[0] != 'I')
                        {
                            std::string number = $3.num;
                            std::string op = $3.relop;
                            op.pop_back();
                            
                            Variable newVar($2, op, number, $5);
                            variables.push_back(newVar);
                        }
                        else
                        {
                            Variable newVar($2, $3.relop, $5);
                            variables.push_back(newVar);
                        }
                        

                    }
    ;

relation:    REL NUMBER {strcpy($<relstr.relop>$, $1); strcpy($<relstr.num>$, $2);}
    |        BIN        {strcpy($<relstr.relop>$, "BI");}
    |        INT        {strcpy($<relstr.relop>$, "IN");}
    ;


constdecs: constdecs constdec    
    |
    ;

constdec: comment STKEYWORD ID ':'  equation   {
                                                    
                                                    std::string re = $5;
                                                    std::string com = $1;
                                                    LHS.reverse();
                                                    RHS.reverse();
                                                    Constraint cons(LHS, RHS, re, com);
                                                    constraints.push_back(cons);

                                               }
    ;

equation:   lhs REL rhs ';' {strcpy($$, $2);}
    ;

lhs:    linear { LHS = EqSide; EqSide.clear();};
rhs:    linear { RHS = EqSide; EqSide.clear();};

linear:     ID OPERATOR linear      {
                                        pusher = $2;
                                        EqSide.push_back(pusher);
                                        for (auto& it : variables)
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

    |       ID                      {
                                        for (auto& it : variables)
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
    |       NUMBER                  {pusher = $1; EqSide.push_back(pusher);}
    ;

obj:    comment objtype ID ':'  objlinear ';' {
                                                
                                                std::string comment = $1;
                                                std::string otype = $2;
                                                OBJ.reverse();

                                                object = Objective(OBJ, otype, comment);

                                              }
    ;

objlinear: linear       {OBJ = EqSide; EqSide.clear();};

objtype: MINI   {strcpy($$, $1);}
    |    MAXI   {strcpy($$, $1);}
    ;

comment: SCOMMENTS {strncpy($$,$1+2, sizeof($1));}
    |   {strcpy($$, "");}
    ;

varcomment: VARCOMMENTS {strncpy($$,$1+3, sizeof($1));}
    |   {strcpy($$, "");}
    ;


%%
