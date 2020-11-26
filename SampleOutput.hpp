#pragma once

#include "Variable.hpp"
#include "Constraint.hpp"
#include "Objective.hpp"

#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <variant>
#include <string>

#include <iostream>

class SampleOutput
{
private:
    std::map<char, std::string> operators;
    std::map<std::string, std::string> relations;


    const std::list<Variable> variables;
    const std::list<Constraint> constraints;
    const Objective object;


    void fillOperators()
    {
        operators['+'] = "+";
        operators['-'] = "-";
        operators['*'] = "\\cdot";
        operators['/'] = "/";
    }

    void fillRelations()
    {
        relations["<="] = "\\le";
        relations[">="] = "\\ge";
        relations["="] = "\\e";
    }

    void writeVariables(std::ofstream& inTex) const
    {
        for (auto& var : variables)
        {
            inTex << "\\item[$"<<var.getInTex();

            if(var.getRelation() == "IN")
            {
                inTex << " integer";
            }
            else if(var.getRelation() == "BI")
            {
                inTex << " binary";
            }
            else if(var.getRelation() == "<=")
            {
                inTex << "\\in[" <<var.getRelnum() << ",-\\infty[$]";
            }
            else if(var.getRelation() == ">=")
            {
                
                inTex << "\\in[" <<var.getRelnum() << ",\\infty[$]";
            }

            inTex << var.getComment() << "\n";
        }
    }

    void writeConstraints(std::ofstream& inTex) const
    {
        for(auto& cons : constraints)
        {
            inTex << cons.getComment() << "\n";

            std::list<std::variant<Variable*, char, std::string>> outlist = cons.getLeft();

            //Left side of equation
            for (auto& element : outlist)
            {
                try
                {
                    char op = std::get<char>(element);
                    inTex << operators.at(op) << " ";
                }
                catch(const std::bad_variant_access& )
                {
                    try
                    {
                        std::string number = std::get<std::string>(element);
                        inTex << number << " ";
                    }
                    catch(const std::bad_variant_access&)
                    {
                        Variable* var = std::get<Variable*>(element);
                        inTex << var->getInTex() << " ";
                    }
                    
                }
            }

            //Relation of equation

            inTex << relations.at(cons.getRelation()) << " ";

            //Right side of equation
            outlist = cons.getRight();
            for (auto& element : outlist)
            {
                try
                {
                    char op = std::get<char>(element);
                    inTex << operators.at(op) << " ";
                }
                catch(const std::bad_variant_access& )
                {
                    try
                    {
                        std::string number = std::get<std::string>(element);
                        inTex << number << " ";
                    }
                    catch(const std::bad_variant_access&)
                    {
                        Variable* var = std::get<Variable*>(element);
                        inTex << var->getInTex() << " ";
                    }
                    
                }
            }

            inTex << "\n\n";

        }
    }

    void writeObjective(std::ofstream& inTex) const
    {

        inTex << object.getComment() << "\n";

        std::list<std::variant<Variable*, char, std::string>> outlist = object.getLeft();

        //Left side of equation
        for (auto& element : outlist)
         {
             try
            {
                    char op = std::get<char>(element);
                    inTex << operators.at(op) << " ";
            }
            catch(const std::bad_variant_access& )
            {
                try
                {
                    std::string number = std::get<std::string>(element);
                    inTex << number << " ";
                }
                catch(const std::bad_variant_access&)
                {
                    Variable* var = std::get<Variable*>(element);
                    inTex << var->getInTex() << " ";
                }
                    
            }
        }

    }

public:
    SampleOutput(const std::list<Variable>& vars, const std::list<Constraint>& cons, const Objective& obj) 
            : variables(vars), constraints(cons), object(obj)
    {
        fillOperators();
        fillRelations();
    }

    void Write(const std::string& fname)
    {
        std::ofstream inTex;
        inTex.open(fname);

        inTex << "Variables\n\n";
        writeVariables(inTex);
        inTex << "\n\n\n";

        inTex << "Constraints\n\n";
        writeConstraints(inTex);

        inTex << "Object function\n\n";
        writeObjective(inTex);

        

        inTex.close();

        

    }

};