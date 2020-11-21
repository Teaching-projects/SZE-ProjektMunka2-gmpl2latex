#pragma once

#include "Variable.hpp"

#include <string>
#include <list>
#include <variant>

class Objective
{
    std::list<std::variant<Variable*, char, int>> LHS;
    std::string relation;
    std::string comment;

public:
    Objective(std::list<std::variant<Variable*, char, int>>& lh, const std::string& rel, const std::string& com):
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
};