#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include "grammar.tab.h"
#include "Variable.hpp"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern std::list<Variable> variables;
extern std::map<std::string, std::string> constraints;
extern std::ofstream toTeX;

int main()
{

    std::cout << "User input\n";

    toTeX.open("output.txt");

    FILE *inputfile = fopen("input.txt", "r");
    if (!inputfile)
    {
        std::cout << "I can't open file!\n";
        return -1;
    }


    yyin = inputfile;

    yyparse();

    
    for(auto v : variables)
    {
        toTeX << v.getID() << ", " << v.getFUllRel() << ", " << v.getComment() << std::endl;
    }

    toTeX.close();

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
