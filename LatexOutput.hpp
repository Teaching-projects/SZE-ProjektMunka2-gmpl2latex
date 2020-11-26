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


class LatexOutput
{
private:
    std::map<char, std::string> operators;
    std::map<std::string, std::string> relations;


    const std::list<Variable> variables;
    const std::list<Constraint> constraints;
    const Objective object;

    void fillOperators();
    void fillRelations();
    void writeVariables(std::ofstream& inTex) const;
    void writeConstraints(std::ofstream& inTex) const;
    void writeObjective(std::ofstream& inTex) const;

public:
    LatexOutput(const std::list<Variable>& vars, const std::list<Constraint>& cons, const Objective& obj);
    void Write(const std::string& fname) const;

};