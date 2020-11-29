#include "HtmlOutput.hpp"

HtmlOutput::HtmlOutput(const std::list<Variable>& vars, const std::list<Constraint>& cons, const Objective& obj) 
            : variables(vars), constraints(cons), object(obj)
{
    fillOperators();
    fillRelations();
}

void HtmlOutput::writeVariables(std::ofstream& inTex) const
{
    for (auto& var : variables)
        {
            inTex << "\t<dt>\\("<<var.getInTex();

            if(var.getRelation() == "IN")
            {
                inTex << " \\in \\mathbb{Z} \\]";
            }
            else if(var.getRelation() == "BI")
            {
                inTex << " \\in\\{0,1\\} \\]";
            }
            else if(var.getRelation() == "<=")
            {
                inTex << "\\in[" <<var.getRelnum() << ",-\\infty[\\)";
            }
            else if(var.getRelation() == ">=")
            {
                
                inTex << "\\in[" <<var.getRelnum() << ",\\infty[\\)";
            }

            inTex << "</dt> <dd>" << var.getComment() << "</dd>\n";
        }
}

void HtmlOutput::writeConstraints(std::ofstream& inTex) const
{
    for(auto& cons : constraints)
    {
        inTex << "<p class=\"description\">\n\t" << cons.getComment() << "\n</p>\n\n<p>\n\t\\[ ";
        std::list<std::variant<Variable*, char, std::string>> outlist = cons.getLeft();
        //Left side of equation
        for (auto& element : outlist)
        {
            try
            {
                char op = std::get<char>(element);
                inTex << operators.at(op) << " ";
            }
            catch(const std::bad_variant_access& )
            {
                try
                {
                    std::string number = std::get<std::string>(element);
                    inTex << number << " ";
                }
                catch(const std::bad_variant_access&)
                {
                    Variable* var = std::get<Variable*>(element);
                    inTex << var->getInTex() << " ";
                }
                
            }
        }
        //Relation of equation
        inTex << relations.at(cons.getRelation()) << " ";
        //Right side of equation
        outlist = cons.getRight();
        for (auto& element : outlist)
        {
            try
            {
                char op = std::get<char>(element);
                inTex << operators.at(op) << " ";
            }
            catch(const std::bad_variant_access& )
            {
                try
                {
                    std::string number = std::get<std::string>(element);
                    inTex << number << " ";
                }
                catch(const std::bad_variant_access&)
                {
                    Variable* var = std::get<Variable*>(element);
                    inTex << var->getInTex() << " ";
                }
                
            }
        }
        inTex << "\\]\n</p>\n\n";
    }
}

void HtmlOutput::writeObjective(std::ofstream& inTex) const
{
    inTex << "<p class=\"description\">\n\t" <<object.getComment() << "\n</p>\n\n<p>\n\t\\[ ";

    std::list<std::variant<Variable*, char, std::string>> outlist = object.getLeft();
    //Left side of equation
    for (auto& element : outlist)
    {
        try
        {
                char op = std::get<char>(element);
                inTex << operators.at(op) << " ";
        }
        catch(const std::bad_variant_access& )
        {
            try
            {
                std::string number = std::get<std::string>(element);
                inTex << number << " ";
            }
            catch(const std::bad_variant_access&)
            {
                Variable* var = std::get<Variable*>(element);
                inTex << var->getInTex() << " ";
            }
                
        }
    }

    if (object.getRelation() == "minimize")
    {
        inTex << "\\to  \\min";
    }
    else
    {
        inTex << "\\to  \\max";
    }

    inTex << "\\]\n</p>\n\n";
    

}

void HtmlOutput::Write(const std::string& fname) const
{
    std::ofstream inTex;
    inTex.open(fname);

    //Beginning formatting
    inTex << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>glpk2html</title>\n\t<meta charset=\"utf-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n</head>\n\n<body>\n\n";
    
    //Variables subsection
    inTex << "<h4>Variables</h4>\n\n<dl>\n";
    writeVariables(inTex);
    inTex << "</dl>\n\n";

    //Constraints subsection
    inTex << "<h4>Constraints</h4>\n\n";
    HtmlOutput::writeConstraints(inTex);

    //Objective subsection
    inTex << "<h4>Objective</h4>\n\n";
    HtmlOutput::writeObjective(inTex);
    inTex << "<script src=\"https://cdn.jsdelivr.net/npm/mathjax@2/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>\n</body>\n</html>\n";
    
    inTex.close();
}

void HtmlOutput::fillOperators()
{
    operators['+'] = "+";
    operators['-'] = "-";
    operators['*'] = "\\cdot";
    operators['/'] = "/";
}

void HtmlOutput::fillRelations()
{
    relations["<="] = "\\le";
    relations[">="] = "\\ge";
    relations["="] = "=";
}