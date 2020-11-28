#pragma once

#include "Variable.hpp"

#include <list>
#include <variant>
#include <string>

class Constraint
{
    std::list<std::variant<Variable*, char, std::string>> LHS; //Left Hand Side of the equation
    std::list<std::variant<Variable*, char, std::string>> RHS; //Right Hand Side of the equation
    std::string relation; //Relation between the two sides
    std::string comment; //Comment for the constraint, marked with "#!" in the .mod file

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