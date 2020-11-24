#pragma once
#include <string>

class Variable
{
private:
    const std::string ID;
    std::string inTex;
    const std::string relation;
    std::string relnum; //previously an int value
    const std::string comment;

	bool isWithNumber;

public:
    Variable(const std::string id, const std::string rel, std::string& nm, std::string com) 
            : ID(id), inTex(ID), relation(rel), relnum(nm), comment(com), isWithNumber(true)
    {

    }

    Variable(const std::string id, const std::string rel, std::string com) 
            : ID(id), inTex(ID), relation(rel), comment(com), isWithNumber(false)
    {

    }
  
	  Variable(const Variable& other):ID(other.getID()), inTex(other.getInTex()), relation(other.getRelation()), 
			  relnum(other.getRelnum()), comment(other.getComment()), isWithNumber(other.isWithNumber) {}

	  /*Variable&operator=(const Variable&other) {
		  this->comment = other.comment;
		  this->ID = other.ID;
		  this->inTex = other.inTex;
		  this->isWithNumber = other.isWithNumber;
		  this->relation = other.relation;
		  this->relnum = other.relnum;
		  return *this;
	  }*/

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
            return getRelation() + getRelnum();
        }
            
        return getRelation();
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