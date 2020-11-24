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
                    //int num = std::get<int>(it);
                    returner += std::get<std::string>(it);
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
                    //int num = std::get<int>(it);
                    returner += std::get<std::string>(it);;
                }
            }
        }

        return returner;
    }

    std::string getComment() const
    {
        return comment;
    }
};