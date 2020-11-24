#pragma once
#include <string>

class Variable
{
private:

    const std::string ID;
    std::string inTex;
    const std::string relation;
    int relnum;
    const std::string comment;

    bool isWithNumber;

public:

    Variable(const std::string id, const std::string rel, int nm, std::string com) 
            : ID(id), inTex(ID), relation(rel), relnum(nm), comment(com), isWithNumber(true)
    {

    }

    Variable(const std::string id, const std::string rel, std::string com) 
            : ID(id), inTex(ID), relation(rel), comment(com), isWithNumber(false)
    {

    }

    const std::string& getID() const
    {
        return ID;
    }

    const std::string& getRelation() const
    {
        return relation;
    }

    const std::string& getInTex() const
    {
        return inTex;
    }

    const std::string& getComment() const
    {
        return comment;
    }

    const std::string getFUllRel() const
    {
        if(isWithNumber)
        {
            return getRelation() + std::to_string(getRelnum());
        }
            
        return getRelation();
    }

    const int getRelnum() const
    {
        return relnum;
    }

    void setInTex(const std::string& it)
    {
        inTex = it;
    }




};