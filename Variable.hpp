#pragma once
#include <string>

class Variable
{
private:
    const std::string ID; //Name of the variabla
    std::string inTex; //Optionally changed name, read from json
    const std::string relation; //LessOrEqual, GreaterOrEqual, Equal, Binary or Integer
    std::string relnum; //The number the previous relation applies to
    const std::string comment; //Comment for the variable marked with "#!<" in the .mod file

public:
    //Constructor for variable with a number on the other side of the relation
    Variable(const std::string id, const std::string rel, std::string& nm, std::string com) 
            : ID(id), inTex(ID), relation(rel), relnum(nm), comment(com)
    {

    }
    //Constructor for variable that is binary or integer
    Variable(const std::string id, const std::string rel, std::string com) 
            : ID(id), inTex(ID), relation(rel), comment(com)
    {

    }

    bool operator==(const std::string& name)
    {
        return ID == name;
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

    const std::string getRelnum() const
    {
        return relnum;
    }

    void setInTex(const std::string& it)
    {
        inTex = it;
    }

};