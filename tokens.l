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
"binary"                                     return BIN;
"integer"                                    return INT;
"#!"                                         return SCOMMENT;
([1-9]({DIGITS})*|0)                         {yylval.val = std::atoi(yytext); return NUMBER;}
{ALPHABET}({ALPHABET}|{DIGITS})*             {strcpy(yylval.name, yytext); return ID;}
\n                                           return '\n';/*skip newline*/
[ \t]                                        ;
%%
