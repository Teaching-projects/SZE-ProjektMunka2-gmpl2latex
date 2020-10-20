%{
    #include <iostream>
    #include <string>
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
%token VARKEYWORD
%token STKEYWORD
%token<name>  REL BIN INT
%token<val> NUMBER
%token LINEEND
%token<st> SCOMMENT STR

%%


command:  expression '\n' command
        |
        ;

expression: keyword //{std::cout << "Keyword\n";}
        |   comment
        |
        ;

keyword:    VARKEYWORD ID relation  LINEEND 
            {
                //std::cout << "VARKEY\n";
                variables.insert(std::pair<std::string, std::string>($2,$2));
            }
       |    STKEYWORD ID 
            {
                //std::cout << "CONST";
                constraints.insert(std::pair<std::string, std::string>($2,$2));
            }
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

    std::cout << "\n\nList of variables:\n";
    for(auto v: variables)
    {
        std::cout << "gmpl: " << v.first << " LaTex: " << v.second << '\n';
    }
    std::cout << "\nList of constraints:\n";
    for(auto v: constraints)
    {
        std::cout << "gmpl: " << v.first << " LaTex: " << v.second << '\n';
    }

    return 0;
}