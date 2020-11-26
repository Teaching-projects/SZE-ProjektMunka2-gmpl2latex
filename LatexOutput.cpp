#include "LatexOutput.hpp"

LatexOutput::LatexOutput(const std::list<Variable>& vars, const std::list<Constraint>& cons, const Objective& obj) 
            : variables(vars), constraints(cons), object(obj)
{
    fillOperators();
    fillRelations();
}

void LatexOutput::writeVariables(std::ofstream& inTex) const
{
    for (auto& var : variables)
        {
            inTex << "\t\t\\item[$"<<var.getInTex();

            if(var.getRelation() == "IN")
            {
                inTex << " \\in \\mathbb{Z} $]";
            }
            else if(var.getRelation() == "BI")
            {
                inTex << " \\in\\{0,1\\} $]";
            }
            else if(var.getRelation() == "<=")
            {
                inTex << "\\in[" <<var.getRelnum() << ",-\\infty[$]";
            }
            else if(var.getRelation() == ">=")
            {
                
                inTex << "\\in[" <<var.getRelnum() << ",\\infty[$]";
            }

            inTex << var.getComment() << "\n";
        }
}

void LatexOutput::writeConstraints(std::ofstream& inTex) const
{
    for(auto& cons : constraints)
    {
        inTex << "\t" << cons.getComment() << "\n\n\t$$ ";
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
        inTex << "$$\n\n";
    }
}

void LatexOutput::writeObjective(std::ofstream& inTex) const
{
    inTex << "\t" <<object.getComment() << "\n\n\t$$ ";

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

    inTex << " $$\n\n";
    

}

void LatexOutput::Write(const std::string& fname) const
{
    std::ofstream inTex;
    inTex.open(fname);

    //Beginning formatting
    inTex << "\\documentclass{article}\n\n\\begin{document}\n\n";
    
    //Variables subsection
    inTex << "\t\\subsubsection*{Variables}\n\n";
    inTex << "\t\\begin{description}\n";
    writeVariables(inTex);
    inTex << "\t\\end{description}\n";
    inTex << "\n\n";

    //Constraints subsection
    inTex << "\t\\subsubsection*{Constraints}\n\n";
    writeConstraints(inTex);

    //Objective subsection
    inTex << "\t\\subsubsection*{Objective}\n\n";
    writeObjective(inTex);
    inTex << "\\end{document}";
    
    inTex.close();
}

void LatexOutput::fillOperators()
{
    operators['+'] = "+";
    operators['-'] = "-";
    operators['*'] = "\\cdot";
    operators['/'] = "/";
}

void LatexOutput::fillRelations()
{
    relations["<="] = "\\le";
    relations[">="] = "\\ge";
    relations["="] = "=";
}