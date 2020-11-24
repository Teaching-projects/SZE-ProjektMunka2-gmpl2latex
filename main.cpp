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
    std::string inF, outF;
    if(argc == 4 || argc==6){
        if(argc == 4){
            std::string cj = "--createjson";
            if(argv[2] == cj){
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
                writeToFile(argv[3],"w",output);
            }else{
                std::cerr << argv[2]<<" Invalid type of arguments\n";
                return -1;
            }
        }else{
            std::string jsonInp = "var.json"; 
            std::string texout = ""; 
            std::string rj = "--readjson";
            std::string ot = "--outputtex";
            if(argv[2] == rj){
                jsonInp ==argv[3];
            }
            if(argv[4] == ot){
                texout ==argv[5];
            }
            FILE *inputfile = fopen(argv[1], "r");
            if (!inputfile)
            {
                std::cerr << "Can't open file!\n";
                return -1;
            }

            yyin = inputfile;
            yyparse();

            std::map<std::string,std::string> VariableNames;
            std::string usageMode = "r";
            VariableNames=jsonToMap(jsonInp.c_str(),"r");

            // change toTex values in variables to ones read from json
            std::string changeto;
            for(auto v: variables){
                changeto=VariableNames[v.getID()];
                v.setInTex(changeto);
            }
            // write to tex file
        }
    }else{
        std::cerr << "Invalid number of arguments\n";
        return -1;
    }

    return 0;
}
