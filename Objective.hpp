#pragma once

#include "Variable.hpp"

#include <string>
#include <list>
#include <variant>

class Objective
{
    std::list<std::variant<Variable*, char, std::string>> LHS; //The linear expression that has to be maximized or minimized
    std::string relation; //maximize or minimize
    std::string comment; //Comment of the Objective function, marked with "#!" in the .mod file

public:
    Objective(std::list<std::variant<Variable*, char, std::string>>& lh, const std::string& rel, const std::string& com):
            LHS(lh), relation(rel), comment(com)
    {

    }

    Objective()
    {

    }

    Objective& operator=(const Objective& other)
    {
        LHS = other.LHS;
        relation = other.relation;
        comment = other.comment;

        return *this;

    }

    std::string getComment() const
    {
        return comment;
    }

    std::string getRelation() const
    {
        return relation;
    }

    const std::list<std::variant<Variable*, char, std::string>>& getLeft() const
    {
        return LHS;
    }
};