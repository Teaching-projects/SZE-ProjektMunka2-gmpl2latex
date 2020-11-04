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
    char comment[1024];
    enum relations {"<=","=",">="};
    enum obj_relations {"minimize","maximize"};
}


%token<name> ID
%token VARKEYWORD STKEYWORD SCOMMENT
%token<name> BIN INT
%token<val> NUMBER
%token<comment> SCOMMENTS
%token<obj_relations> O_REL
%token<relations> REL


%type<relations> rs r
%%


file:    vs cs o
    ;

vs:     vardec comment vs
    |
    |   comment vs;
cs:     constdec comment cs
    |
    |   comment cs;

vardec:  VARKEYWORD ID rs  ';' 
           {
                variables.insert(std::pair<std::string, std::string>($2,$2));

                toTeX << "\\item [$" << $2  << " "<< $3 << "$]\n";
           }
        ;
rs:     r rs    {$$=$1}
    |   r rss
    |
    ;

r:      BIN | INT | rel;
rss:    ',' r rss
    |
    ;
rel: REL NUMBER;

constdec:STKEYWORD ID ':' cb ';' {constraints.insert(std::pair<std::string, std::string>($2,$2)); toTeX << $2 << "\n";}
        |
        ;
cb:      l REL l ;
l:      ID | NUMBER| ;   
o:      O_REL ID
        |
        ;
comment: SCOMMENT  SCOMMENTS '\n'   {std::cout << "SCOMMENT " << $2 <<'\n'; toTeX << $2 << '\n';}
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

    /*std::ofstream vars,consts;
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
    */
    //fclose(inputfile);
    return 0;
}