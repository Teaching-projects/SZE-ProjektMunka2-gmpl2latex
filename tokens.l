%{
    #include <iostream>
    #include "grammar.tab.h"
%}

%option noyywrap
extern enum relations;

DIGITS      [0-9]
ALPHABET    [a-zA-Z]

%%
"exit"                                       return '\0';
"var"                                        return VARKEYWORD;
"s.t."                                       return STKEYWORD;
"binary"                                     return BIN;
"integer"                                    return INT;
"#!"({ALPHABET}|{DIGITS}|" ")*               {strcpy(yylval.comment, yytext);return SCOMMENTS;}
";"                                          return ';';
":"                                          return ':';
("+"|"-"|"*"|"/")                            {strcpy(yylval.operation, yytext); return OPERATOR;}
("<="|"="|">=")                              {strcpy(yylval.rels, yytext); return REL;}
"minimize"                                   {strcpy(yylval.name, yytext); return MINI;}
"maximize"                                   {strcpy(yylval.name, yytext); return MAXI;}
([1-9]({DIGITS})*|0)                         {yylval.val = std::atoi(yytext); return NUMBER;}
{ALPHABET}({ALPHABET}|{DIGITS})*             {strcpy(yylval.name, yytext); return ID;}
\n                                           /*skip newline*/;
[ \t]                                        ;
%%
