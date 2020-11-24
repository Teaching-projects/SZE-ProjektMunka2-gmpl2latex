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

#include "json_parser_project.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern std::list<Variable> variables;
extern std::list<Constraint> constraints;
extern Objective object;
extern bool ParseSuccessfull;

std::ofstream toTeX;

int main(int argc, char **argv)
{

    FILE *inputfile = fopen(argv[1], "r");
    if (!inputfile)
    {
        std::cerr << "Can't open file!\n";
        return -1;
    }

    yyin = inputfile;
    yyparse();

    if(!ParseSuccessfull)
    { 
        std::cerr << "Parsing error!";
        return 1;
    }

    rapidjson::Document output;
    output=createJson(1,variables);  
    writeToFile("var.json","w",output);

    /*
    for (auto& v : variables)
    {
        std::cout << "\n" << v.getID() << v.getRelation() << v.getComment() << "\n";
    }

    for (auto& k : constraints)
    {
        std::cout << "\n\n\n" << k.getComment() << "\n" << k.toString() << "\n\n\n";

    }

    std::cout << object.getComment() << "\n" << object.toString(); 
    
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

    fclose(inputfile);
    */

    return 0;
}
