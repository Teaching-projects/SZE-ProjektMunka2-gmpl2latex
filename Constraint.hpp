#pragma once

#include "Variable.hpp"

#include <list>
#include <variant>
#include <string>

class Constraint
{
    std::list<std::variant<Variable*, char, int>> LHS;
    std::list<std::variant<Variable*, char, int>> RHS;
    std::string relation;
    std::string comment;

public:
    Constraint(std::list<std::variant<Variable*, char, int>>& lh, std::list<std::variant<Variable*, char, int>>& rh,
    const std::string& rel, const std::string& comm)
            : LHS(lh), RHS(rh), relation(rel), comment(comm)
            {

            }

    std::string toString()
    {
        std::string returner = "";

        for(auto& it : LHS)
        {
            try
            {
                Variable* var = std::get<Variable*>(it);
                returner += var->getID();
            }
            catch(const std::bad_variant_access&)
            {
                try
                {
                    char op = std::get<char>(it);
                    returner += op;
                }
                catch (const std::bad_variant_access&)
                {
                    int num = std::get<int>(it);
                    returner += std::to_string(num);
                }
            }
        }

        returner += relation;

        for(auto& it : RHS)
        {
            try
            {
                Variable* var = std::get<Variable*>(it);
                returner += var->getID();
            }
            catch(const std::bad_variant_access&)
            {
                try
                {
                    char op = std::get<char>(it);
                    returner += op;
                }
                catch (const std::bad_variant_access&)
                {
                    int num = std::get<int>(it);
                    returner += std::to_string(num);
                }
            }
        }

        return returner;
    }
};