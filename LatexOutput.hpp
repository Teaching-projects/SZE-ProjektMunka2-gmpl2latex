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
    std::map<char, std::string> operators; //Map to easily chage operators
    std::map<std::string, std::string> relations; //Map to easily chage relation signs


    const std::list<Variable> variables; //The list of variables in the file
    const std::list<Constraint> constraints; //The list of constraints in the file
    const Objective object; //The objective function of the file

    void fillOperators(); //Init operators map
    void fillRelations(); //Init relations map
    void writeVariables(std::ofstream& inTex) const; //write the variables block to the given file
    void writeConstraints(std::ofstream& inTex) const; //write the constraints block to the given file
    void writeObjective(std::ofstream& inTex) const; //write the objective function to the given file

public:
    LatexOutput(const std::list<Variable>& vars, const std::list<Constraint>& cons, const Objective& obj);

    //Public outputter function, calls writeVariables(), writeConstraints() and writeObjective() in order and writes the tags in the file
    void Write(const std::string& fname) const;

};