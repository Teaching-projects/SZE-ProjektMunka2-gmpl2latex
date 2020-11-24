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
"#!<"({ALPHABET}|{DIGITS}|" "|[\'\"","])*    {strcpy(yylval.comment, yytext);return VARCOMMENTS;}
"#!"({ALPHABET}|{DIGITS}|" "|[\'\"","])*     {strcpy(yylval.comment, yytext);return SCOMMENTS;}
"#"({ALPHABET}|{DIGITS}|" "|[\'\"","])*      ;
";"                                          return ';';
":"                                          return ':';
("+"|"-"|"*"|"/")                            {yylval.operation = yytext[0]; return OPERATOR;}
("<="|"="|">=")                              {strcpy(yylval.rels, yytext); return REL;}
"minimize"                                   {strcpy(yylval.name, yytext); return MINI;}
"maximize"                                   {strcpy(yylval.name, yytext); return MAXI;}
([0-9]+"."[0-9]*[1-9]|0|{DIGITS}*)           {strcpy(yylval.val, yytext); return NUMBER;}
{ALPHABET}({ALPHABET}|{DIGITS}|"_")*         {strcpy(yylval.name, yytext); return ID;}
\n                                           /*skip newline*/;
[ \t]                                        ;
%%
