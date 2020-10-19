%{
    #include <iostream>
    #include "grammar.tab.h"
%}

%option noyywrap

DIGITS      [0-9]
ALPHABET    [a-zA-Z]

%%
"exit"                                       return '\0';
"var"                                        return VARKEYWORD;
"s.t."                                       return STKEYWORD;
{ALPHABET}({ALPHABET}|{DIGITS})*             {strcpy(yylval.name, yytext); return ID;}
\n                                           return '\n';
[ \t]                                        ;
%%
