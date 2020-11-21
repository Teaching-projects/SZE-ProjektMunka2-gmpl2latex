#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include "grammar.tab.h"

#include "Variable.hpp"
#include "Constraint.hpp"
#include "Objective.hpp"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern std::list<Variable> variables;
extern std::list<Constraint> constraints;
extern Objective object;
std::ofstream toTeX;

int main()
{

//    toTeX.open("output.txt");

    FILE *inputfile = fopen("input.txt", "r");
    if (!inputfile)
    {
        std::cout << "I can't open file!\n";
        return -1;
    }


    yyin = inputfile;
    yyparse();

    for (auto& k : constraints)
    std::cout << "\n\n\n" << k.toString() << "\n\n\n";


    std::ofstream vars,consts;
    vars.open("var.json");
    
    vars << "{\n";
    for(auto& v : variables)
    {
        vars << "\t\"" << v.getID() << "\" : \"" << v.getInTex() << "\"";
        if(&v != &variables.back()) vars << ",";
        vars << "\n";

    }
    vars << "}";

 //   toTeX.close();

    /*std::ofstream vars,consts;
    vars.open("var.json");
    consts.open("constr.json");

    std::cout << "\n\nList of variables:\n";
    vars << "{\n";
    consts << "{\n";
    for(auto v: variables)
    {
        std::cout << "gmpl: "<< v.first  << " LaTex: " << v.second  << '\n';
        vars << "\t\"" << v.first << "\" : \"" << v.second <<"\"\n";

    }
    std::cout << "\nList of constraints:\n";
    for(auto v: constraints)
    {
        std::cout << "gmpl: " << v.first << " LaTex: " << v.second << '\n';
        consts << "\t\"" << v.first << "\" : \"" << v.second << "\"\n";
    }
    vars << "}\n";
    consts << "}\n";

    vars.close();
    consts.close();*/

    fclose(inputfile);
    return 0;
}
