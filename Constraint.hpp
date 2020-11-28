#pragma once

#include "Variable.hpp"

#include <list>
#include <variant>
#include <string>

class Constraint
{
    std::list<std::variant<Variable*, char, std::string>> LHS;
    std::list<std::variant<Variable*, char, std::string>> RHS;
    std::string relation;
    std::string comment;

public:
    Constraint(std::list<std::variant<Variable*, char, std::string>>& lh,
    std::list<std::variant<Variable*, char, std::string>>& rh,
    const std::string& rel, const std::string& comm)
            : LHS(lh), RHS(rh), relation(rel), comment(comm)
            {

            }

    std::string getComment() const
    {
        return comment;
    }

    const std::list<std::variant<Variable*, char, std::string>>& getLeft() const
    {
        return LHS;
    }
    const std::list<std::variant<Variable*, char, std::string>>& getRight() const
    {
        return RHS;
    }

    const std::string getRelation() const
    {
        return relation;
    }
};