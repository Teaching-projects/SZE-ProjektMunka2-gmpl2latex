%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>

    #include <cstdlib>
    #include <string.h>

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }
    //extern FILE *yyin;

    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> constraints;
    std::ofstream toTeX;
%}

%union
{
    char name[16];
    int  val;
    char st[16];
    char longname[32];
}


%token<name> ID
%token VARKEYWORD STKEYWORD RESTWORD
%token<name>  REL BIN INT
%token<val> NUMBER
%token LINEEND
%token<st> SCOMMENT STR

%type<longname> relation

%%


command:    expression '\n' command
        |
        ;

expression: vardec constdec restdec
        |   comment
        |
        ;

vardec:     VARKEYWORD ID relation  LINEEND vardec 
           {

                variables.insert(std::pair<std::string, std::string>($2,$2));

                toTeX << "\\item [$" << $2  << " "<< $3 << "$]\n";
           }
        | 
        ;

constdec:   STKEYWORD ID  constdec {constraints.insert(std::pair<std::string, std::string>($2,$2)); toTeX << $2 << "\n";}
        |
        ;

restdec:    RESTWORD ID
        |
        ;

relation:   REL NUMBER 
            {
                std::string relOperator = $1;
                if(relOperator== "=")
                {
                  std::string returner = "=" + std::to_string($2);
                  strcpy($$, returner.c_str());
                }
                else if(relOperator == "<=")
                {
                   
                   std::string returner = "\\in ["+std::to_string($2)+",-\\infty[";
                   strcpy($$, returner.c_str());
                }
                else if(relOperator == ">=")
                {
                   
                   std::string returner = "\\in ["+std::to_string($2)+",\\infty[";
                   strcpy($$, returner.c_str());
                }
            }

        |   BIN        
            {
                std::string returner = "\\in \\{0,1\\}";
                strcpy($$, returner.c_str());
            }

        |   INT        
            {
                std::string returner = "\\in \\mathbb{Z}";
                strcpy($$, returner.c_str());
            }
        |
        ;
comment:    SCOMMENT  ID    {std::cout << "SCOMMENT " << $2 <<'\n'; toTeX << $2 << '\n';}
        |   SCOMMENT        {std::cout << "SCOMMENT \n";}
        ;
%%

int main()
{

    std::cout << "User input\n";

    toTeX.open("output.txt");

    /*FILE *inputfile = fopen("input.txt", "r");
    if (!inputfile)
    {
        std::cout << "I can't open file!\n";
        return -1;
    }

    yyin = inputfile;*/

    yyparse();

    toTeX.close();

    std::ofstream vars,consts;
    vars.open("var.json");
    consts.open("constr.json");

    std::cout << "\n\nList of variables:\n";
    vars << "{\n";
    consts << "{\n";
    for(auto v: variables)
    {
        std::cout << "gmpl: " << v.first << " LaTex: " << v.second << '\n';
        vars << "\t\"" << v.first << "\" : \"" << v.second <<"\"\n";

    }
    std::cout << "\nList of constraints:\n";
    for(auto v: constraints)
    {
        std::cout << "gmpl: " << v.first << " LaTex: " << v.second << '\n';
        consts << "\t\"" << v.first << "\" : \"" << v.second << "\"\n";
    }
    vars << "}\n";
    consts << "}\n";

    vars.close();
    consts.close();

    //fclose(inputfile);
    return 0;
}