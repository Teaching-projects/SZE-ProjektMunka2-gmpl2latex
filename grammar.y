%{
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }

    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> constraints;
%}

%union
{
    char name[16];
    int  val;
    char st[16];
}


%token<name> ID
%token VARKEYWORD STKEYWORD RESTWORD
%token<name>  REL BIN INT
%token<val> NUMBER
%token LINEEND
%token<st> SCOMMENT STR

%%


command:    expression '\n' command
        |
        ;

expression: vardec constdec restdec
        |   comment
        |
        ;
vardec:     VARKEYWORD ID relation  LINEEND vardec {variables.insert(std::pair<std::string, std::string>($2,$2));}
        | 
        ;

constdec:   STKEYWORD ID  constdec {constraints.insert(std::pair<std::string, std::string>($2,$2));}
        |
        ;

restdec:    RESTWORD ID
        |
        ;

relation:   REL NUMBER {std::cout << "var name: " << $1 << " var value: " << $2 << '\n';}
        |   BIN        {std::cout << "BIN" << '\n';}
        |   INT        {std::cout << "INT" << '\n';}
        |
        ;
comment:    SCOMMENT  ID    {std::cout << "SCOMMENT " << $2 <<'\n';}
        |   SCOMMENT        {std::cout << "SCOMMENT \n";}
        ;
%%

int main()
{

    std::cout << "User input\n";

    yyparse();

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
    return 0;
}