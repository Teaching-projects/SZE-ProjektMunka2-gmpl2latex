%{
    #include <iostream>
    #include <string>
    #include <vector>

    int yylex();
    int yyerror(char* message)
    {
        return 1;
    }

    std::vector<std::string> variables;
    std::vector<std::string> constraints;
%}

%union
{
    char name[16];
}


%token<name> ID
%token VARKEYWORD
%token STKEYWORD


%%


command: expression '\n' command
        |
        ;

expression:  keyword
            |
            ;

keyword:    VARKEYWORD ID
            {
                variables.push_back($2);
            }
       |    STKEYWORD ID 
            {
                constraints.push_back($2);
            }
       ;

%%

int main()
{

    std::cout << "\nUser input:\n\n";

    yyparse();

    std::cout << "\n\nList of variables:\n";
    for(int i = 0; i < variables.size(); ++i)
    {
        std::cout << variables[i] << std::endl;
    }
    std::cout << "\nList of constraints:\n";
    for(int i = 0; i < constraints.size(); ++i)
    {
        std::cout << constraints[i] << std::endl;
    }

    return 0;
}